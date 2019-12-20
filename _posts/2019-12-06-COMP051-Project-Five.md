---
layout: post
title: COMP051 - Project Five
subtitle: Each post also has a subtitle
tags: [COMP051]
---

## Project Task

![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/1.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/2.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/3.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/4.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/5.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FIVE/6.jpg){: .center-block :}

## Program

{% highlight javascript linenos %}
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Account {
public:
    Account(string number, string name, string type);
    string getNumber();
    string getName();
    string getType();
    int getBalance();
    void setBalance(int x);
private:
    string number,
            name,
            type;
    int balance = 0;
};

Account::Account(string number, string name, string type) {
    this->number = number;
    this->name = name;
    this->type = type;
}

string Account::getNumber() {
    return number;
}
string Account::getName() {
    return name;
}
string Account::getType() {
    return type;
}
int Account::getBalance() {
    return balance;
}

void Account::setBalance(int x) {
    balance = x;
}

class JETransactionLines {
private:
    string lineNumber, accountNumber;
    int debit, credit;
public:
    void set(string line, string account, int deb, int cred);
    string getLineNumber();
    string getAccountNumber();
    int getDebit();
    int getCredit();
};

void JETransactionLines::set(string line, string account, int deb, int cred) {
    lineNumber = line;
    accountNumber = account;
    debit = deb;
    credit = cred;
}

string JETransactionLines::getLineNumber() {
    return lineNumber;
}

string JETransactionLines::getAccountNumber() {
    return accountNumber;
}

int JETransactionLines::getDebit() {
    return debit;
}

int JETransactionLines::getCredit() {
    return credit;
}

class JETransactionHeader {
private:
    string dateOfJE;
    string transactionID;
    string memo;
    bool valid = true;
    vector<JETransactionLines> lines;
    int lineCount = -1;
public:
    void create(string date, string id, string notes);
    void insertLine(JETransactionLines lineToAdd);
    void validate(Account chartOfAccounts[]);
    bool isValid();
    void updateBalance(Account chartOfAccounts[]);
};

void JETransactionHeader::create(string date, string id, string notes) {
    dateOfJE = date;
    transactionID = id;
    memo = notes;
}

void JETransactionHeader::insertLine(JETransactionLines lineToAdd) {
    lines.push_back(lineToAdd);
    lineCount++;

}

void JETransactionHeader::validate(Account chartOfAccounts[]) {
    int totalCred = 0, totalDeb = 0;
    for (int y = 0; y < lineCount + 1; y++) {
        bool validAccountNumber = false;
        for (int x = 0; x < 13; x++) {
            if (chartOfAccounts[x].getNumber() == lines[y].getAccountNumber()) {
                validAccountNumber = true;
                break;
            }
        }
        if (!validAccountNumber) {
            cout << "Invalid account number = " << lines[y].getAccountNumber() << endl;

            valid = false;
            break;
        }
        if (lines[y].getCredit() > 0 && lines[y].getDebit() > 0) {
            cout << "Debit or credit cannot both be positive." << endl;
            valid = false;
            break;
        }
        if (lines[y].getCredit() < 0 || lines[y].getDebit() < 0) {
            cout << "Debit or credit cannot be negative." << endl;
            valid = false;
            break;
        }
        totalCred = totalCred + lines[y].getCredit();
        totalDeb = totalDeb + lines[y].getDebit();
    }

    if (totalCred != totalDeb && valid) {
        cout << "Total debits = " << totalDeb << " does not match total credits = " << totalCred << endl;
        valid = false;
    }

    if (isValid())
        updateBalance(chartOfAccounts);
    else
        cout << transactionID << " is invalid!" << endl;
}

bool JETransactionHeader::isValid() {
    return valid;
}

void JETransactionHeader::updateBalance(Account chartOfAccounts[]) {
    for (int y = 0; y < lineCount + 1; y++) {
        for (int x = 0; x < 13; x++) {
            if (chartOfAccounts[x].getNumber() == lines[y].getAccountNumber()) {
                if (lines[y].getDebit() > 0)
                    chartOfAccounts[x].setBalance(chartOfAccounts[x].getBalance() + lines[y].getDebit());
                else
                    chartOfAccounts[x].setBalance(chartOfAccounts[x].getBalance() - lines[y].getCredit());
                break;
            }
        }
    }
}

void readDataFile(JETransactionHeader jeTransactionHeader[]) {
    string fileName;

    cout << "Enter file name: ";
    cin >> fileName;

    cout << endl << "Validating Journals:" << endl;
    ifstream readFile;
    readFile.open(fileName);

    int x = 0;
    string line, dateOrDebit, memoOrCredit, idOrNumber;
    while (readFile >> line >> dateOrDebit >> memoOrCredit >> idOrNumber) {
        if (line == "0") {
            jeTransactionHeader[x].create(dateOrDebit, idOrNumber, memoOrCredit);
            x++;
        } else {
            JETransactionLines jeTransactionLines;
            jeTransactionLines.set(line, idOrNumber, stoi(dateOrDebit), stoi(memoOrCredit));
            jeTransactionHeader[x - 1].insertLine(jeTransactionLines);
        }
    }
    readFile.close();
}

void validateJEs(JETransactionHeader jesToValidate[], Account chartOfAccounts[]) {
    for (int x = 0; x < 9; x++)
        jesToValidate[x].validate(chartOfAccounts);
}

string sexyLine(const string& lastWord, string beginning) {
    unsigned int max = 28 - (beginning.length() + lastWord.length());
    for (unsigned int x = 0; x < max; x++) {
        beginning.append(" ");
    }
    return beginning + lastWord;
}

void displayStatement(Account entries[]) {
    cout << "Simple Income Statement:" << endl;

    int revenue = 0, expense = 0;
    cout << "Acct#\tAccount\t\tBalance" << endl;
    for (int x = 0; x < 11; x++) {
        cout << sexyLine(to_string(entries[x].getBalance()),
                entries[x].getNumber() + "\t" + entries[x].getName()) << endl;

        if (entries[x].getNumber().rfind("1", 0) == 0) {
            revenue = revenue + entries[x].getBalance();
        } else {
            expense = expense + entries[x].getBalance();
        }

        if (expense == 0 && entries[x + 1].getNumber().rfind("6", 0) == 0) {
            cout << "Total Revenue = " << revenue << endl << endl;
            cout << "Acct#\tAccount\t\tBalance" << endl;
        }
    }
    int netIncome = revenue + expense;
    cout << "Total Expense = " << expense << endl;
    cout << "Net Income = " << netIncome << endl;
}

int main() {

    cout << "COMP 51 Project 5 - Simple Journal Generator" << endl;

    Account a("1000","Sales","Revenue"),
            b("1010","Services","Revenue"),
            c("1020","Warranties","Revenue"),
            d("1030","Refunds","Revenue"),
            e("1040","Shipping","Revenue"),
            f("6000","Travel","Expense"),
            g("6005","Meals","Expense"),
            h("6010","Salaries","Expense"),
            i("6020","Supplies","Expense"),
            j("6050","Rent","Expense"),
            k("6060","Repairs","Expense"),
            l("2000","Accounts Receivable","Balance Sheet"),
            m("4000","Accounts Payable","Balance Sheet");

    Account chartOfAccounts[13] = {a, b, c, d, e, f, g, h, i, j, k, l, m};
    JETransactionHeader journalArray[9];

    readDataFile(journalArray);
    validateJEs(journalArray, chartOfAccounts);
    displayStatement(chartOfAccounts);

    system("pause");

    return 0;
}
{% endhighlight %}
