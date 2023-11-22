#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool available;
};

struct Borrower {
    string name;
    int borrowedBooks;
};

struct Transaction {
    string bookISBN;
    string borrowerName;
    time_t checkoutDate;
    time_t returnDate;
};

class Library {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<Transaction> transactions;

public:
    void addBook(const Book& book);
    void searchBooks(const string& searchTerm);
    void displayAllBooks();
    void checkoutBook(const string& ISBN, const string& borrowerName);
    void returnBook(const string& ISBN);

    void addBorrower(const Borrower& borrower);

    void displayTransactions();
};

void printBook(const Book& book);

int main() {
    Library library;

    library.addBook({"The Catcher in the Rye", "J.D. Salinger", "9780140237504", true});
    library.addBook({"To Kill a Mockingbird", "Harper Lee", "9780061120084", true});
    library.addBook({"1984", "George Orwell", "9780451524935", true});

    library.addBorrower({"John Doe", 0});
    library.addBorrower({"Jane Smith", 0});

    library.checkoutBook("9780140237504", "John Doe");
    library.checkoutBook("9780061120084", "Jane Smith");

    library.displayAllBooks();

    library.displayTransactions();

    library.returnBook("9780140237504");

    library.displayAllBooks();

    return 0;
}

void Library::addBook(const Book& book) {
    books.push_back(book);
}

void Library::searchBooks(const string& searchTerm) {
    cout << "\n--- Search Results ---\n";
    for (const Book& book : books) {
        if (book.title.find(searchTerm) != string::npos ||
            book.author.find(searchTerm) != string::npos ||
            book.ISBN.find(searchTerm) != string::npos) {
            printBook(book);
        }
    }
}

void Library::displayAllBooks() {
    cout << "\n--- All Books ---\n";
    for (const Book& book : books) {
        printBook(book);
    }
}

void Library::checkoutBook(const string& ISBN, const string& borrowerName) {
    auto bookIt = find_if(books.begin(), books.end(),
                          [&ISBN](const Book& book) {
                              return book.ISBN == ISBN && book.available;
                          });

    auto borrowerIt = find_if(borrowers.begin(), borrowers.end(),
                              [&borrowerName](const Borrower& borrower) {
                                  return borrower.name == borrowerName;
                              });

    if (bookIt != books.end() && borrowerIt != borrowers.end()) {
        bookIt->available = false;
        borrowerIt->borrowedBooks++;

        Transaction transaction = {ISBN, borrowerName, time(nullptr), 0};
        transactions.push_back(transaction);

        cout << "Book checked out successfully.\n";
    } else {
        cout << "Book or borrower not found, or the book is not available.\n";
    }
}

void Library::returnBook(const string& ISBN) {
    auto bookIt = find_if(books.begin(), books.end(),
                          [&ISBN](const Book& book) {
                              return book.ISBN == ISBN && !book.available;
                          });

    if (bookIt != books.end()) {
        bookIt->available = true;

        auto transactionIt = find_if(transactions.begin(), transactions.end(),
                                     [&ISBN](const Transaction& transaction) {
                                         return transaction.bookISBN == ISBN && transaction.returnDate == 0;
                                     });

        if (transactionIt != transactions.end()) {
            transactionIt->returnDate = time(nullptr);
            cout << "Book returned successfully.\n";
        } else {
            cout << "Transaction not found.\n";
        }
    } else {
        cout << "Book not found or already returned.\n";
    }
}

void Library::addBorrower(const Borrower& borrower) {
    borrowers.push_back(borrower);
}

void Library::displayTransactions() {
    cout << "\n--- Transaction History ---\n";
    for (const Transaction& transaction : transactions) {
        cout << "Book ISBN: " << transaction.bookISBN << " | Borrower: " << transaction.borrowerName
             << " | Checkout Date: " << ctime(&transaction.checkoutDate);

        if (transaction.returnDate != 0) {
            cout << " | Return Date: " << ctime(&transaction.returnDate);
        } else {
            cout << " | Status: Checked Out\n";
        }

        cout << endl;
    }
}

void printBook(const Book& book) {
    cout << "Title: " << book.title << " | Author: " << book.author
         << " | ISBN: " << book.ISBN << " | Available: " << (book.available ? "Yes" : "No") << endl;
}
