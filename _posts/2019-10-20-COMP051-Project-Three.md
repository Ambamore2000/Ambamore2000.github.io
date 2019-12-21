---
layout: runc++
title: COMP051 - Project Three
code: http://onlinegdb.com/embed/js/Hy_hZy3CS?theme=light
tags: [COMP051]
---

## Project Task

![Task](http://andrewjkim.me/college/COMP051/PROJECT_THREE/1.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_THREE/2.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_THREE/3.jpg){: .center-block :}

## Program

{% highlight javascript linenos %}
#include <iostream>
#include <ctime>

/***********************************************************
 * File: main.cpp
 * Author: Andrew Kim
 * Description: A simple casino simulator.
 ***********************************************************/

using namespace std;

void updateBalance(int &bal, int payoff, bool won) {
    if (won) {
        bal = bal + payoff;
        cout << "- WIN -" << endl << "New Current Balance: " << bal << endl;
    } else {
        bal = bal - payoff;
        cout << "- LOSS -" << endl << "New Current Balance: " << bal << endl;
    }
}

void wageBet(int balance, int &wage) {
    cout << "Current Balance: " << balance << endl;

    int wageBuffer;
    cout << "Bet Amount: ";
    cin >> wageBuffer;

    while (wageBuffer < 1 || wageBuffer > balance || cin.fail()) {
        if (cin.fail())
            cout << "ERROR: Please input an integer." << endl;
        else if (wageBuffer < 1)
            cout << "ERROR: Please input a wager greater than or equal to $1" << endl;
        else if (wageBuffer > balance)
            cout << "ERROR: Please input a wager less than or equal to your balance." << endl;
        cin.clear();
        cin.ignore(128, '\n');
        cin >> wageBuffer;
    }
    wage = wageBuffer;
}

int chooseOption() {
    cout << "1) Play High-Low" << endl;
    cout << "2) Play 21" << endl;
    cout << "3) Play Craps" << endl;
    cout << "4) Play the Slots" << endl;
    cout << "5) Play Test Cases" << endl;
    cout << "6) Leave Casino" << endl;

    int optionInput;
    cin >> optionInput;

    while (optionInput < 1 || optionInput > 6) {
        cout << "ERROR: Please input an option from 1-6" << endl;
        cin.clear();
        cin.ignore(128, '\n');
        cin >> optionInput;
    }

    return optionInput;
}

bool highLow() {
    int rnd = rand() % 10 + 1;
    int otherRnd = rand() % 10 + 1;
    cout << "Random Number : " << rnd << endl
    << "Generating another random number..." << endl
    << "Do you think this new random number will be higher or lower?" << endl
    << "Input H or L." << endl;
    char boolCheck;
    cin >> boolCheck;
    while (boolCheck != 'H' && boolCheck != 'h' && boolCheck != 'L' && boolCheck != 'l') {
        cout << "ERROR: Please input H or L." << endl;
        cin.clear();
        cin.ignore(128, '\n');
        cin >> boolCheck;
    }
    cout << "Comparison Random Number: " << otherRnd << endl;
    if (boolCheck == 'H' || boolCheck == 'h') {
        return otherRnd > rnd;
    } else if (boolCheck == 'L' || boolCheck == 'l') {
        return otherRnd < rnd;
    }
    return NULL;
}

int generateRandomValue() {
    int randVal = rand () % 13 + 1;
    if (randVal > 10)
        randVal = 10;
    return randVal;
}

bool twentyOne() {
    int userVal = (generateRandomValue() + generateRandomValue());
    cout << "Initial Score: " << userVal << endl;

    char userInput;

    do {
        cout << "(H)it or (S)tay?" << endl;
        cin >> userInput;
        while (userInput != 'H' && userInput != 'h' && userInput != 'S' && userInput != 's') {
            cout << "ERROR: Please input H or S." << endl;
            cin.clear();
            cin.ignore(128, '\n');
            cin >> userInput;
        }
        if (userInput == 'H' || userInput == 'h') {
            userVal = userVal + generateRandomValue();
            cout << "New Score: " << userVal << endl;
        } else if (userInput == 'S' || userInput == 's')
            break;
    } while (userVal < 21);

    if (userVal > 21)
        return false;
    else {
        int computerValue = rand () % 8 + 16;
        cout << "Computer Score: " << computerValue << endl;
        if (computerValue > 21)
            return true;
        return userVal > computerValue;
    }
}

int rollDie() {
    return rand() % 6 + 1;
}

bool craps() {
    char userInput;
    cout << "(P)ass or (N)o pass?" << endl;
    cin >> userInput;
    while (userInput != 'P' && userInput != 'p' && userInput != 'N' && userInput != 'n') {
        cout << "ERROR: Please input P or N." << endl;
        cin.clear();
        cin.ignore(128, '\n');
        cin >> userInput;
    }

    bool passBool;

    if (userInput == 'P' || userInput == 'p')
        passBool = true;
    else if (userInput == 'N' || userInput == 'n')
        passBool = false;

    int dieOne = rollDie();
    int dieTwo = rollDie();

    cout << "Die One: " << dieOne << endl
    << "Die Two: " << dieTwo << endl;

    int sum = dieOne + dieTwo;

    if (sum == 2 || sum == 3 || sum == 12) {
        return !passBool;
    } else if (sum == 7 || sum == 11) {
        return passBool;
    } else {
        int newSum = -1;
        while (newSum != sum && newSum != 7) {
            dieOne = rollDie();
            dieTwo = rollDie();
            newSum = dieOne + dieTwo;
        }
        cout << "New Die One: " << dieOne << endl
             << "New Die Two: " << dieTwo << endl;
        if (newSum == 7)
            return !passBool;
        if (newSum == sum)
            return passBool;
    }
    return NULL;
}

int randomSlot() {
    return rand() % 10;
}

void slots(int balance, int wager) {
    int slotOne = randomSlot();
    int slotTwo = randomSlot();
    int slotThree = randomSlot();
    cout << "|" << slotOne << "|" << slotTwo << "|" << slotThree << "|" << endl;

    if (slotOne == slotTwo && slotTwo == slotThree)
        updateBalance(balance, wager*99, true);
    else if (slotOne == slotTwo || slotOne == slotThree || slotTwo == slotThree) {
        updateBalance(balance, wager*10, true);
    } else {
        updateBalance(balance, wager, false);
    }
}

void testCaseDriver() {
    int ba = rand () % 101 + 100;
    // Fake win
    updateBalance(ba, 10, true);
    // Fake loss
    updateBalance(ba, 10, false);
    // Fake negative balance
    updateBalance(ba, -10, false);

    //  Loop for slots
    int loopSlots;
    cout << "How many times do you want to play the slot machine?" << endl;
    cin >> loopSlots;
    while (loopSlots < 1 || cin.fail()) {
        cout << "ERROR: Input an integer greater than 1.";
        cin.clear();
        cin.ignore(128, '\n');
        cin >> loopSlots;
    }
    for (int x = 0; x <= loopSlots; x++) {
        slots(ba, 10);
    }

}

int main() {

    srand(unsigned(time(0)));

    int balance = rand () % 101 + 100;

    do {
        int option = chooseOption();
        int wager;
        switch (option) {
            case 1:
                wageBet(balance, wager);
                updateBalance(balance, wager, highLow());
                continue;
            case 2:
                wageBet(balance, wager);
                if (twentyOne())
                    updateBalance(balance, wager*2, true);
                else
                    updateBalance(balance, wager, false);
                continue;
            case 3:
                wageBet(balance, wager);
                updateBalance(balance, wager, craps());
                continue;
            case 4:
                wageBet(balance, wager);
                slots(balance, wager);
                continue;
            case 5:
                testCaseDriver();
            case 6:
                cout << "Goodbye.." << endl;
                return 0;
        }
    } while (balance >= 1);

    cout << "GAME OVER: You have gone bankrupt.. loser." << endl;

    return 0;
}
{% endhighlight %}
