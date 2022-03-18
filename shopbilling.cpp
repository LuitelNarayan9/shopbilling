/*C++ Program For Retail Management System*/
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <iomanip>

using namespace std;


struct customer
{
    string Name, Id, Pass, Add;
    float Price;
};
struct product
{
    string PName, PId;
    int quantity;

    double Price;
};
class RMS
{
   
    int Total_users = 0;

    customer cs;
    product pd;

public:
    int login();
    void registr();
    void buy();
    void menu();

    void administrator();
    void buyer();
    void displayproduct();
    void displayusers();
    void profile();
    int  getTotal();
    void generatebill(string, int);
};

// main module...

int main()
{
    int choice;
    while (1)
    {
        cout << "\t\t\n===================================================================\n";
        cout << "\t\t\tRetail Management System\n";
        cout << "-------------------------------------------------------------------\n";       
        cout << "\t\t| 1. ADMINISTRATOR     |\n";
        cout << "\t\t| 2. BUYER             |\n";
        cout << "\t\t| 3. EXIT              |\n";
        cout << "\t\t\n===================================================================\n";
        cout << "\n\t\tENTER CHOICE: ";
        cin >> choice;
        RMS rms;
        rms.getTotal();
        switch (choice)
        {
        case 1:
            system("cls");
            rms.administrator();
            break;
        case 2:
            system("cls");
            rms.buyer();
            break;
        case 3:
            exit(0);
            break;
        }
    }
    return 0;
}

//getting total USERS

int RMS::getTotal(){
    ifstream getusr("users.txt");
    string line;
    int counter = 0;
    if(getusr.is_open()){
        while(getline(getusr, line)){
            counter++;
        }
    Total_users = counter;
    }
    return counter;
}



// display all product
void RMS::displayproduct()
{
    int counter = 0;
    ifstream prod("product.txt");
    // string i,n;
    // double p;
    cout << "\t\t\n===================================================================\n";
    cout << "\t\t\t\tPRODUCT MENU\n";
    cout << "\t\t\n===================================================================\n\n\n";
    cout << "No. " << setw(10) << " Product ID " << setw(20) << " Product Name " << setw(30) << " Price " << setw(2) << endl;
    cout << "\n-------------------------------------------------------------------\n";
    if (prod.is_open())
    {
        while (prod >> pd.PId >> pd.PName >> pd.Price)
        {
            cout << counter << setw(10) << pd.PId << setw(20) << pd.PName << setw(30) << pd.Price << endl;
            counter++;
        }
        prod.close();
    }
    else
    {
        cout << "Unable to open File!\n";
    }
}

// display all product
void RMS::buy()
{
    system("cls");
    displayproduct();
    string choice;
    int quant;
    cout << "\t\t_________________________________________________________________\n\n";
    cout << "\n\t\tENTER PRODUCT ID TO BUY: ";
    cin >> choice;
    cout << "\n\t\tHOW MANY SUCH PRODUCT YOU WANT TO BUY: ";
    cin >> quant;
    pd.quantity = quant;
    generatebill(choice, quant);
    cout << "\n___________________________________________________________________\n\n";
}

// generate bill
void RMS::generatebill(string pid, int q)
{
  
    ifstream bill("product.txt");
    string ids, nm;
    double pr;
    if (bill.is_open())
    {
        int found = 0;
        int ii = 0;
        while (bill >> pd.PId >> pd.PName >> pd.Price)
        {

            if (pd.PId == pid)
            {
                ii++;
                found = 1;
                cout << "No." << setw(10) << " Product ID " << setw(20) << " Product Name " << setw(30) << " Price " << setw(2) << endl;
                cout << "\n-------------------------------------------------------------------\n";
                cout << ii + 1 << setw(10) << pd.PId << setw(20) << pd.PName << setw(30) << pd.Price << endl;
                cout << "\n-------------------------------------------------------------------\n\n";
                cout << "\t\tTotal Amount you have to pay is: " << (double)q * pd.Price << "\n";
                cout << "\n-------------------------------------------------------------------\n";
                bill.close();
                break;
            }
        }
        if (found == 0)
        {
            cout << "PLEASE ENTER THE CORRECT PRODUCT ID TO PURCHASE\n";
            cout << "Loading ";
            for (int i = 0; i < 5; i++)
            {
                putchar('.');
                Sleep(1000);
            }
            buy();
        }
    }
    else
    {
        cout << "Unable to Open the File\n";
    }
}



// disply all users
void RMS::displayusers()
{
    system("cls");
    int counter = 0;
    ifstream usr("users.txt");
    // string i,n;
    // double p;
    cout << "\t\t\n===================================================================\n";
    cout << "\t\t\t\tALL USERS\n";
    cout << "\t\t\n===================================================================\n\n\n";
    cout << "No." << setw(10) << "USER NAME" << setw(30) << "USER ID" << setw(20) << "USER ADDRESS" << setw(2) << endl;
    cout << "-------------------------------------------------------------------\n";
    if (usr.is_open())
    {
        while (usr >> cs.Name >> cs.Id >> cs.Pass >> cs.Add)
        {
            cout << counter << setw(10) << cs.Name << setw(30) << cs.Id << setw(20) << cs.Add << endl;
            counter++;
        }
        usr.close();
    }
    else
    {
        cout << "Unable to open File!\n";
    }
}

// user and admin registration from file
void RMS::registr()
{
    system("cls");
    ofstream fout("users.txt", ios::app);
    if (!fout.is_open())
    {
        cout << "Unable to Open File" << endl;
    }
    else
    {
        cout << "\n@@@@@@@@@@@@@@@@ REGISTRATION MENU @@@@@@@@@@@@@@@@@@\n";
        cout << "\t\tEnter Name: ";
        cin.get();
        getline(cin, cs.Name);
        cout << "\t\tEnter ID: ";
        cin >> cs.Id;
        cout << "\t\tEnter Password: ";
        cin >> cs.Pass;
        cout << "\t\tEnter Address: ";
        cin.get();
        getline(cin, cs.Add);
        fout << cs.Name << " " << cs.Id << " " << cs.Pass << " " << cs.Add << endl;
        system("cls");
        cout << cs.Name << " Registered with Details\n";
        fout.close();
        Total_users += 1;
    }
}

//  user and admin login from file
int RMS::login()
{
    system("cls");
    cout << "\n@@@@@@@@@@@@@@@@ LOGIN MENU @@@@@@@@@@@@@@@@@@\n";
    string name, id, pwd, add, n, i, p, a;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    int found = 0;
    cout << "\n\t\tEnter Password: ";
    cin >> pwd;
    ifstream inputfile("users.txt");
    while (inputfile >> n >> i >> p >> a)
    {
        if ((id == i) && (pwd == p))
        {
            cs.Name = n;
            cs.Id = i;
            cs.Pass = p;
            cs.Add = a;
            inputfile.close();
            return 1;
        }
    }

    return 0;
}

// admin module only

void RMS::administrator()
{
    cout << "\n@@@@@@@@@@@@@@@@ ADMIN LOGIN MENU @@@@@@@@@@@@@@@@@@\n";
    string id, pwd;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    cout << "\n\t\tEnter Password: ";
    cin >> pwd;
    if (id == "admin-1" && pwd == "admin-1")
    {
        int choice;
        while (1)
        {
            cout << "\t\t\n===================================================================\n";
            cout << "\t\t\tADMINISTRATOR MENU\n";
            cout << "-------------------------------------------------------------------\n";
            cout << "\t\t| 1. DISPLAY PRODUCT    |\n";
            cout << "\t\t| 2. DISPLAY USERS      |\n";
            cout << "\t\t| 3. LOGOUT             |\n";
            cout << "\t\t\n===================================================================\n";
            cout<< "Total Uses in the Databases : "<<Total_users<<endl;
            cout << "\n\t\tENTER CHOICE: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                system("cls");
                displayproduct();
                break;
            case 2:
                system("cls");
                displayusers();
                break;
            case 3:
                system("cls");
                main();
                break;
            default:
                cout << "\nERROR: INVALID OPTION\n";
                break;
            }
        }
    }
    else
    {
        cout << "INVALID ADMIN CREDANTIALS\n";
        administrator();
    }
}

// user menu options

void RMS::menu()
{
    int choice;
    while (1)
    {
        cout << "\t\t\n===================================================================\n";
        cout << "\t\t\tWELCOME " << (cs.Name) << "\n";
        cout << "-------------------------------------------------------------------\n";
        cout << "\t\t| 1. BUY           |\n";
        cout << "\t\t| 2. PROFILE       |\n";
        cout << "\t\t| 3. LOGOUT        |\n";
        cout << "\t\t\n===================================================================\n";
        cout << "\n\t\tENTER CHOICE: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            buy();
            break;
        case 2:
            system("cls");
            profile();
            break;
        case 3:
            system("cls");
            main();
            break;
        default:
            cout << "\nERROR: INVALID OPTION\n";
            break;
        }
    }
}

// profile of user
void RMS::profile()
{
    cout << "\t\t\n===================================================================\n";
    cout << "\t\t\tPROFILE\n";
    cout << "-------------------------------------------------------------------\n";
    cout << "| NAME " << setw(20) << " ID " << setw(20) << " PASSWORD " << setw(20) << " ADDRESS " << setw(1) << "|\n";
    cout << " " << cs.Name << setw(20) << cs.Id << setw(20) << cs.Pass << setw(20) << cs.Add << setw(1) << endl;
    cout << "\t\t\n===================================================================\n";
}

// user first screen

void RMS::buyer()
{
    int choice;
    while (1)
    {
        cout << "\t\t\n===================================================================\n";
        cout << "\t\t\tBUYER MENU\n";
        cout << "-------------------------------------------------------------------\n";
        cout << "\t\t| 1. LOGIN         |\n";
        cout << "\t\t| 2. REGISTER      |\n";
        cout << "\t\t| 3. MAIN MENU     |\n";
        cout << "\t\t\n===================================================================\n";
        cout << "\n\t\tENTER CHOICE: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            if (login() == 1)
                menu();
            else
                cout << "\nINVALID USER CREDANTIALS\n";
            // system("cls");
            // buyer();
            break;
        case 2:
            system("cls");
            registr();
            break;

        case 3:
            system("cls");
            main();
            break;

        default:
            cout << "\nERROR: INVALID OPTION\n";
            break;
        }
    }
}