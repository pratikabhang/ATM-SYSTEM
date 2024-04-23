#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
using namespace std;

class ATM {
private:
    long int acc_num;
    string name;
    int pin;
    double balance;
    string mobile;

public:
    void setData(long int acc_num, string name, int pin, double balance, string mobile) {
        this->acc_num = acc_num;
        this->name = name;
        this->pin = pin;
        this->balance = balance;
        this->mobile = mobile;
    }

    long int getAccNum() {
        return this->acc_num;
    }

    string getName() {
        return this->name;
    }

    int getPin() {
        return this->pin;
    }

    double getBalance() {
        return this->balance;
    }

    string getMobile() {
        return this->mobile;
    }

    void checkBalance() {
        cout << "Your Balance is: " << this->balance << endl;
        _getch();
    }

    void withdrawCash(double amount) {
        if (amount > 0 && amount <= this->balance) {
            this->balance -= amount;
            cout << "Please collect your cash" << endl;
            cout << "Your Remaining Balance is: " << this->balance << endl;
            _getch();
        } else {
            cout << "Invalid or Insufficient Amount" << endl;
            _getch();
        }
    }

    void ViewDetails() {
        cout << "Account Number: " << this->acc_num << endl;
        cout << "Name: " << this->name << endl;
        cout << "Balance: " << this->balance << endl;
        cout << "Mobile Number: " << this->mobile << endl;
        _getch();
    }

    void updateMobile(string old_mobile, string new_mobile) {
        if (old_mobile == this->mobile) {
            cout << "Enter New Mobile Number: ";
            cin >> new_mobile;
            this->mobile = new_mobile;
            cout << "Mobile Number Updated Successfully" << endl;
            _getch();
        } else {
            cout << "Invalid Mobile Number" << endl;
            _getch();
        }
    }

    void createAccount() {
        long int new_acc_num;
        string new_name, new_mobile;
        int new_pin;
        double initial_balance;

        cout << "Enter New Account Number: ";
        cin >> new_acc_num;
        cout << "Enter Name: ";
        cin.ignore(); 
        getline(cin, new_name);
        cout << "Enter Pin: ";
        cin >> new_pin;
        cout << "Enter Initial Balance: ";
        cin >> initial_balance;
        cout << "Enter Mobile Number: ";
        cin >> new_mobile;

        setData(new_acc_num, new_name, new_pin, initial_balance, new_mobile);
        cout << "Account Created Successfully!" << endl;

      
        ofstream outfile("accounts.csv", ios::app); 
        if (outfile.is_open()) {
            outfile << new_acc_num << "," << new_name << "," << new_pin << "," << initial_balance << "," << new_mobile << endl;
            outfile.close();
        } else {
            cout << "Error: Unable to open file for writing!" << endl;
        }

        _getch();
    }
};

int main() {
    int choice, account_num, pin;
    double amount;
    string old_mob, new_mob;

    ATM atm;

    do {
        system("cls");
        cout << "**********Welcome to ATM**********" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Existing User" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                atm.createAccount();
                break;

            case 2:
                cout << "Enter Account Number: ";
                cin >> account_num;
                cout << "Enter Pin: ";
                cin >> pin;

                {
                    do {
                        system("cls");
                        cout << "==========Welcome Back " << atm.getName() << "==========" << endl;
                        cout << "1. Check Balance" << endl;
                        cout << "2. Withdraw Cash" << endl;
                        cout << "3. View Details" << endl;
                        cout << "4. Update Mobile Number" << endl;
                        cout << "5. Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        switch (choice) {
                            case 1:
                                atm.checkBalance();
                                _getch();
                                break;

                            case 2:
                                cout << "Enter Amount: ";
                                cin >> amount;
                                atm.withdrawCash(amount);
                                _getch();
                                break;

                            case 3:
                                atm.ViewDetails();
                                _getch();
                                break;

                            case 4:
                                cout << "Enter Old Mobile Number: ";
                                cin >> old_mob;
                                atm.updateMobile(old_mob, new_mob);
                                _getch();
                                break;

                            case 5:
                                exit(0);
                                break;

                            default:
                                cout << "Invalid Choice" << endl;
                                _getch();
                                break;
                        }
                    } while (choice != 5);
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                cout << "Invalid Choice" << endl;
                _getch();
                break;
        }

        cout << "\nPress any key to continue...";
        _getch();

    } while (choice != 3);

    return 0;
}
