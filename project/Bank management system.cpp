#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(string t, double a) : type(t), amount(a) {}

    void display() {
        cout << setw(10) << type << " : " << fixed << setprecision(2) << amount << endl;
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double initialBalance) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    int getAccountNumber() { return accountNumber; }

    double getBalance() { return balance; }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposited: " << amount << endl;
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!" << endl;
            return false;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout << "Withdrawn: " << amount << endl;
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (amount > balance) {
            cout << "Insufficient balance for transfer!" << endl;
            return false;
        }
        balance -= amount;
        to.balance += amount;
        transactions.push_back(Transaction("Transfer to " + toAccountNumber(to), amount));
        to.transactions.push_back(Transaction("Transfer from " + toAccountNumber(*this), amount));
        cout << "Transferred: " << amount << " to Account " << to.getAccountNumber() << endl;
        return true;
    }

    void showTransactions() {
        cout << "\nTransaction History for Account " << accountNumber << ":\n";
        for (auto &t : transactions)
            t.display();
    }

    void displayInfo() {
        cout << "\nAccount Number: " << accountNumber << "\nBalance: " << fixed << setprecision(2) << balance << endl;
        showTransactions();
    }

    string toAccountNumber(const Account &a) {
        return to_string(a.accountNumber);
    }
};

class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string n, int id) : name(n), customerID(id) {}

    void addAccount(Account acc) {
        accounts.push_back(acc);
    }

    Account* getAccount(int accNum) {
        for (auto &acc : accounts) {
            if (acc.getAccountNumber() == accNum)
                return &acc;
        }
        return nullptr;
    }

    void displayCustomerInfo() {
        cout << "\nCustomer Name: " << name << "\nCustomer ID: " << customerID << endl;
        for (auto &acc : accounts)
            acc.displayInfo();
    }
};

int main() {
    string name;
    int custID, accNum;
    double balance;

    cout << "Enter Customer Name: ";
    getline(cin, name);
    cout << "Enter Customer ID: ";
    cin >> custID;

    Customer customer(name, custID);

    int numAccounts;
    cout << "Enter number of accounts: ";
    cin >> numAccounts;

    for (int i = 0; i < numAccounts; i++) {
        cout << "Enter Account Number for Account " << i + 1 << ": ";
        cin >> accNum;
        cout << "Enter Initial Balance: ";
        cin >> balance;
        customer.addAccount(Account(accNum, balance));
    }

    int choice;
    do {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. Show Account Info\n5. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            int acc;
            double amt;
            cout << "Enter Account Number: ";
            cin >> acc;
            cout << "Enter Amount to Deposit: ";
            cin >> amt;
            Account* a = customer.getAccount(acc);
            if (a) a->deposit(amt);
            else cout << "Account not found!\n";
        } 
        else if (choice == 2) {
            int acc;
            double amt;
            cout << "Enter Account Number: ";
            cin >> acc;
            cout << "Enter Amount to Withdraw: ";
            cin >> amt;
            Account* a = customer.getAccount(acc);
            if (a) a->withdraw(amt);
            else cout << "Account not found!\n";
        } 
        else if (choice == 3) {
            int fromAcc, toAcc;
            double amt;
            cout << "Enter Source Account Number: ";
            cin >> fromAcc;
            cout << "Enter Destination Account Number: ";
            cin >> toAcc;
            cout << "Enter Amount to Transfer: ";
            cin >> amt;
            Account* src = customer.getAccount(fromAcc);
            Account* dst = customer.getAccount(toAcc);
            if (src && dst) src->transfer(*dst, amt);
            else cout << "One or both accounts not found!\n";
        } 
        else if (choice == 4) {
            customer.displayCustomerInfo();
        }
    } while (choice != 5);

    cout << "Thank you for using the Banking System!\n";
    return 0;
}