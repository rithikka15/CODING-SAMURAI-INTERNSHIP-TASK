#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
public:
    int accNo;
    string name;
    double balance;
};

BankAccount acc[100];
int n = 0;

// Load accounts from file
void load() {
    ifstream fin("accounts.txt");
    n = 0;
    while (fin >> acc[n].accNo >> acc[n].name >> acc[n].balance) {
        n++;
    }
    fin.close();
}

// Save accounts to file
void save() {
    ofstream fout("accounts.txt");
    for (int i = 0; i < n; i++) {
        fout << acc[i].accNo << " "
             << acc[i].name << " "
             << acc[i].balance << endl;
    }
    fout.close();
}

// Find account
int search(int acno) {
    for (int i = 0; i < n; i++) {
        if (acc[i].accNo == acno)
            return i;
    }
    return -1;
}

// Create new account
void createAccount() {
    cout << "Enter Account Number: ";
    cin >> acc[n].accNo;
    cout << "Enter Name: ";
    cin >> acc[n].name;
    cout << "Enter Initial Balance: ";
    cin >> acc[n].balance;
    n++;
    cout << "Account created successfully\n";
}

// Delete account
void deleteAccount() {
    int acno;
    cout << "Enter Account Number to delete: ";
    cin >> acno;

    int pos = search(acno);
    if (pos == -1) {
        cout << "Account not found\n";
        return;
    }

    for (int i = pos; i < n - 1; i++) {
        acc[i] = acc[i + 1];
    }
    n--;
    cout << "Account deleted successfully\n";
}

int main() {
    load();
    int choice;

    do {
        cout << "\n--- BANK MENU ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Transfer Money\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            createAccount();
        }

        else if (choice == 2) {
            int acno;
            double amt;
            cout << "Account Number: ";
            cin >> acno;
            cout << "Amount: ";
            cin >> amt;

            int i = search(acno);
            if (i != -1) {
                acc[i].balance += amt;
                cout << "Deposit successful\n";
            } else {
                cout << "Account not found\n";
            }
        }

        else if (choice == 3) {
            int acno;
            double amt;
            cout << "Account Number: ";
            cin >> acno;
            cout << "Amount: ";
            cin >> amt;

            int i = search(acno);
            if (i != -1 && acc[i].balance >= amt) {
                acc[i].balance -= amt;
                cout << "Withdrawal successful\n";
            } else {
                cout << "Insufficient balance or account not found\n";
            }
        }

        else if (choice == 4) {
            int acno;
            cout << "Account Number: ";
            cin >> acno;

            int i = search(acno);
            if (i != -1) {
                cout << "Balance: " << acc[i].balance << endl;
            } else {
                cout << "Account not found\n";
            }
        }

        else if (choice == 5) {
            int from, to;
            double amt;
            cout << "From Account: ";
            cin >> from;
            cout << "To Account: ";
            cin >> to;
            cout << "Amount: ";
            cin >> amt;

            int i1 = search(from);
            int i2 = search(to);

            if (i1 != -1 && i2 != -1 && acc[i1].balance >= amt) {
                acc[i1].balance -= amt;
                acc[i2].balance += amt;
                cout << "Transfer successful\n";
            } else {
                cout << "Transfer failed\n";
            }
        }

        else if (choice == 6) {
            deleteAccount();
        }

        save();

    } while (choice != 7);

    cout << "Thank you\n";
    return 0;
}
