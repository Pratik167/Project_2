#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <limits>
#include <ctime>
#include<stdio.h>
#include<string>
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
    void showAllInvoices();
    void searchInvoice();
    int getLastInvoiceNumber();
    void changepass();
    friend class permission;
};
int getNumberInput()
{
	int x;
	 while (true) 
	 {
        cin>>x;

        // Check if input is a valid number
        if (cin.fail()) 
		{
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            cout << "Invalid input. Please enter a number: ";
        } else {
        	return x;
            break;  // Valid number entered
        }
    }
}
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
    cout << "\t\t\t\tSIGN UP PAGE\n";
    
    if (accountExists()) 
    {
        cout << "An account already exists. Redirecting to login...\n";
        for (int q = 0; q < 3; q++) 
        {
            Sleep(100);printf(".");Sleep(100);printf(".");Sleep(100);printf(".");Sleep(200);printf("\b \b");printf("\b \b");printf("\b \b");
        }
        
        if (logIn() == 1) 
        {
            cout << "Login successful!\n";
            shopping obj;  // Create shopping object to access loggedInMenu
            obj.loggedInMenu();  // Call loggedInMenu after successful login
        } 
        else 
        {
            cout << "Invalid username or password.\n";
        }
        return;  // End the signUp function and prevent further execution
    }
	int pin;
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cin.ignore();  // To ignore the newline character after the username input
    password = getPassword();
	cout<<"Enter a pin which can be used incase you forget the password";
	pin= getNumberInput();
    ofstream pinfile("pin.txt",ios::out);
    if(pinfile.is_open())
    {
    	pinfile<<pin;
    	pinfile.close();
	}
    ofstream file("users.txt", ios::app);
    if (file.is_open()) 
    {
        file << username << " " << password<<endl;
        file.close();
        cout << "Sign up successful!\n";
        for (int q = 0; q < 3; q++) 
        {
            Sleep(100);printf(".");Sleep(100);printf(".");Sleep(100);printf(".");Sleep(200);printf("\b \b");printf("\b \b");printf("\b \b");
        }
        shopping obj;
        obj.loggedInMenu();
    } 
    else 
    {
        cout << "Error opening file.\n";
    }
    
}
	void changepass() {
	system("cls");
	cout<<"Account recovery"<<endl;
    fstream file("users.txt");
    string storedusername, storedpass, username, newpass;
    bool userFound = false;

    if (!file.is_open()) {
        cout << "Error opening files!" << endl;
        return;
    }

    cout << "Enter your username: ";
    cin >> username;

    while (file >> storedusername >> storedpass) {
        if (username == storedusername) {
        	file.close();
        	fstream file("users.txt",ios::out);
            newpass=getPassword();  // Replace with getPassword() if needed
            file << storedusername << " " << newpass << endl;
            userFound = true;
        } 
    }
    file.close();
    if(userFound)
    {
    	cout<<"Password changed succesfully";
//	   	logIn();
	}
    
}

    int logIn() 
	{
		system("cls");
		cout<<"\t\t\t\t\tLOGIN PAGE\n";
        string username, password, storedUser, storedPass;
        int attempts = 3;
        
        ifstream file("users.txt");
    if (!file || file.peek() == ifstream::traits_type::eof()) 
    {
        cout << "No users found. Please sign up first.\n";
        file.close();
        for (int q = 0; q < 3; q++) 
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
        signUp();
        return 0; // No users, cannot log in
    }

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
            if(attempts==0)
            {
            
            	int recoverpin,storedpin,check=0;
            	cout<<"Enter pin to recoverr id:";
            	recoverpin= getNumberInput();
            	ifstream file("pin.txt");
            	if (file.is_open()) 
				{
               		while (file >> storedpin ) 
					{
                    	if (storedpin==recoverpin) 
						{
                        	file.close();
                       		changepass();
                       		check=1;
                   		}
                	}
                	if(check==0)
                	{
                		cout<<"Incorrect pin";
					}
					else
					{
						if(logIn()==1)
						{
							return 1;
						}
					}
                	file.close();
            	}
				else
				{
					cout<<"Error opening the file";
				}	 
            	
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
int getlastInvoiceno()
{
	int x;
	ifstream num;
	num.open("invoicenum.txt");
	num>>x;
	num.close();
	return x+1;	
}
void saveNumber(int number) {
    std::ofstream file("invoicenum.txt");  // Open file in write mode, overwriting existing content
    if (file.is_open()) {
        file << number;  // Write the number to the file
        file.close();    // Close the file
       
    } else {
        std::cout << "Unable to open file." << std::endl;
    }
}
void shopping :: admin()
{
	system("cls");
	m:
	int choice;
	cout<<"\n\n\n\t\t\tADMIN SECTION";
	cout<<"\n\n\n\t\t1) Add the product";
	cout<<"\n\n\n\t\t2) Modify the product";
	cout<<"\n\n\n\t\t3) Delete the product";
	cout<<"\n\n\n\t\t4) Back To Main Menu";
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
    system("cls");
    int choice;
    cout << "\t\t\t  Buyer  \n";
    cout << "__________________________________________\n";
    cout << "1) Buy Product\n";
    cout << "2) Show All Invoices\n";
    cout << "3) Search Invoice\n";
    cout << "4) Go Back\n";
    cout<<  "5) Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
    	showAllInvoices();
    	break;
    case 3:
        searchInvoice();
        break;
    case 4:
        return;
    case 5:
    cout<<"\n\nThanks";
    exit(0);
    default:
        cout << "Invalid choice! Try again.";
        goto m;
    }
}
void shopping::showAllInvoices()
{
    system("cls");
    ifstream invoiceFile("invoice.txt");
    if (!invoiceFile)
    {
        cout << "\nNo invoices found!\n";
        return;
    }
    string line;
    cout << "\n\t\t All Invoices \n";
    cout << "----------------------------------------\n";
    while (getline(invoiceFile, line))
    {
        cout << line << "\n";
    }
    invoiceFile.close();
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
	pcode=getNumberInput();
	cout<<"\n\n\t Name of the product:";
	cin>>pname;
	erprice:
	cout<<"\n\n\t Price of the product:";
	price=getNumberInput();
	cout<<"\n\n\t Discount on Product:";
	dis=getNumberInput();
	if(dis>=price)
	{
		cout<<"discount cannot be greater than price";
		goto erprice;
	}
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
	pkey=getNumberInput();
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
				c=getNumberInput();
				cout<<"\n\t\t Name of the product:";
				cin>>n;
				erpr:
				cout<<"\n\t\t Price:";
				p=getNumberInput();
				cout<<"\n\t\t Discount:";
				d=getNumberInput();
				if(dis>=price)
				{
					cout<<"discount cannot be greater than price";
					goto erpr;
				}
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
	pkey=getNumberInput();
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
void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|____________________MENU_________________________\n";
    cout << "| ProNo    Name                      Price\n";
    cout << "|_____________________________________________\n";
    if (!data) {
        cout << "No products available.\n";
        return;
    }

    while (data >> pcode >> pname >> price >> dis) {
        cout << setw(8) << left << pcode
             << setw(25) << left << pname
             << setw(10) << left << price << "\n";
    }
    data.close();
}

void shopping::receipt() {
    system("cls");
    fstream data;
    int arrc[100]; // array of product codes
    int arrq[100]; // array of quantities
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;
    static int invoiceNumber = getlastInvoiceno() ; // Static variable for unique invoice numbers

    string customerName;  // Variable to store customer name
    cout << "\n\n\t\t\t\t RECEIPT";
    cout << "\n\n Enter Customer's Name: ";
    cin.ignore();  // Clear the input buffer
    getline(cin, customerName);  // Get the full name including spaces

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n No products available!";
        return;
    }
    data.close();
    list();
    cout << "\n ________________________________________\n";
    cout << "                Place Order              \n";
    cout << "_________________________________________\n";

    do {
        cout << "\n\n Enter Product Code: ";
        arrc[c] = getNumberInput();

        bool productFound = false;
        data.open("database.txt", ios::in);
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == arrc[c]) {
                productFound = true;
                break;
            }
        }
        data.close();

        if (!productFound) {
            cout << "\n\n Product code not found. Try AGAIN!!!";
            continue;
        }
		flag:
        cout << "\n\n Enter the Product Quantity: ";
        arrq[c] = getNumberInput();
		if(arrq[c]==0)
		{
			cout<<"Quantity cannot be 0";
			goto flag;
		}
        for (int i = 0; i < c; i++) {
            if (arrc[c] == arrc[i]) {
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
	time_t timestamp =time(&timestamp);
	struct tm datetime =*localtime(&timestamp);
    cout << "\n\n\t\t\t__________________INVOICE_________________\n";
    cout <<ctime(&timestamp)<<endl;
    cout << "Invoice Number: " << invoiceNumber << "\n";
    cout << "Customer Name: " << customerName << "\n";
    cout << "Product No   Product Name            Quantity   Price     Amount      Discounted Amount\n";
    cout << "________________________________________________________________________________________\n";

    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                dis = amount - (amount * dis / 100);
                total += dis;
                cout << setw(12) << left << pcode
                     << setw(25) << left << pname
                     << setw(10) << left << arrq[i]
                     << setw(10) << left << price
                     << setw(12) << left << amount
                     << setw(10) << left << dis << "\n";
            }
        }
        data.close();
    }

    float VAT = total * 0.13;
    float serviceCharge = total * 0.10;
    float grandTotal = total + VAT + serviceCharge;
	float discount;
    cout << "________________________________________________________________________________________\n";
    cout << "Total Amount: " << total << "\n";
    if (datetime.tm_hour > 12 && datetime.tm_hour < 15) 
	{
   		discount = total * 0.02;
    	cout << "_______________________________________________\n";
    	cout << "Happy Hour Discount (2%): " << discount << "\n";
    	grandTotal -= discount;  // Apply discount to total before VAT & Service Charge
	}
    cout << "VAT (13%): " << VAT << "\n";
    cout << "Service Charge (10%): " << serviceCharge << "\n";
    cout << "Grand Total: " << grandTotal << "\n";

    char saveChoice;
    cout << "\nDo you want to save this invoice? (y/n): ";
    cin >> saveChoice;

    if (saveChoice == 'y' || saveChoice == 'Y') {
        ofstream invoiceFile("invoice.txt", ios::app);
        if (invoiceFile.is_open()) {
            invoiceFile << "\n\n\t\t\t__________________INVOICE_________________\n";
            invoiceFile << "Invoice Number: " << invoiceNumber << "\n";
            saveNumber(invoiceNumber);
            invoiceFile << "Customer Name: " << customerName << "\n";
            invoiceFile << "Product No   Product Name            Quantity   Price     Amount      Discounted Amount\n";
            invoiceFile << "________________________________________________________________________________________\n";

            for (int i = 0; i < c; i++) {
                data.open("database.txt", ios::in);
                while (data >> pcode >> pname >> price >> dis) {
                    if (pcode == arrc[i]) {
                        amount = price * arrq[i];
                        dis = amount - (amount * dis / 100);
                        invoiceFile << setw(12) << left << pcode
                                    << setw(25) << left << pname
                                    << setw(10) << left << arrq[i]
                                    << setw(10) << left << price
                                    << setw(12) << left << amount
                                    << setw(10) << left << dis << "\n";
                    }
                }
                data.close();
            }

            invoiceFile << "________________________________________________________________________________________\n";
            invoiceFile << "Total Amount: " << total << "\n";
              if (datetime.tm_hour > 12 && datetime.tm_hour < 15) 
				{
    				discount = total * 0.02;
    				total -= discount;  // Fix: Apply the discount before saving
   				 	invoiceFile << "Happy Hour Discount (2%): " << discount << "\n";
				}	
            invoiceFile << "VAT (13%): " << VAT << "\n";
            invoiceFile << "Service Charge (10%): " << serviceCharge << "\n";
            invoiceFile << "Grand Total: " << grandTotal << "\n";
            invoiceFile.close();

            cout << "\nInvoice saved to 'invoice.txt'.\n";
        } else {
            cout << "\nError saving the invoice.\n";
        }
    } else {
        cout << "\nInvoice not saved.\n";
    }

    invoiceNumber++; // Increment invoice number for the next receipt
}

void shopping::searchInvoice() {
    system("cls");
    ifstream invoiceFile("invoice.txt");
    if (!invoiceFile.is_open()) {
        cout << "\nNo invoices found!\n";
        return;
    }

    string keyword;
    cout << "Enter Invoice Number to search: ";
    cin >> keyword;
	cin.ignore();
    string line, invoiceContent;
    bool found = false, invoiceStart = false;

    cout << "\n\t\tSearch Results\n";
    cout << "----------------------------------------\n";

    while (getline(invoiceFile, line)) {
        if (line.find("Invoice Number: ") != string::npos) {
            if (invoiceStart && invoiceContent.find("Invoice Number: " + keyword) != string::npos) {
                found = true;
                cout << invoiceContent << endl;
                cout << "----------------------------------------\n";
            }
            invoiceContent.clear();
            invoiceStart = true;
        }

        if (invoiceStart) {
            invoiceContent += line + "\n";
        }
    }

    if (invoiceStart && invoiceContent.find("Invoice Number: " + keyword) != string::npos) {
        found = true;
        cout << invoiceContent << endl;
        cout << "----------------------------------------\n";
    }

    if (!found) {
        cout << "\nNo matching invoice found for the Invoice Number: " << keyword << endl;
    }

    invoiceFile.close();
}

int main() 
{

    shopping obj;
    obj.menu();
    return 0;
}

