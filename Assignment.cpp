#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Book {
public:
    Book(int id, const std::string& title, const std::string& author, int copies)
        : id(id), title(title), author(author), copies(copies) {}

    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getCopies() const { return copies; }

    bool issueBook() {
        if (copies > 0) {
            copies--;
            return true;
        }
        return false;
    }

    void returnBook() {
        copies++;
    }

    void printDetails() const {
        std::cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author
                  << "\nAvailable Copies: " << copies << std::endl;
    }

private:
    int id;
    std::string title;
    std::string author;
    int copies;
};

class EBook : public Book {
public:
    EBook(int id, const std::string& title, const std::string& author, int copies, const std::string& fileFormat)
        : Book(id, title, author, copies), fileFormat(fileFormat) {}

    void printDetails() const {
        Book::printDetails();
        std::cout << "File Format: " << fileFormat << std::endl;
    }

private:
    std::string fileFormat;  
};

class Library {
public:
    void addBook() {
        int id, copies;
        std::string title, author;
        std::cout << "Enter Book ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter Book Title: ";
        std::getline(std::cin, title);
        std::cout << "Enter Author: ";
        std::getline(std::cin, author);
        std::cout << "Enter Number of Copies: ";
        std::cin >> copies;

        books.push_back(Book(id, title, author, copies));
        std::cout << "Book added successfully.\n";
    }

    void addEBook() {
        int id, copies;
        std::string title, author, fileFormat;
        std::cout << "Enter EBook ID: ";
        std::cin >> id;
        std::cin.ignore();
        std::cout << "Enter EBook Title: ";
        std::getline(std::cin, title);
        std::cout << "Enter Author: ";
        std::getline(std::cin, author);
        std::cout << "Enter Number of Copies: ";
        std::cin >> copies;
        std::cin.ignore();
        std::cout << "Enter File Format (e.g., PDF, EPUB): ";
        std::getline(std::cin, fileFormat);

        ebooks.push_back(EBook(id, title, author, copies, fileFormat));
        std::cout << "EBook added successfully.\n";
    }

    void issueBook() {
        int id;
        std::cout << "Enter Book ID to issue: ";
        std::cin >> id;

        for (auto& book : books) {
            if (book.getId() == id) {
                if (book.issueBook()) {
                    std::cout << "Book issued successfully.\n";
                } else {
                    std::cout << "No copies available.\n";
                }
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void returnBook() {
        int id;
        std::cout << "Enter Book ID to return: ";
        std::cin >> id;

        for (auto& book : books) {
            if (book.getId() == id) {
                book.returnBook();
                std::cout << "Book returned successfully.\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void generateReport() {
        std::cout << "Library Report:\n";
        for (const auto& book : books) {
            book.printDetails();
            std::cout << "-------------------------\n";
        }

        for (const auto& ebook : ebooks) {
            ebook.printDetails();
            std::cout << "-------------------------\n";
        }
    }

private:
    std::vector<Book> books;   // Collection of physical books
    std::vector<EBook> ebooks; // Collection of ebooks
};

int main() {
    Library library;
    int choice;

    while (true) {
        std::cout << "1. Add Book\n2. Add EBook\n3. Issue Book\n4. Return Book\n5. Generate Report\n6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.addEBook();
                break;
            case 3:
                library.issueBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                library.generateReport();
                break;
            case 6:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
