#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <ctime>
#include <sstream>
#include <limits>
using namespace std;

class Book
{
public:
    string title, author, publisher, isbn;
    int year;
    string status = "Available";
    Book(string t, string a, string p, int y, string i, string s) : title(t), author(a), publisher(p), year(y), isbn(i), status(s) {}
    void displaybook()
    {
        cout << "Title: " << title << ", Author: " << author << ", Publisher: " << publisher
             << ", Year: " << year << ", ISBN: " << isbn << ", Status: " << status << endl;
    }
};

class Account
{
private:
    vector<pair<string, time_t>> borrowedBooks;
    int fine;

public:
    Account() : fine(0) {}
    int getFine() { return fine; }
    void addFine(int amount) { fine += amount; }
    void clearFine() { fine = 0; }
    vector<pair<string, time_t>> &getBorrowedBooks() { return borrowedBooks; }
};

class User
{
protected:
    string name;
    string id;

public:
    Account account;
    string role;
    User(string n, string id, string r) : name(n), id(id), role(r) {}
    virtual ~User() {}
    string getId() { return id; }
    string getName() { return name; }
    virtual void borrowBook(vector<Book> &books, string isbn) = 0;
    virtual void returnBook(vector<Book> &books, string isbn) = 0;
};

class Student : public User
{
private:
    int maxBooks = 3;
    int finePerDay = 10;
    int maxBorrowDays = 15;
    int calculateFine()
    {
        int finex = 0;
        time_t now = time(0);
        for (const auto &b : account.getBorrowedBooks())
        {
            int daysBorrowed = (now - b.second)/(60*60*24);
            if (daysBorrowed > maxBorrowDays)
            {
                finex += (daysBorrowed - maxBorrowDays) * finePerDay;
            }
        }
        account.addFine(finex);
        int x = account.getFine();
        finex = 0;
        return x;
    }

public:
    Student(string n, string id, string r = "Student") : User(n, id, r) {}
    void borrowBook(vector<Book> &books, string isbn) override
    {
        if (calculateFine() == 0)
        {
            if (account.getBorrowedBooks().size() < maxBooks)
            {
                for (auto &book : books)
                {
                    if (book.isbn == isbn && book.status == "Available")
                    {
                        book.status = "Borrowed";
                        time_t now = time(0);
                        account.getBorrowedBooks().push_back({isbn, now});
                        cout << "Book borrowed successfully!" << endl;
                        return;
                    }
                }
                cout << "Book is not available!" << endl;
            }
            else
            {
                cout << "Borrow limit reached!" << endl;
            }
        }
        else
        {
            cout << "you are not allowed to borrow books until fine is paid" << endl;
        }
    }
    void payFine()
    {
        cout << "Amount paid = " << calculateFine() << endl;
        cout << "Fine paid successfully!" << endl;
        account.clearFine();
    }
    void returnBook(vector<Book> &books, string isbn) override
    {
        for (auto it = account.getBorrowedBooks().begin(); it != account.getBorrowedBooks().end(); ++it)
        {
            if (it->first == isbn)
            {
                time_t now = time(0);
                int daysBorrowed = (now - it->second)/(60*60*24);
                if (daysBorrowed > maxBorrowDays)
                {
                    int overdue = (daysBorrowed - maxBorrowDays);
                    int bookfine = (daysBorrowed - maxBorrowDays) * finePerDay;
                    cout << "This book is Overdue by " << overdue << "days.\nFine for this book: " << bookfine << " rupees." << endl;
                    payFine();
                }
                account.getBorrowedBooks().erase(it);
                for (auto &book : books)
                {
                    if (book.isbn == isbn)
                    {
                        book.status = "Available";
                        break;
                    }
                }
                cout << "Book returned successfully!" << endl;
                return;
            }
        }
        cout << "Book not found in borrowed list!" << endl;
    }
    void viewBorrowedBooks()
    {
        if (account.getBorrowedBooks().empty())
        {
            cout << "No borrowed books." << endl;
            return;
        }
        cout << "Borrowed Books:" << endl;
        for (const auto &b : account.getBorrowedBooks())
        {
            cout << "ISBN: " << b.first << " Borrowed on: " << ctime(&b.second) << endl;
        }
    }
    void veiwfine()
    {
        cout << calculateFine() << endl;
    }
   
};
class Faculty : public User
{
    int maxBooks = 5;
    int maxBorrowDays = 30;
    int canborrow()
    {
        int canborrow = 1;
        for (auto it = account.getBorrowedBooks().begin(); it != account.getBorrowedBooks().end(); ++it)
        {
            time_t now = time(0);
            int daysBorrowed = (now - it->second)/(60*60*24);
            if (daysBorrowed > 60)
            {
                canborrow = 0;
                break;
            }
        }
        return canborrow;
    }

public:
    int getcanborrow()
    {
        return canborrow();
    }
    Faculty(string n, string id, string r = "Faculty") : User(n, id, r) {}
    void borrowBook(vector<Book> &books, string isbn) override
    {
        if (account.getBorrowedBooks().size() < maxBooks)
        {
            for (auto &book : books)
            {
                if (book.isbn == isbn && book.status == "Available")
                {
                    book.status = "Borrowed";
                    time_t now = time(0);
                    account.getBorrowedBooks().push_back({isbn, now});
                    cout << "Book borrowed successfully!" << endl;
                    return;
                }
            }
            cout << "Book is not available!" << endl;
        }
        else
        {
            cout << "Borrow limit reached!" << endl;
        }
    }
    void returnBook(vector<Book> &books, string isbn) override
    {
        for (auto it = account.getBorrowedBooks().begin(); it != account.getBorrowedBooks().end(); ++it)
        {
            if (it->first == isbn)
            {
                time_t now = time(0);
                int daysBorrowed = (now - it->second)/(60*60*24);
                if (daysBorrowed > maxBorrowDays)
                {
                    int overdue = (daysBorrowed - maxBorrowDays);
                    cout << "Overdue by " << overdue << "days" << endl;
                }
                account.getBorrowedBooks().erase(it);
                for (auto &book : books)
                {
                    if (book.isbn == isbn)
                    {
                        book.status = "Available";
                        break;
                    }
                }
                cout << "Book returned successfully!" << endl;
                return;
            }
        }
        cout << "Book not found in borrowed list!" << endl;
    }
    void viewBorrowedBooks()
    {
        if (account.getBorrowedBooks().empty())
        {
            cout << "No borrowed books." << endl;
            return;
        }
        cout << "Borrowed Books:" << endl;
        for (const auto &b : account.getBorrowedBooks())
        {
            cout << "ISBN: " << b.first << " Borrowed on: " << ctime(&b.second);
        }
    }
};

class Librarian : public User
{
public:
    Librarian(string n, string id, string r = "Librarian") : User(n, id, r) {}
    void borrowBook(vector<Book> &books, string isbn) override
    {
        cout << "Librarians cannot borrow books!" << endl;
    }
    void returnBook(vector<Book> &books, string isbn) override {}
    void addBook(vector<Book> &books, string title, string author, string publisher, int year, string isbn)
    {
        books.push_back(Book(title, author, publisher, year, isbn, "Available"));
        cout << "Book added successfully!" << endl;
    }
    void removeBook(vector<Book> &books, string isbn)
    {
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->isbn == isbn)
            {
                books.erase(it);
                cout << "Book removed successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void updateBook(vector<Book> &books, string isbn, string newTitle, string newAuthor, string newPublisher, int newyear)
    {
        for (auto &book : books)
        {
            if (book.isbn == isbn)
            {
                book.title = newTitle;
                book.author = newAuthor;
                book.publisher = newPublisher;
                book.year = newyear;
                cout << "Book information updated successfully!" << endl;
                return;
            }
        }
        cout << "Book not found!" << endl;
    }
    void addUser(vector<User *> &users, User *newUser)
    {
        users.push_back(newUser);
        cout << "User added successfully!" << endl;
    }
    void removeUser(vector<User *> &users, string userid)
    {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if ((*it)->getId() == userid)
            { // Use getId() instead of directly accessing id
                users.erase(it);
                cout << "User removed successfully!" << endl;
                return;
            }
        }
        cout << "User not found!" << endl;
    }
};

class Library
{
public:
    vector<Book> books;
    vector<User *> users;

    Library() {}
    ~Library()
    {
        for (auto u : users)
            delete u;
    }

    void loadData()
    {
        // Load books
        ifstream infile("./data/books.txt");
        if (!infile)
        {
            cout << "Error: books.txt not found or could not be opened." << endl;
            return;
        }

        string line;
        while (getline(infile, line))
        {
            if (line.empty())
                continue;

            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ','))
            {
                tokens.push_back(token);
            }

            if (tokens.size() != 6)
                continue;

            try
            {
                int year = stoi(tokens[3]);
                books.push_back(Book(tokens[0], tokens[1], tokens[2], year, tokens[4], tokens[5]));
            }
            catch (const invalid_argument &e)
            {
                cout << "Invalid year format in books.txt: " << tokens[3] << endl;
            }
        }
        infile.close();

        // Load users
        ifstream ufile("./data/users.txt");
        if (!ufile)
        {
            cout << "Error: users.txt not found or could not be opened." << endl;
            return;
        }

        while (getline(ufile, line))
        {
            if (line.empty())
                continue;

            istringstream iss(line);
            vector<string> tokens;
            string token;
            while (getline(iss, token, ','))
            {
                tokens.push_back(token);
            }

            if (tokens.size() != 3)
                continue; // name, userID, role

            string name = tokens[0];
            string id = tokens[1];
            string role = tokens[2];

            if (role == "Student")
                users.push_back(new Student(name, id));
            else if (role == "Faculty")
                users.push_back(new Faculty(name, id));
            else if (role == "Librarian")
                users.push_back(new Librarian(name, id));
            else
            {
                cout << "Unknown role: " << role << endl;
            }
        }
        ufile.close();
    }
    void saveData()
    {
        // Save books
        ofstream outfile("./data/books.txt");
        for (auto &book : books)
        {
            outfile << book.title << "," << book.author << ","
                    << book.publisher << "," << book.year << "," << book.isbn << ","
                    << book.status << "\n";
        }
        outfile.close();

        // Save users
        ofstream uoutfile("./data/users.txt");
        for (auto user : users)
        {
            string role;
            if (dynamic_cast<Student *>(user))
                role = "Student";
            else if (dynamic_cast<Faculty *>(user))
                role = "Faculty";
            else if (dynamic_cast<Librarian *>(user))
                role = "Librarian";

            uoutfile << user->getName() << "," << user->getId() << "," << role << "\n";
        }
        uoutfile.close();
    }

    void ViewAvailableBooks()
    {
        cout << "\nAvailable Books:\n";
        for (auto &book : books)
        {
            if (book.status == "Available")
                book.displaybook();
        }
    }


    Book *findBookByISBN(string isbn)
    {
        for (auto &book : books)
        {
            if (book.isbn == isbn)
                return &book;
        }
        return nullptr;
    }
};

int main()
{
    Library library;
    library.loadData();

    int choice;
    cout << "\n*LIBRARY MANAGEMENT SYSTEM*\n";
    do
    {
        cout << "1. Student" << endl;
        cout << "2. Faculty" << endl;
        cout << "3. Librarian" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == 1)
        {
            string name, id;
            cout << "Enter name : ";
            cin >> name;
            cout << "Enter Id : ";
            cin >> id;
            int Is_student = 0;

            User *loggedInUser = nullptr;
            for (auto user : library.users)
            {
                if (user->getName() == name && user->getId() == id)
                {
                    loggedInUser = user;
                    Is_student = 1;
                    break;
                }
            }

            if (loggedInUser == nullptr)
            {
                cout << "User not found!\n";
            }

            // Use dynamic_cast to check if the user is a Student
            Student *student = dynamic_cast<Student *>(loggedInUser);
            if (Is_student)
            {
                cout << "Welcome " << name << endl;
                cout << "----------------------------------" << endl;
                do
                {
                    cout << "1. View Available Books" << endl;
                    cout << "2. Borrow a Book" << endl;
                    cout << "3. Return a Book" << endl;
                    cout << "4. View Borrowed Books" << endl;
                    cout << "5. Check Fine" << endl;
                    cout << "6. Pay Fine" << endl;
                    cout << "7. Exit" << endl;
                    cout << "Enter your choice : ";
                    cin >> choice;

                    if (choice == 1)
                    {
                        library.ViewAvailableBooks();
                    }
                    else if (choice == 2)
                    {
                        string isbn;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        student->borrowBook(library.books, isbn);
                    }
                    else if (choice == 3)
                    {
                        string isbn;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        student->returnBook(library.books, isbn);
                    }
                    else if (choice == 4)
                    {
                        student->viewBorrowedBooks();
                    }
                    else if (choice == 5)
                    {
                        student->veiwfine();
                    }
                    else if (choice == 6)
                    {
                        student->payFine();
                    }
                    else if (choice == 7)
                    {
                        cout << "Exiting.....";
                    }
                    else
                    {
                        cout << "Invalid choice! Try again.\n";
                    }

                    library.saveData();
                } while (choice != 7);
            }
        }
        else if (choice == 2)
        {
            string name, id;
            cout << "Enter name : ";
            cin >> name;
            cout << "Enter Id : ";
            cin >> id;
            int Is_faculty = 0;
            User *loggedInUser = nullptr;
            for (auto user : library.users)
            {
                if (user->getName() == name && user->getId() == id)
                {
                    loggedInUser = user;
                    Is_faculty = 1;
                    break;
                }
            }

            if (loggedInUser == nullptr)
            {
                cout << "User not found!\n";
            }

            Faculty *faculty = dynamic_cast<Faculty *>(loggedInUser);
            if (Is_faculty)
            {
                cout << "Welcome " << name << endl;
                cout << "---------------------------------" << endl;
                do
                {
                    cout << "1. View Available Books" << endl;
                    cout << "2. Borrow a Book" << endl;
                    cout << "3. Return a Book" << endl;
                    cout << "4. View Borrowed Books" << endl;
                    cout << "5. Exit" << endl; 
                    cout << "Enter your choice : ";
                    cin >> choice;

                    if (choice == 1)
                    {
                        library.ViewAvailableBooks();
                    }
                    else if (choice == 2)
                    {
                        string isbn;
                        if (faculty->getcanborrow() == 0)
                        {
                            cout << "You have an overdue book for more than 60 days.\nYou cannnot borrow books.\n"
                                 << "You have to return overdue book to borrow new book." << endl;
                        }
                        else
                        {
                            cout << "Enter book ISBN: ";
                            cin >> isbn;

                            faculty->borrowBook(library.books, isbn);
                        }
                    }
                    else if (choice == 3)
                    {
                        string isbn;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        faculty->returnBook(library.books, isbn);
                    }
                    else if (choice == 4)
                    {
                        faculty->viewBorrowedBooks();
                    }
                    else if (choice == 5)
                    {
                        cout << "Exiting........";
                    }
                    library.saveData();
                } while (choice != 5);
            }
        }
        else if (choice == 3)
        {
            string name, id;
            cout << "Enter name : ";
            cin >> name;
            cout << "Enter Id : ";
            cin >> id;
            int Is_librarian = 0;
            User *loggedInUser = nullptr;
            for (auto user : library.users)
            {
                if (user->getName() == name && user->getId() == id)
                {
                    loggedInUser = user;
                    Is_librarian = 1;
                    break;
                }
            }

            if (loggedInUser == nullptr)
            {
                cout << "User not found!\n";
            }
            Librarian *librarian = dynamic_cast<Librarian *>(loggedInUser);
            if (Is_librarian)
            {
                cout << "Welcome " << name << endl;
                cout << "---------------------------------------------";
                do
                {
                    cout << "1. View Available Books" << endl;
                    cout << "2. View All Books" << endl;
                    cout << "3. Add a Book" << endl;
                    cout << "4. Remove a Book" << endl;
                    cout << "5. Update a Book" << endl;
                    cout << "6. View All Users" << endl;
                    cout << "7. Add a User" << endl;
                    cout << "8. Remove a User" << endl;
                    cout << "9. Exit" << endl;
                    cout << "Enter your choice : ";
                    cin >> choice;

                    if (choice == 1)
                    {
                        library.ViewAvailableBooks();
                    }
                    else if (choice == 2)
                    {
                        cout << "\n All Books\n";
                        for (auto &book : library.books)
                        {
                            book.displaybook();
                        }
                    }
                    else if (choice == 3)
                    {
                        string title, author, publisher, isbn;
                        int year;
                        cout << "Enter book title: ";
                        cin >> title;
                        cout << "Enter book author: ";
                        cin >> author;
                        cout << "Enter book publisher: ";
                        cin >> publisher;
                        cout << "Enter book year: ";
                        cin >> year;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        librarian->addBook(library.books, title, author, publisher, year, isbn);
                    }
                    else if (choice == 4)
                    {
                        string isbn;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        librarian->removeBook(library.books, isbn);
                    }
                    else if (choice == 5)
                    {
                        string isbn, newTitle, newAuthor, newPublisher;
                        int newYear;
                        cout << "Enter book ISBN: ";
                        cin >> isbn;
                        cout << "Enter new title: ";
                        cin >> newTitle;
                        cout << "Enter new author: ";
                        cin >> newAuthor;
                        cout << "Enter new publisher: ";
                        cin >> newPublisher;
                        cout << "Enter new year: ";
                        cin >> newYear;
                        librarian->updateBook(library.books, isbn, newTitle, newAuthor, newPublisher, newYear);
                    }
                    else if (choice == 6)
                    {
                        cout << "\nAll Users\n";
                        for (auto user : library.users)
                        {
                            cout << "Name: " << user->getName() << ", ID: " << user->getId() << ", Role: " << user->role << endl;
                        }
                    }
                    else if (choice == 7)
                    {
                        string name, id, role;
                        cout << "Enter user name: ";
                        cin >> name;
                        cout << "Enter user ID: ";
                        cin >> id;
                        cout << "Enter user role (Student/Faculty/Librarian): ";
                        cin >> role;
                        if (role == "Student")
                        {
                            librarian->addUser(library.users, new Student(name, id));
                        }
                        else if (role == "Faculty")
                        {
                            librarian->addUser(library.users, new Faculty(name, id));
                        }
                        else if (role == "Librarian")
                        {
                            librarian->addUser(library.users, new Librarian(name, id));
                        }
                    }
                    else if (choice == 8)
                    {
                        string userid;
                        cout << "Enter user ID: ";
                        cin >> userid;
                        librarian->removeUser(library.users, userid);
                    }
                    else if (choice == 9)
                    {
                        cout << "Exiting........";
                    }
                    library.saveData();
                } while (choice != 9);
            }
        }
        else if (choice == 4)
        {
            cout << "Exiting.............";
        }
        else
        {
            cout << "Invalid choice" << endl;
        }

    } while (choice != 4);
    return 0;
}