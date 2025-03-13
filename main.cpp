#include <iostream>
using namespace std;

// Book Class
class Book {
public:
    string title, author, isbn; // attributes title, author, isbn
    bool available; // book availability for borrowing
    Book* next; // pointer to next book
    Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true), next(nullptr) {} // constructor
};

// User Class
class User {
private:
    static int nextID; // keeps track of next available user ID
public:
    Book* borrowedBooks; // points to borrowed books
    User* next; // points to next user
    string name; // name of user
    int userID; // user id
    User(string n) : name(n), userID(nextID++), borrowedBooks(nullptr), next(nullptr) {} // constructor
    virtual string getType() = 0;
};

// initialize nextID
int User::nextID = 0;

// Student Class
class Student : public User {
public:
    Student(string n) : User(n) {}
    string getType() override { // returns type of user (student)
        return "Student";
    }
};

// Faculty Class
class Faculty : public User {
public:
    Faculty(string n) : User(n) {}
    string getType() override { // returns type of user (faculty)
        return "Faculty";
    }
};

// Singleton Library Class
class Library {
private:
    Book* books; // points to first book
    User* users; // points to first user
    static Library* instance;
    Library() : books(nullptr), users(nullptr) {}
public:
    static Library* getInstance() { // returns instance of library if not makes ones
        if (!instance) {
            instance = new Library();
        }
        return instance;
    }

    // Function to add a book
    void addBook(string title, string author, string isbn) {
        Book* newBook = new Book(title, author, isbn);
        newBook->next = books;
        books = newBook;
        cout << "> Book added: " << title << " by " << author << endl;
    }

    // Function to add a user
    void addUser(string name, int type) {
        User* newUser;
        if (type == 1) {
            newUser = new Student(name);
        } else if (type == 2) {
            newUser = new Faculty(name);
        } else {
            cout << "Invalid user type!" << endl;
            return;
        }
        newUser->next = users;
        users = newUser;
        cout << "> User added: " << name << " with ID " << newUser->userID << endl;
    }

    // Function to list all books
    void listBooks() {
        if (!books) {
            cout << "No books available." << endl;
            return;
        }
        Book* temp = books;
        cout << "> Books in the library:\n";
        while (temp) {
            cout << "Title: " << temp->title << ", Author: " << temp->author << ", ISBN: " << temp->isbn
                 << ", Available: " << (temp->available ? "Yes" : "No") << endl;
            temp = temp->next;
        }
    }

    // Function to list all users
    void listUsers() {
        if (!users) {
            cout << "No users registered." << endl;
            return;
        }
        User* temp = users;
        cout << "> Users in the library:\n";
        while (temp) {
            cout << "Name: " << temp->name << ", Type: " << temp->getType() << ", User ID: " << temp->userID << endl;
            temp = temp->next;
        }
    }

    // borrow books section

    // return books section

    // search books section

};

// define static instance
Library* Library::instance = nullptr;

// Function that handles the manage books page
void manageBooks(Library* lib) {
    int bChoice; // choice for books
    while (true) {
        cout << endl << "> Manage Books:" << endl
                    << "1. Add a Book" << endl
                    << "2. List All Books" << endl
                    << "3. Go Back" << endl
                    << "Enter your choice: ";
        cin >> bChoice;
        cin.ignore();

        if (bChoice == 1) {
            string title, author, isbn;
            cout << ">> Enter Title: "; 
            getline(cin, title);
            cout << ">> Enter Author: ";
            getline(cin, author);
            cout << ">> Enter ISBN: ";
            getline(cin, isbn);
            lib->addBook(title, author, isbn); // Adds book to library
        } else if (bChoice == 2) {
            lib->listBooks(); // List all books
        } else if (bChoice == 3) {
            break; // Go back to main menu
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Function that handles the manage users page
void manageUsers(Library* lib) {
    int uChoice; // choice for users
    while (true) {
        cout << "\n> Manage Users:\n1. Add a User\n2. List All Users\n3. Go Back\nEnter your choice: ";
        cin >> uChoice;
        cin.ignore(); // Ignore any remaining newline characters in the input buffer.

        if (uChoice == 1) {
            int type;
            string name;
            cout << ">> Enter 1 for Student or 2 for Faculty: "; cin >> type;
            cin.ignore(); // Ignore any remaining newline characters in the input buffer.
            cout << ">> Enter Name: "; getline(cin, name); // Use getline to capture full name
            lib->addUser(name, type); // Add the user to the library.
        } else if (uChoice == 2) {
            lib->listUsers(); // List all users.
        } else if (uChoice == 3) {
            break; // Go back.
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    Library* lib = Library::getInstance();
    int choice; // choice for main menu

    while (true) {
        cout << endl << "Welcome to the Library: " << endl
                << "1. Manage Books" << endl
                << "2. Manage Users" << endl
                << "3. Exit" << endl
                << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            manageBooks(lib); // manage books menu
        } else if (choice == 2) {
            manageUsers(lib); // manage users menu
        } else if (choice == 3) {
            cout << "Thank you for using the Library System!" << endl;
            break; // exit loop
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}