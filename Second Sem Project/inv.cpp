#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>  // for _getch()

using namespace std;

// Function to get password input hidden as '*'
string getPassword() 
{
    string password;
    char ch;
    cout << "Enter your password: ";
    while ((ch = _getch()) != '\r') {  // '\r' is the carriage return (Enter key)
        if (ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                password.resize(password.size() - 1);  // Remove last character
                cout << "\b \b";  // Move cursor back, overwrite with space, move back again
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

// Function to check if an account already exists
int accountExists() 
{
    ifstream file("users.txt");
    string storedUser, storedPass;
    if (file.is_open()) {
        if (file >> storedUser >> storedPass) {
            file.close();
            return 1;  // Account exists
        }
        file.close();
    }
    return 0;  // No account exists
}

// Function to log in an existing user with three attempts
int logIn() 
{
    string username, password, storedUser, storedPass;
    int attempts = 3;

    while (attempts > 0) {
        cout << "Enter your username: ";
        cin >> username;
        cin.ignore();  // To ignore the newline character after the username input
        password = getPassword();

        ifstream file("users.txt");
        if (file.is_open()) {
            while (file >> storedUser >> storedPass) {
                if (storedUser == username && storedPass == password) {
                    file.close();
                    return 1;  // Login successful
                }
            }
            file.close();
        } else {
            cout << "Error opening file.\n";
        }

        attempts--;
        if (attempts > 0) {
            cout << "Invalid username or password. You have " << attempts << " attempt(s) left.\n";
        }
    }

    return 0;  // Login failed after 3 attempts
}

// Function to sign up a new user
void signUp() {
    if (accountExists()) {
        cout << "An account already exists. Redirecting to login...\n";
        if (logIn() == 1) {
            cout << "Login successful!\n";
        } else {
            cout << "Invalid username or password.\n";
        }
        return;
    }

    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cin.ignore();  // To ignore the newline character after the username input
    password = getPassword();

    ofstream file("users.txt", ios::app);
    if (file.is_open()) {
        file << username << " " << password << endl;
        file.close();
        cout << "Sign up successful!\n";
    } else {
        cout << "Error opening file.\n";
    }
}

int main() {
    int choice;
    cout << "1. Sign Up\n";
    cout << "2. Log In\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        signUp();
    } else if (choice == 2) {
        if (logIn() == 1) {
            cout << "Login successful!\n";
        } else {
            cout << "Invalid username or password.\n";
        }
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}

