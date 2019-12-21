---
layout: runc++
title: COMP051 - Project One
code: "//onlinegdb.com/embed/js/rkb9NHjAH?theme=dark"
tags: [COMP051]
---

## Project Task

![Task](http://andrewjkim.me/college/COMP051/PROJECT_ONE/1.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_ONE/2.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_ONE/3.jpg){: .center-block :}

## Program

{% highlight javascript linenos %}
/////////////////////////////////////
///////Change Making Program/////////
///////////By: Andrew Kim////////////
/////////////////////////////////////
#include <iostream>
#include <string>

using namespace std;

int main()
{
  // Prompt user name
  string name;
  cout << "Change making program by Andrew Kim" << endl
        << "What is the customer's first name? ";
  cin >> name;
  
  // Prompt item description
  string description;
  cout << "Enter an item description: ";
  cin >> description;
 
  // Random seed
  srand((unsigned)time(0));
  
  //Display random price from 1-2000 cents.
  int price = rand()%2000 + 1;
  cout << "The price of " << description << " (in cents): " << price << endl;
  
  // Prompt amount tendered (in cents)
  int amountTendered;
  cout << "Please enter the amount tendered in cents: ";
  cin >> amountTendered;
  
  // Display change
  cout.precision(2);
  cout << name << " bought " << description << " for $" << fixed << (0.01 * price) << " and tendered $" 
  << fixed << (0.01 * amountTendered) << endl
  << name << "'s change is:" << endl;
  
  int change = amountTendered - price;
  
  // Initializing constants for change
  const int HUNDREDS = 10000;
  const int FIFTIES = 5000;
  const int TWENTIES = 2000;
  const int TENS = 1000;
  const int FIVES = 500;
  const int ONES = 100;
  const int QUARTERS = 25;
  const int DIMES = 10;
  const int NICKELS = 5;
  const int PENNIES = 1;
  
  // For plurals
  string s = "";
  
  // Andrew's Change 101
  
  int numOfHundreds = (change / HUNDREDS);
  if (numOfHundreds != 0) {
      if (numOfHundreds != 1)
        s = "s";
      cout << "         " << numOfHundreds << " one-hundred-dollar bill" + s << endl;
      s = "";
      change = change - (HUNDREDS*numOfHundreds);
  }
  
  int numOfFifties = (change / FIFTIES);
  if (numOfFifties != 0) {
      if (numOfFifties != 1)
        s = "s";
      cout << "         " << numOfFifties << " fifty-dollar bill" + s << endl;
      s = "";
      change = change - (FIFTIES*numOfFifties);
  }
  
  int numOfTwenties = (change / TWENTIES);
  if (numOfTwenties != 0) {
      if (numOfTwenties != 1)
        s = "s";
      cout << "         " << numOfTwenties << " twenty-dollar bill" + s << endl;
      s = "";
      change = change - (TWENTIES*numOfTwenties);
  }
  
  int numOfTens = (change / TENS);
  if (numOfTens != 0) {
      if (numOfTens != 1)
        s = "s";
      cout << "         " << numOfTens << " ten-dollar bill" + s << endl;
      s = "";
      change = change - (TENS*numOfTens);
  }
  
  int numOfFives = (change / FIVES);
  if (numOfFives != 0) {
      if (numOfFives != 1)
        s = "s";
      cout << "         " << numOfFives << " five-dollar bill" + s << endl;
      s = "";
      change = change - (FIVES*numOfFives);
  }
  
  int numOfOnes = (change / ONES);
  if (numOfOnes != 0) {
      if (numOfOnes != 1)
        s = "s";
      cout << "         " << numOfOnes << " one-dollar bill" + s << endl;
      s = "";
      change = change - (ONES*numOfOnes);
  }
  
  int numOfQuarters = (change / QUARTERS);
  if (numOfQuarters != 0) {
      if (numOfQuarters != 1)
        s = "s";
      cout << "         " << numOfQuarters << " quarter" + s << endl;
      s = "";
      change = change - (QUARTERS*numOfQuarters);
  }
  
  int numOfDimes = (change / DIMES);
  if (numOfDimes != 0) {
      if (numOfDimes != 1)
        s = "s";
      cout << "         " << numOfDimes << " dime" + s << endl;
      s = "";
      change = change - (DIMES*numOfDimes);
  }
  
  int numOfNickels = (change / NICKELS);
  if (numOfNickels != 0) {
      if (numOfNickels != 1)
        s = "s";
      cout << "         " << numOfNickels << " nickel" + s << endl;
      s = "";
      change = change - (NICKELS*numOfNickels);
  }
  
  int numOfPennies = (change / PENNIES);
  if (numOfPennies != 0) {
      s = "y";
      if (numOfPennies != 1)
        s = "ies";
      cout << "         " << numOfPennies << " penn" + s << endl;
      change = change - (PENNIES*numOfPennies);
  }
  
  return 0;
}

{% endhighlight %}
