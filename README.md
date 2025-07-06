# Library Management System

This system is designed to manage books and user interactions within a library. It supports three user roles, students, faculty, and librarians, each with specific privileges and limitations.Students and Faculty can borrow and return books,Librarians can manage users and books.


### Compilation & Execution Instructions

#### Compilation Command
bash
g++ LMS.cpp -o LMS

#### Execution Command
bash
.\LMS 


## Features

1.*User Management*:
-Supports user roles with different borrowing limits and fine policies.
2.*Book Management*:
-Allows librarians to add, remove, and update books.
3.*Borrowing and Returning Books*:
-Users can borrow and return books based on their roles.
4.*Fine Management*:
-Automatically calculates fines for overdue books.
5.*Data Persistence*:
- Save all changes (books and user data) to files (books.txt and users.txt) for persistent storage.


## User Roles
### Student:
-Can borrow up to 3 books for 15 days.Fine are calculated at 10 rupees per day after the due date.
### Faculty:
-Can borrow up to 5 books for 30 days. No fines are applied for overdue books.
### Librarian:
-Manages books and users. Cannot borrow books.
5. Data Persistence:
- Save all changes (books and user data) to files (books.txt and users.txt) for persistent storage.


### Requirements

#### Software Requirements
- A C++ compiler like g++ (part of GCC).
- Visual Studio Code (or any text editor/IDE).
#### Files Required
- books.txt : Stores the list of the books in the library.
- users.txt : Stores the list of registered users.


### How to Use
1. When you run the program, you will see a menu like this:
text
~ LIBRARY MANAGEMENT SYSTEM ~
1. Student
2. Faculty
3. Librarian
4. Exit
Enter your choice:

2. Select your role by entering the corresponding number.

#### For Students:
- Log in with your name and user ID.
- After logging in, you can perform these actions:
 - View available books.
 - Borrow a book.
 - Return a borrowed book.
 - View borrowed books.
 - Check fine amount for overdue books.
 - Pay fines to clear outstanding dues.
 - Exit

#### For Faculty:
- Log in with your name and user ID.
- After logging in, you can perform these actions:
 - View available books.
 - Borrow a book (up to 5 books at a time).
 - Return a borrowed book.
 - View borrowed books.
 - Exit

#### For Librarians:
- Log in with your name and user ID.
- After logging in, you can perform these actions:
 - View available books.
 - View all books.
 - Add new books to the library.
 - Remove existing books from the library.
 - Update book details (title, author, publisher, etc.).
 - View all Users.
 - Add new users (students or faculty).
 - Remove existing users.
 - Exit.

 
