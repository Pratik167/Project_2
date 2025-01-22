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
void shopping :: admin()
{
	m:
	int choice;
	cout<<"\n\n\n\t\t\tADMIN SECTION";
	cout<<"\n\n\n\t\t|______1) Add the product|";
	cout<<"\n\n\n\t\t|______2) Modify the product|";
	cout<<"\n\n\n\t\t|______3) Delete the product|";
	cout<<"\n\n\n\t\t|______4) Back To Main Menu|";
	
	cout<<"\n\n\t\t Enter:";
	cin>>choice;
	
	switch(choice)
	{
		case 1:
			add();
			break;
		case 2:
			edit();
			break;
		case 3:
			rem();
			break;
		case 4:
			menu();
			break;
			
		default:
			cout<<"Invalid Choice, Enter Again";
	}
	goto m;
}

void shopping::buyer()
{
	m:
	int choice;
	cout<<"\t\t\t MENU";
	cout<<"\t\t\t ___________\n";
	cout<<"                  \n";
	cout<<"\t\t 1) Buy Product\n";
	cout<<"                  \n";
	cout<<"\t\t 2) Go Back   \n";
	cout<<"\t\t Enter:";
	cin>>choic;
	switch(choice)
	{
		case 1:
			receipt();
			break;
			
		case 2;
		menu();
		default:
			cout<<"Invalid choice";
	}
	goto m;
}
void shopping::add()
{
	fstream data;
	int c;
	int token=0;
	float p;
	float d;
	string n;
	
	cout<<"\n\n\t\t\t Add New Product";
	cout<<"\n\n\t Product Code of the Product:";
	cint>>pcode;
	cout<<"\n\n\t Name of the product:";
	cin>>pname;
	cout<<"\n\n\t Price of the product:";
	cin>>price;
	cout<<"\n\n\t Discount on Product:";
	cin>>dis;
	
	data.open("database.txt",ios::in);
	if(!data)
	{
		data.open("database.txt",ios::app|ios::out);
		data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
		data.close();	
	}
	else
	{
		data>>c>>n>>p>>d;
		while(!data.eof())
		{
			if(c==pcode)
			{
				token++;
			}
			data>>c>>n>>p>>d;
		}
		data.close();
		
		if(token==1)
		{
		goto m;
		}
		else
		{
		data.open("database.txt",ios::app|ios::out);
		data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
		data.close();
		}
	}
	cout<<"\n\n\t\t Recorded Successfully!!!";
}
int main() 
{
    shopping obj;
    obj.menu();
    return 0;
}

