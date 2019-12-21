---
layout: runc++
title: COMP051 - Project Two
code: http://onlinegdb.com/embed/js/HkFt-1hCr?theme=light
tags: [COMP051]
---

## Project Task

![Task](http://andrewjkim.me/college/COMP051/PROJECT_TWO/1.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_TWO/2.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_TWO/3.jpg){: .center-block :}

## Program

{% highlight javascript linenos %}
/***********************************************************
 * File: main.cpp
 * Author: Andrew Kim
 * Description: To calculate statistics for character or number data entry.
 *
 ***********************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

int main() {

    srand((unsigned)time(0));

    // Initial Prompt
    cout << "Welcome to Andrew Kim's Project 2 - Counting Letters and Numbers" << endl
         << "Would you like to count..." << endl
         << "A: letters" << endl
         << "or" << endl
         << "B: numbers" << endl
         << "Enter 'A' or 'B' to proceed." << endl;

    // Initial Variables/Inputs
    char lettersOrNumbers;
    cin >> lettersOrNumbers;

    char letterInput = ' ';
    char booleanOptionInput = 'Y';

    int vowelAmount = 0;
    int consonantAmount = 0;
    int digitAmount = 0;
    int otherAmount = 0;

    int numDecVal;
    string classification;

    // While user doesn't enter a valid option, re-prompt user until user enters valid option (Only 'A' and 'B' are valid).
    while (lettersOrNumbers != 'A' && lettersOrNumbers != 'a' && lettersOrNumbers != 'B' && lettersOrNumbers != 'b') {
        cout << "ERROR: Invalid input." << endl
            << "Would you like to count..." << endl
            << "A: letters" << endl
            << "or" << endl
            << "B: numbers" << endl
            << "Enter 'A' or 'B' to proceed." << endl;
        cin >> lettersOrNumbers;
    }

    // If user selects to count letters. (Option A)
    if (lettersOrNumbers == 'A' || lettersOrNumbers == 'a') {
        // While user doesn't choose "no" on continuation prompt.
        while (booleanOptionInput == 'Y' || booleanOptionInput == 'y') {
            cout << "Please enter a character." << endl;
            cin >> letterInput;
            numDecVal = letterInput;

            // If input is between A-Z (Uppercase letters), classify as vowel/consonant
            if (numDecVal >= 'A' && numDecVal <= 'Z') {
                if (numDecVal == 'A' ||
                numDecVal == 'E' ||
                numDecVal == 'I' ||
                numDecVal == 'O' ||
                numDecVal == 'U') {
                    vowelAmount++;
                    classification = "Vowel";
                } else {
                    consonantAmount++;
                    classification = "Consonant";
                }
            // If input is between a-z (Lowercase letters), classify as vowel/consonant
            } else if (numDecVal >= 'a' && numDecVal <= 'z') {
                if (numDecVal == 'a' ||
                numDecVal == 'e' ||
                numDecVal == 'i' ||
                numDecVal == 'o' ||
                numDecVal == 'u') {
                    vowelAmount++;
                    classification = "Vowel";
                } else {
                    consonantAmount++;
                    classification = "Consonant";
                }
            // If input is between 0-9, classify as digit.
            } else if (numDecVal >= '0' && numDecVal <= '9') {
                digitAmount++;
                classification = "Digit";
            // Otherwise, every other input is classified as other.
            } else {
                otherAmount++;
                classification = "Other";
            }

            cout << "Input: " << letterInput << endl
            << "Numeric Decimal Value: " << numDecVal << endl
            << "Classification: " << classification << endl;

            cout << "Would you like to continue? (Y/N)" << endl;
            cin >> booleanOptionInput;
            while (booleanOptionInput != 'Y' && booleanOptionInput != 'N' && booleanOptionInput != 'y' && booleanOptionInput != 'n') {
                cout << "ERROR: Input was not (Y)es or (N)o." << endl;
                cin >> booleanOptionInput;
            }
        }

        cout << "Amount of:" << endl
             << "Vowels: " << vowelAmount << endl
             << "Consonants: " << consonantAmount << endl
             << "Digits: " << digitAmount << endl
             << "Others: " << otherAmount << endl;

    }
    // If user selects to count numbers. (Option B)
    else if (lettersOrNumbers == 'B' || lettersOrNumbers == 'b') {
        int upperBound, loopAmount;

        cout << "Please enter an integer from 10-1000." << endl; // Handle non-numeric input & if its greater or less than 10-1000.
        cin >> upperBound;

        // Re-prompts for upper bound if input is not an integer or is an integer not between 10-1000.
        while (upperBound > 1000 || upperBound < 10 || cin.fail()) {
            cin.clear();
            cin.ignore(128, '\n');
            cout << "ERROR: Out of bounds/Not an integer. Enter an integer from 10-1000." << endl;
            cin >> upperBound;
        }

        cout << "Please enter amount of times to run loop. (Greater than 3)" << endl; //Must be greater than 3.
        cin >> loopAmount;

        // Re-prompts user for loop amount if input is not an integer or is an integer less than or equal to 3.
        while (loopAmount <= 3) {
            cin.clear();
            cin.ignore(128, '\n');
            cout << "ERROR: Too low. Enter an integer greater than 3." << endl;
            cin >> loopAmount;
        }

        // Random number generator variables
        int current = 0;
        int lowest = 1000;
        int highest = 0;
        int total = 0;

        bool initial = true;

        // Loop through and do random number generation calculations.
        for (int i = 0; i <= loopAmount; i++) {
            // If in first for loop.
            if (initial) {
                initial = false;
                cout << setw(32) << "Counter" << setw(6) << "Loops" << setw(12) << "Current" << setw(8) << "Lowest" << setw(10) << "Highest" << setw(6) << "Total" << setw(9) << endl;
                cout << "Initial values  " << i << setw(9) << i << setw(9) << loopAmount << setw(9) << current << setw(9) << "0" << setw(9) << highest << setw(9) << total << endl;
                continue;
            }
            current = rand() % upperBound + 1;

            if (current < lowest)
                lowest = current;
            if (current > highest)
                highest = current;

            total = current + total;

            cout << "End of loop     " << i << setw(9) << i << setw(9) << loopAmount << setw(9) << current << setw(9) << lowest << setw(9) << highest << setw(9) << total << endl;

        }

        cout << "Lowest Generated Number: " << lowest << endl
             << "Highest Generated Number: " << highest << endl
             << "Average of Generated Numbers: " << total/loopAmount << endl;
    }

    system("pause");

}
{% endhighlight %}
