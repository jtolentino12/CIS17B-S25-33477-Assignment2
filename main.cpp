#include <iostream>

using namespace std;

// Book Class
class Book {
    public:
        string title, author, isbn;
        bool available;
        Book* next;

        Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true), next(nullptr) {}
};

// Library Class
class Library {

};

// User Class
class User {

};

// Student Class
class Student : public User {

};

// Faculty Class
class Faculty : public User {

};

int main() {







    return 0;
}

