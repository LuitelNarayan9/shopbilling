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
    int getTotal();
    void generatebill(string, int);
    void showmenu();
    void showmenu1();
    void adduser();
    void searchuser();
    void updateuser();
    void deleteuser();
    void addproduct();
    void searchproduct();
    void updateproduct();
    void deleteproduct();
    void showproduct();
};

// main module...

int main()
{
    int choice;
    while (1)
    {
        system("color F1");
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

// show product information
void RMS::showproduct()
{
    cout << "\t\t\n===================================================================\n";
    cout << "\t\t\tPRODUCT INFORMATION\n";
    cout << "-------------------------------------------------------------------\n";
    cout << setw(5) << "| P_ID " << setw(20) << " P_NAME " << setw(20) << " PRICE " << setw(10) << "|\n";
    cout << setw(5) << " " << pd.PId << setw(20) << pd.PName << setw(20) << pd.Price << setw(10) << endl;
    cout << "\t\t\n===================================================================\n";
}

// showing products menu to adminstrator

void RMS::showmenu1()
{

    int choice;
    while (1)
    {

        cout << "\t\t\n===================================================================\n";
        cout << "\t\t\tADMIN CONTROLS\n";
        cout << "-------------------------------------------------------------------\n";
        cout << "\t\t| 1. ADD PRODUCT                |\n";
        cout << "\t\t| 2. SEARCH PRODUCT             |\n";
        cout << "\t\t| 3. UPDATE PRODUCT             |\n";
        cout << "\t\t| 4. DELETE PRODUCT             |\n";
        cout << "\t\t| 5. DISPLAY ALL PRODUCT        |\n";
        cout << "\t\t| 6. BACK                       |\n";
        cout << "\t\t\n===================================================================\n";
        cout << "\n\t\tENTER CHOICE: ";
        cin >> choice;
        RMS rms;
        rms.getTotal();
        switch (choice)
        {
        case 1:
            addproduct();
            break;
        case 2:
            searchproduct();
            break;
        case 3:
            updateproduct();
            break;
        case 4:
            deleteproduct();
            break;
        case 5:
            displayproduct();
            break;
        case 6:
            administrator();
            break;
        default:
            cout << "Enter valid options\n";
            break;
        }
    }
}

// display product

void RMS::displayproduct()
{

    system("cls");
    int counter = 0;
    ifstream pdt("product.txt");
    cout << "\t\t\n===================================================================\n";
    cout << "\t\t\t\tALL PRODUCTS\n";
    cout << "\t\t\n===================================================================\n\n\n";
    cout << setw(5) << "No." << setw(10) << "P_ID" << setw(30) << "P_NAME" << setw(20) << "P_PRICE" << setw(10) << endl;
    cout << "-------------------------------------------------------------------\n";
    if (pdt.is_open())
    {
        while (pdt >> pd.PId >> pd.PName >> pd.Price)
        {
            counter++;
            cout << setw(5) << counter << setw(10) << pd.PId << setw(30) << pd.PName << setw(20) << pd.Price << setw(10) << endl;
        }
        cout << endl
             << "Total Product: " << counter << endl;
        pdt.close();
    }
    else
    {
        cout << "Unable to open File!\n";
    }
}

// add product by administrator

void RMS::addproduct()
{

    ofstream fout("product.txt", ios::app);
    if (!fout.is_open())
    {
        cout << "Unable to Open File" << endl;
    }
    else
    {
        cout << "\n@@@@@@@@@@@@@@@@ ADD NEW PRODUCT @@@@@@@@@@@@@@@@@@\n";
        cout << "\t\tEnter Product ID: ";
        cin >> pd.PId;
        cout << "\t\tEnter Product Name: ";
        cin >> pd.PName;
        cout << "\t\tEnter Price: ";
        cin >> pd.Price;
        fout << pd.PId << " " << pd.PName << " " << pd.Price << endl;
        system("cls");
        cout << cs.Name << " Product added successfully\n";
        fout.close();
    }
}

// product search by admin
void RMS::searchproduct()
{

    cout << "\n@@@@@@@@@@@@@@@@ SEARCH PRODUCT @@@@@@@@@@@@@@@@@@\n";
    string name, id, i;
    double p;
    cout << "\n\t\tEnter ID: ";
    cin >> i;
    int found = 0;

    ifstream inputfile("product.txt");
    while (inputfile >> id >> name >> p)
    {
        if ((id == i))
        {
            pd.PId = id;
            pd.PName = name;
            pd.Price = p;
            showproduct();
            found = 1;
            inputfile.close();
            break;
        }
    }

    if (found == 0)
        cout << "Product Not Found in Database" << endl;
}

// updating product information

void RMS::updateproduct()
{

    cout << "\n@@@@@@@@@@@@@@@@ UPDATE PRODUT @@@@@@@@@@@@@@@@@@\n";
    string name, id, i, nn, ni, np;
    double p;
    cout << "\n\t\tEnter ID: ";
    cin >> i;
    int found = 0;
    ifstream inputfile("product.txt");
    ofstream fout("new.txt");
    if (!inputfile.is_open())
    {
        cout << "open the file first\n";
        return;
    }

    while (inputfile >> id >> name >> p)
    {
        if ((id != i))
        {
            fout << id << " " << name << " " << p << endl;
        }
        else
        {
            pd.PId = id;
            pd.PName = name;
            pd.Price = p;
            showproduct();
            found = 1;
            cout << "\nID is same ...\n";
            cout << "Enter new Name: ";
            cin >> pd.PName;
            cout << "Enter new Price: ";
            cin >> pd.Price;
            fout << pd.PId << " " << pd.PName << " " << pd.Price << endl;
        }
    }
    fout.close();
    inputfile.close();
    remove("product.txt");
    rename("new.txt", "product.txt");
    if(found == 0)
    cout<<"Id didn't exist"<<endl;
    else
    cout<<"Record Updated"<<endl;
}

// deleting product information

void RMS::deleteproduct()
{

    cout << "\n@@@@@@@@@@@@@@@@ DELETE PRODUCT @@@@@@@@@@@@@@@@@@\n";
    string name, id, i;
    double p;
    cout << "\n\t\tEnter ID: ";
    cin >> i;
    int found = 0;

    ifstream inputfile("product.txt");
    ofstream fout("new.txt");
    if (!fout.is_open())
        fout.open("new.txt");
    while (inputfile >> id >> name >> p)
    {
        if ((id == i))
        {

            pd.PId = id;
            pd.PName = name;
            pd.Price = p;
            showproduct();
            cout << "Deleting ... " << pd.PName << endl;
            found = 1;
        }
        else
        {
            fout << id << " " << name << " " << p << endl;
        }
    }
    fout.close();
    inputfile.close();
    remove("product.txt");
    rename("new.txt", "product.txt");
    if (found == 0)
        cout << "\nProduct Not Found in Database" << endl;
    if (found == 1)
    {
        cout << "\nProduct Removed from Database" << endl;
    }
}

// showing users menus to administrator()

void RMS::showmenu()
{

    int choice;
    while (1)
    {

        cout << "\t\t\n===================================================================\n";
        cout << "\t\t\tADMIN CONTROLS\n";
        cout << "-------------------------------------------------------------------\n";
        cout << "\t\t| 1. ADD USER                |\n";
        cout << "\t\t| 2. SEARCH USER             |\n";
        cout << "\t\t| 3. UPDATE USER             |\n";
        cout << "\t\t| 4. DELETE USER             |\n";
        cout << "\t\t| 5. DISPLAY ALL USER        |\n";
        cout << "\t\t| 6. BACK                    |\n";
        cout << "\t\t\n===================================================================\n";
        cout << "\n\t\tENTER CHOICE: ";
        cin >> choice;
        RMS rms;
        rms.getTotal();
        switch (choice)
        {
        case 1:
            adduser();
            break;
        case 2:
            searchuser();
            break;
        case 3:
            updateuser();
            break;
        case 4:
            deleteuser();
            break;
        case 5:
            displayusers();
            break;
        case 6:
            administrator();
            break;
        default:
            cout << "Enter valid options\n";
            break;
        }
    }
}

// admin is adding the user...

void RMS ::adduser()
{
    registr();
}

// admin searchuser code

void RMS ::searchuser()
{

    cout << "\n@@@@@@@@@@@@@@@@ SEARCH USER @@@@@@@@@@@@@@@@@@\n";
    string name, id, pwd, add, n, i, p, a;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    int found = 0;

    ifstream inputfile("users.txt");
    if (!inputfile.is_open())
    {
        inputfile.close();
        inputfile.open("users.txt");
    }
    while (inputfile >> n >> i >> p >> a)
    {
        if ((id == i))
        {
            cs.Name = n;
            cs.Id = i;
            cs.Pass = p;
            cs.Add = a;
            profile();
            found = 1;
            inputfile.close();
            break;
        }
    }
    inputfile.close();
    if (found == 0)
        cout << "User Not Found in Database" << endl;
}

// update user by admin

void RMS::updateuser()
{

    cout << "\n@@@@@@@@@@@@@@@@ UPDATE USER @@@@@@@@@@@@@@@@@@\n";
    string id, n, i, p, a;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    int found = 0;

    ifstream inputfile("users.txt");
    ofstream fout("new.txt");
    if (!inputfile.is_open()){
        cout<<"please open the file first\n";
        return;
    }
    while (inputfile >> n >> i >> p >> a)
    {
        if ((id != i))
        {
           fout << n << " " << i << " " << p << " " << a << endl; 
        }
        else{
            cs.Name = n;
            cs.Id = i;
            cs.Pass = p;
            cs.Add = a;
            profile();
            found = 1;
            cout << "Enter new Name: ";
            cin >> cs.Name;
            cout << "\nID is same ... \n";

            cout << "Enter new Password: ";
            cin >> cs.Pass;
            cout << "Enter new Address: ";
            cin >> cs.Add;
            fout<<cs.Name<<" "<<cs.Id<<" "<<cs.Pass<<" "<<cs.Add<<endl;
        }
        
    }
    fout.close();
    inputfile.close();
    remove("users.txt");
    rename("new.txt", "users.txt");
    if (found == 0)
        cout << "\nUser Not Found in Database" << endl;
    else
        cout << "\nUser Updated in Database" << endl;
}

// deleting the user by administrator

void RMS::deleteuser()
{

    cout << "\n@@@@@@@@@@@@@@@@ DELETE USER @@@@@@@@@@@@@@@@@@\n";
    string id, n, i, p, a;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    int found = 0;
    ifstream inputfile("users.txt");
    ofstream fout("new.txt");
    if (!fout.is_open())
        fout.open("new.txt");
    while (inputfile >> n >> i >> p >> a)
    {
        if ((id == i))
        {
            cs.Name = n;
            cs.Id = i;
            cs.Pass = p;
            cs.Add = a;
            profile();
            cout << "Deleting ..." << cs.Name << endl;

            found = 1;
        }
        else
        {
            fout << n << " " << i << " " << p << " " << a << endl;
        }
    }
    fout.close();
    inputfile.close();
    remove("users.txt");
    rename("new.txt", "users.txt");
    if (found == 0)
        cout << "\nUser Not Found in Database" << endl;
    if (found == 1)
        cout << "\nUser Deleted from Database" << endl;
}

// getting total USERS

int RMS::getTotal()
{
    ifstream getusr("users.txt");
    string line;
    int counter = 0;
    if (getusr.is_open())
    {
        while (getline(getusr, line))
        {
            counter++;
        }
        Total_users = counter;
    }

    getusr.close();

    return counter;
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
                cout << setw(5) << "No." << setw(10) << " Product ID " << setw(20) << " Product Name " << setw(30) << " Price " << setw(10) << endl;
                cout << "\n-------------------------------------------------------------------\n";
                cout << setw(5) << ii + 1 << setw(10) << pd.PId << setw(20) << pd.PName << setw(30) << pd.Price << setw(10) << endl;
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
    cout << setw(5) << "No." << setw(10) << "USER NAME" << setw(30) << "USER ID" << setw(20) << "USER PASSWORD" << setw(30)<<"USER ADDRESS" << setw(10) << endl;
    cout << "-------------------------------------------------------------------\n";
    if (usr.is_open())
    {
        while (usr >> cs.Name >> cs.Id >> cs.Pass >> cs.Add)
        {
            cout << setw(5) << counter << setw(10) << cs.Name << setw(30) << cs.Id << setw(20) <<cs.Pass << setw(30) << cs.Add << setw(10) << endl;
            counter++;
        }

        cout << endl
             << "Total users: " << counter << endl;
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
        cout << "Unable to Open File but trying...." << endl;
        fout.close();
        fout.open("users.txt", ios::app);
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
        cout << "Thank you " << cs.Name << " Now you can Login withh your ID and Password" << endl;
        fout.close();
        Total_users += 1;
    }
}

//  user and admin login from file
int RMS::login()
{
    system("cls");
    cout << "\n@@@@@@@@@@@@@@@@ LOGIN MENU @@@@@@@@@@@@@@@@@@\n";
    string id, pwd, add, n, i, p, a;
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
    static string id, pwd;
    static int chk = 0;
    if (chk == 1)
            goto here;
    cout << "\n\t\tEnter ID: ";
    cin >> id;
    cout << "\n\t\tEnter Password: ";
    cin >> pwd;
    chk = 1;

    if (id == "admin-1" && pwd == "admin-1")
    {
    here:
        cout << "\n\n\t\t\tLoading ";
        for (int i = 0; i < 4; i++)
        {
            putchar('.');
            Sleep(500);
        }
        system("cls");
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
            cout << "Total Users in the Databases : " << Total_users << endl;
            cout << "\n\t\tENTER CHOICE: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                system("cls");
                displayproduct();
                showmenu1();
                break;
            case 2:
                system("cls");
                displayusers();
                showmenu();
                break;
            case 3:
                system("cls");
                chk--;
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
    cout << setw(5) << " " << cs.Name << setw(20) << cs.Id << setw(20) << cs.Pass << setw(20) << cs.Add << setw(1) << endl;
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
            {
                cout << "\t\t\tLoading ";
                for (int i = 0; i < 5; i++)
                {
                    putchar('.');
                    Sleep(500);
                }
                system("cls");
                menu();
            }
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