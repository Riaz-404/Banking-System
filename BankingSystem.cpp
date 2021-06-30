#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class account
{
private:
    static int CurAccNo;
    string fname;
    string lname;
    int account_no = ++CurAccNo;
    int balance;

public:
    account(){};
    void open_account(string s1, string s2, int bal);
    void set_fname(string s){
        if(s != "")
            fname = s;
    }
    void set_lname(string s){
        if(s != "")
            lname = s;
    }
    void set_balance(int i){
        if(i>=0)
            balance = i;
    }
    string get_fname() { return fname; }
    string get_lname() { return lname; }
    int get_account_no() { return account_no; };
    int get_balance() { return balance; }

    static void setCurAccNo(int No)
    {
        if (No > 0)
        {
            CurAccNo = No;
        }
    }
    void deposit(int amount);
    void withdraw(int amount);
    friend ostream &operator<<(ostream &out, account &a);
    friend istream &operator>>(istream &in, account &a);
    friend ofstream &operator<<(ofstream &o, account &a);
    friend ifstream &operator>>(ifstream &i, account &a);
    ~account();
};
int account::CurAccNo = 0;

bool isEmpty(ifstream &ifs)
{
    return ifs.peek() == ifstream::traits_type::eof();
}

int main()
{
    vector<account> Accounts;

    ofstream ofs("BankingData.txt", ios::app);
    ifstream file("BankingData.txt");

    int checker=1;

    while (!file.eof() && !isEmpty(file))
    {
        account acc;
        file >> acc;
        if(checker==acc.get_account_no()){
            Accounts.push_back(acc);
            checker++;
        }
        else{
            break;
        }
    }

    account::setCurAccNo(Accounts.size());

    
    int choice;

    do
    {
        cout << "***Vongchong Banking System***\n";
        cout << "\n";
        cout << "\t 1. Create an Account\n";
        cout << "\t 2. Check Balance\n";
        cout << "\t 3. Deposit\n";
        cout << "\t 4. Withdraw\n";
        cout << "\t 5. Account Details\n";
        cout << "\t 6. Show All Accounts\n";
        cout << "\t 7. Exit\n";

        cout << "\nSelect your option(1-7): ";
        cin >> choice;

        system("cls");

        switch (choice)
        {
        case 1:
        {
            account ac;
            cin >> ac;
            cout << "Congratulations!!! Your account is created.\n";
            cout << "Your account no is " << ac.get_account_no() << endl;
            Accounts.push_back(ac);
            ofs << ac;
            break;
        }

        case 2:
        {
            cout << "Enter your account no: ";
            int no;
            cin >> no;
            no--;
            cout << "Balance: ";
            cout << Accounts[no].get_balance() << endl;
            break;
        }

        case 3:
        {
            int accno, amount;
            cout << "Enter your account no: ";
            cin >> accno;
            cout << "Enter Deposit ammount: ";
            cin >> amount;
            accno--;
            Accounts[accno].deposit(amount);
            cout << amount << " is deposited to your account.\n";
            break;
        }

        case 4:
        {
            int accno, amount;
            cout << "Enter your account no: ";
            cin >> accno;
            cout << "Enter Withdraw ammount: ";
            cin >> amount;
            accno--;
            Accounts[accno].withdraw(amount);
            cout << amount << " is withdrawn from your account.\n";
            break;
        }

        case 5:
        {
            int n;
            cout << "Enter your account no: ";
            cin >> n;
            cout << endl;
            cout << Accounts[n - 1];
            break;
        }

        case 6:
        {
            for (int i = 0; i < Accounts.size(); i++)
            {
                cout << Accounts[i] << endl;
            }
            break;
        }

        case 7:
            cout << "Thanks for using...";
            break;

        default:
            cout << "Enter any number between 1-7 :(\n";
            break;
        }
        if(choice !=7){
            cout<<endl;
            system("pause");
            system("cls");
        }
        

    } while (choice != 7);


    ofstream outfile;
    outfile.open("BankingData.txt", ios::trunc);
    
    for(int i=0;i<Accounts.size();i++)
    {
        outfile << Accounts[i];
    }
    outfile.close();
}

void account::open_account(string s1, string s2, int bal)
{
    fname = s1;
    lname = s2;
    balance = bal;
}

void account::deposit(int amount)
{
    balance += amount;
}

void account::withdraw(int n)
{
    balance -= n;
}

ostream &operator<<(ostream &out, account &a)
{
    out << "Account no: " << a.get_account_no() << endl;
    out << "Name : " << a.get_fname() << " " << a.get_lname() << endl;
    out << "Balance: " << a.get_balance() << endl;
    return out;
}
istream &operator>>(istream &in, account &a)
{
    string s1, s2;
    int bal;
    cout << "\nEnter your first name: ";
    in >> s1;
    cout << "Enter your last name: ";
    in >> s2;
    cout << "Deposit amount: ";
    in >> bal;
    a.open_account(s1, s2, bal);
    return in;
}

ifstream &operator>>(ifstream &i, account &a)
{
    string first_name, last_name;
    int AccNo, balance;

    i >> first_name >> last_name >> AccNo >> balance;

    a.set_fname(first_name);
    a.set_lname(last_name);
    a.set_balance(balance);
    a.account_no = AccNo;
    
    return i;
}

ofstream &operator<<(ofstream &o, account &a)
{
    o << a.fname << endl;
    o << a.lname << endl;
    o << a.account_no << endl;
    o << a.balance << endl;
    
    return o;
}

account::~account()
{
    
}