#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
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
    void loggedInMenu();
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
		system("cls");
		cout<<"\t\t\t\tSIGN UP PAGE\n";
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
		system("cls");
		cout<<"\t\t\t\t\tLOGIN PAGE\n";
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
    cout << "\t\t\t Choice: ";
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
                for (int q=0;q<3;q++)
					{
                        Sleep(100);
                        printf(".");
                        Sleep(100);
                        printf(".");
                        Sleep(100);
                        printf(".");
                        Sleep(200);
                        printf("\b \b");
                        printf("\b \b");
                        printf("\b \b");
                    }
                loggedInMenu();  // Call the logged-in menu
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
}

void shopping::loggedInMenu() 
{
	system("cls");
    int choice;
    while (true) 
	{
        cout << "\n\n\t\t\t Welcome to the Main Menu\n";
        cout << "\t\t\t _________________________\n";
        cout << "\t\t\t 1. Admin (Modify Menu)\n";
        cout << "\t\t\t 2. Buyer (Generate Invoice)\n";
        cout << "\t\t\t 3. Exit\n";
        cout << "\t\t\t Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                admin();  // Navigate to admin section
                break;
            case 2:
                buyer();  // Navigate to buyer section
                break;
            case 3:
                cout << "\nExiting the system. Goodbye!\n";
                exit(0);  // Exit the program
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    }
}

void shopping :: admin()
{
	system("cls");
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
			loggedInMenu();
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
	system("cls");
	cout<<"\t\t\t MENU";
	cout<<"\n\t\t\t ___________\n";
	cout<<"                  \n";
	cout<<"\t\t 1) Generate Invoice\n";
	cout<<"                  \n";
	cout<<"\t\t 2) Go Back   \n";
	cout<<"                  \n";
	cout<<"\t\t 3) Exit   \n";
	cout<<"\t\t Enter:";
	cin>>choice;
	switch(choice)
	{
		case 1:
			receipt();
			break;
			
		case 2:
		menu();
		
		case 3:
			cout<<"Exiting The Program!!!";
			for (int q=0;q<3;q++)
					{
                        Sleep(100);
                        printf(".");
                        Sleep(100);
                        printf(".");
                        Sleep(100);
                        printf(".");
                        Sleep(200);
                        printf("\b \b");
                        printf("\b \b");
                        printf("\b \b");
                    }
			exit(0);
		default:
			cout<<"Invalid choice";
	}
	goto m;
}
void shopping::add()
{
	system("cls");
	fstream data;
	int c;
	int token=0;
	float p;
	float d;
	string n;
	m:
	list();
	cout<<"\n\n\t\t\t Add New Product";
	cout<<"\n\n\t Product Code of the Product:";
	cin>>pcode;
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
void shopping::edit()
{
	system("cls");
	fstream data,data1;
	int pkey;
	int token=0;
	int c;
	float p;
	float d;
	string n;
	list();
	cout<<"\n\t\t\t Modify Item";
	cout<<"\n\t\t\t Product Code:";
	cin>>pkey;
	data.open("database.txt",ios::in);
	if(!data)
	{
		cout<<"\n\n File Doesn't Exist";
	}
	else
	{
		data1.open("database1.txt",ios::app|ios::out);
		data>>pcode>>pname>>price>>dis;
		while(!data.eof())
		{
			if(pkey==pcode)
			{
				cout<<"\n\t\t Product New Code:";
				cin>>c;
				cout<<"\n\t\t Name of the product:";
				cin>>n;
				cout<<"\n\t\t Price:";
				cin>>p;
				cout<<"\n\t\t Discount:";
				cin>>d;
				data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
				cout<<"\n\n\t\t Record Edited!!!";
				token++;
			}
			else
			{
				data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
			}
			data>>pcode>>pname>>price>>dis;
		}
		data.close();
		data1.close();
		remove("database.txt");
		rename("database1.txt","database.txt");
		if(token==0)
		{
			cout<<"\n\n Record Not Found!!!";
		}
	}
}
void shopping::rem()
{
	system("cls");
	list();
	fstream data,data1;
	int pkey;
	int token=0;
	cout<<"\n\n\t Delete Product";
	cout<<"\n\n\t Product Code:";
	cin>>pkey;
	data.open("database.txt",ios::in);
	if(!data)
	{
		cout<<"\n\n File Doesn't Exist";
	}
	else
	{
		data1.open("database1.txt",ios::app|ios::out);
		data>>pcode>>pname>>price>>dis;
		while(!data.eof())
		{
			if(pkey==pcode)
			{
				cout<<"\n\n\t Product Deleted Successfully";
				token++;
			}
			else
			{
				data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<dis<<"\n";
			}
			data>>pcode>>pname>>price>>dis;
		}
		data.close();
		data1.close();
		remove("database.txt");
		rename("database1.txt","database.txt");
		if(token==0)
		{
			cout<<"\n\n Record Not Found!!!";
		}
	}
}
void shopping::list()
{
    system("cls");
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|____________________MENU_________________________\n";
    cout << "| ProNo    Name                      Price\n";
    cout << "|_____________________________________________\n";
    if (!data)
    {
        cout << "No products available.\n";
        return;
    }

    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << setw(8) << left << pcode
             << setw(25) << left << pname
             << setw(10) << left << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}
void shopping::receipt()
{
    system("cls");
    fstream data;
    int arrc[100]; // array of product codes
    int arrq[100]; // array of quantities
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;

    string customerName;  // Variable to store customer name
    cout << "\n\n\t\t\t\t RECEIPT";
    cout << "\n\n Enter Customer's Name: ";
    cin.ignore();  // Clear the input buffer
    getline(cin, customerName);  // Get the full name including spaces

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty!!!";
        return;
    }
    data.close();
    list();
    cout << "\n ________________________________________\n";
    cout << "                Place Order              \n";
    cout << "_________________________________________\n";

    do
    {
        cout << "\n\n Enter Product Code: ";
        cin >> arrc[c];
        cout << "\n\n Enter the Product Quantity: ";
        cin >> arrq[c];

        for (int i = 0; i < c; i++)
        {
            if (arrc[c] == arrc[i])
            {
                cout << "\n\n Duplicate Product Code. Try AGAIN!!!";
                goto retry;
            }
        }
        c++;
        cout << "\n\n Do you want to buy another product? (y/n): ";
        cin >> choice;

    retry:
        continue;
    } while (choice == 'y');

    cout << "\n\n\t\t\t__________________INVOICE_________________\n";
    cout << "Customer Name: " << customerName << "\n";  // Display customer name in the invoice
    cout << "Product No   Product Name            Quantity   Price     Amount      Discounted Amount\n";
    cout << "________________________________________________________________________________________\n";

    for (int i = 0; i < c; i++)
    {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == arrc[i])
            {
                amount = price * arrq[i];
                dis = amount - (amount * dis / 100); // Apply individual product discount
                total += dis;
                cout << setw(12) << left << pcode
                     << setw(25) << left << pname
                     << setw(10) << left << arrq[i]
                     << setw(10) << left << price
                     << setw(12) << left << amount
                     << setw(10) << left << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }

    // Check if the total is greater than or equal to 500
    if (total >= 500)
    {
        float discount = total * 0.10; // 10% discount
        total -= discount;
        cout << "_______________________________________________\n";
        cout << "Total after 10% discount: " << total << "\n";
    }

    cout << "________________________________________________________________________________________\n";
    cout << "Total Amount: " << total << "\n";

    // Ask if the user wants to save the invoice
    char saveChoice;
    cout << "\nDo you want to save this invoice? (y/n): ";
    cin >> saveChoice;

    if (saveChoice == 'y' || saveChoice == 'Y')
    {
        ofstream invoiceFile;
        invoiceFile.open("invoice.txt", ios::app);  // Open invoice.txt in append mode to keep adding invoices

        if (invoiceFile.is_open())
        {
            invoiceFile << "\n\n\t\t\t__________________INVOICE_________________\n";
            invoiceFile << "Customer Name: " << customerName << "\n";  // Save the customer name in the invoice file
            invoiceFile << "Product No   Product Name            Quantity   Price     Amount      Discounted Amount\n";
            invoiceFile << "________________________________________________________________________________________\n";

            for (int i = 0; i < c; i++)
            {
                data.open("database.txt", ios::in);
                data >> pcode >> pname >> price >> dis;
                while (!data.eof())
                {
                    if (pcode == arrc[i])
                    {
                        amount = price * arrq[i];
                        dis = amount - (amount * dis / 100); // Apply individual product discount
                        invoiceFile << setw(12) << left << pcode
                                    << setw(25) << left << pname
                                    << setw(10) << left << arrq[i]
                                    << setw(10) << left << price
                                    << setw(12) << left << amount
                                    << setw(10) << left << dis << "\n";
                    }
                    data >> pcode >> pname >> price >> dis;
                }
                data.close();
            }

            // Apply total discount if applicable
            if (total >= 500)
            {
                float discount = total * 0.10; // 10% discount
                total -= discount;
                invoiceFile << "_______________________________________________\n";
                invoiceFile << "Total after 10% discount: " << total << "\n";
            }

            invoiceFile << "________________________________________________________________________________________\n";
            invoiceFile << "Total Amount: " << total << "\n";
            invoiceFile.close();

            cout << "\nInvoice saved to 'invoice.txt'.\n";
        }
        else
        {
            cout << "\nError saving the invoice.\n";
        }
    }
    else
    {
        cout << "\nInvoice not saved.\n";
    }
}


int main() 
{
	system("color 2");
    shopping obj;
    obj.menu();
    return 0;
}

