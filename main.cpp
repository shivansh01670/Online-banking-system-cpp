#include <iostream>
#include <string>
#include "BankService.h"

using namespace std;

int main() {
    BankService bankService;
    bool exitApp = false;

    while (!exitApp) {
        cout << "\n========== Online Banking System ==========\n";
        cout << "1. Register  2. Login\n";
        cout << "3. Create Account  4. Deposit\n";
        cout << "5. Withdraw  6. Show Balance\n";
        cout << "7. Transfer  8. Show Transactions\n";
        cout << "9. Delete Account  10. Bank Statement\n";
        cout << "11. Logout  12. Exit\n";
        cout << "Choose an option: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                cin.ignore(10000, '\n');
                cout << "Enter name: ";
                string name; getline(cin, name);
                cout << "Enter email: ";
                string email; getline(cin, email);
                cout << "Enter password: ";
                string password; getline(cin, password);
                bankService.registerUser(name, email, password);
                break;
            }
            case 2: {
                cin.ignore(10000, '\n');
                cout << "Enter email: ";
                string email; getline(cin, email);
                cout << "Enter password: ";
                string password; getline(cin, password);
                bankService.login(email, password);
                break;
            }
            case 3:
                bankService.createAccount();
                break;
            case 4: {
                cout << "Enter amount to deposit: ";
                double amount; cin >> amount;
                bankService.deposit(amount);
                break;
            }
            case 5: {
                cout << "Enter amount to withdraw: ";
                double amount; cin >> amount;
                bankService.withdraw(amount);
                break;
            }
            case 6:
                bankService.showBalance();
                break;
            case 7: {
                cout << "Enter recipient Account ID: ";
                int toAccountId; cin >> toAccountId;
                cout << "Enter amount to transfer: ";
                double amount; cin >> amount;
                bankService.transfer(toAccountId, amount);
                break;
            }
            case 8:
                bankService.showTransactions();
                break;
            case 9: {
                cout << "Enter Account ID to delete: ";
                int accountId; cin >> accountId;
                bankService.deleteAccount(accountId);
                break;
            }
            case 10: {
                cout << "Enter Account ID for statement: ";
                int accountId; cin >> accountId;
                bankService.generateBankStatement(accountId);
                break;
            }
            case 11:
                bankService.logout();
                break;
            case 12:
                exitApp = true;
                break;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
    
    cout << "Thank you for using the Online Banking System!\n";
    return 0;
}
