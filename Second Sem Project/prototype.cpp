#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class permission;

class shopping 
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void admin();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
    friend class permission;
};

class permission // login haru ko lagi made this class
{
public:
    string getPassword() 
	{
        string password;
        char ch;
        cout << "Enter your password: ";
        while ((ch = _getch()) != '\r') 
		{  // '\r' is the Enter key
            if (ch == '\b') 
			{  // Handle backspace
                if (!password.empty()) 
				{
                    password.resize(password.size() - 1);  // Remove last character
                    cout << "\b \b";  // Move cursor back, overwrite with space, move back again
                }
            } 
			else 
			{
                password += ch;
                cout << '*';
            }
        }
        cout << endl;
        return password;
    }

    int accountExists() 
	{
        ifstream file("users.txt");
        string storedUser, storedPass;
        if (file.is_open()) 
		{
            if (file >> storedUser >> storedPass) 
			{
                file.close();
                return 1;  // Account exists
            }
            file.close();
        }
        return 0;  // No account exists
    }

    void signUp() 
	{
        if (accountExists()) 
		{
            cout << "An account already exists. Redirecting to login...\n";
            if (logIn() == 1) 
			{
                cout << "Login successful!\n";
            } 
			else 
			{
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
        if (file.is_open()) 
		{
            file << username << " " << password << endl;
            file.close();
            cout << "Sign up successful!\n";
        } 
		else 
		{
            cout << "Error opening file.\n";
        }
    }

    int logIn() 
	{
        string username, password, storedUser, storedPass;
        int attempts = 3;

        while (attempts > 0) 
		{
            cout << "Enter your username: ";
            cin >> username;
            cin.ignore();  // To ignore the newline character after the username input
            password = getPassword();

            ifstream file("users.txt");
            if (file.is_open()) 
			{
                while (file >> storedUser >> storedPass) 
				{
                    if (storedUser == username && storedPass == password) 
					{
                        file.close();
                        return 1;  // Login successful
                    }
                }
                file.close();
            } 
			else 
			{
                cout << "Error opening file.\n";
            }

            attempts--;
            if (attempts > 0) 
			{
                cout << "Invalid username or password. You have " << attempts << " attempt(s) left.\n";
            }
        }

        return 0;  // Login failed after 3 attempts
    }
};
// shopping class ko member functions
void shopping::menu()
{
    int choice;
    permission perm;

    cout << "\t\t\t____________________________\n";
    cout << "\t\t\t_________MAIN<>MENU_________\n";
    cout << "\t\t\t____________________________\n";

    cout << "\t\t\t 1. Signup \n";
    cout << "\t\t\t 2. Login \n";
    cout << "\t\t\t 3. Exit  \n";
    pass:
    cout << "\t\t\t Choice:";
    cin >> choice;

    switch (choice) 
	{
        case 1:
            perm.signUp();  // Call signUp using the permission instance
            break;
        case 2:
            if (perm.logIn()) 
			{
                cout << "Login successful!\n";
            } 
			else 
			{
                cout << "Invalid username or password.\n";
            }
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice! Please try again.\n";
            goto pass;
    }
};
int main() 
{
    shopping obj;
    obj.menu();
    return 0;
}

