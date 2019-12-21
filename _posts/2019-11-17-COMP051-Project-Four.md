---
layout: post
title: COMP051 - Project Three
tags: [COMP051]
---

## Project Task

![Task](http://andrewjkim.me/college/COMP051/PROJECT_FOUR/1.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FOUR/2.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FOUR/3.jpg){: .center-block :}
![Task](http://andrewjkim.me/college/COMP051/PROJECT_FOUR/4.jpg){: .center-block :}

## Program

{% highlight javascript linenos %}
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;

class Item {
public:
	Item();
	Item(string desc, double cost, int ounces);

	void addQuantity(int x);
	string getDescription();
	int getQuantity();
	double getPrice();
	int getWeight();

private:
	string description = "";
	double price;
	int quantity;
	int weight;
};

Item::Item() {
	description = "";
	price = 0;
	quantity = 0;
	weight = 0;
}
Item::Item(string desc, double cost, int ounces) {
	description = move(desc);
	price = cost;
	quantity = 0;
	weight = ounces;
}

void Item::addQuantity(int x) {
	quantity = quantity + x;
}

string Item::getDescription() {
	return description;
}
int Item::getQuantity() {
	return quantity;
}
double Item::getPrice() {
    return price;
}
int Item::getWeight() {
    return weight;
}

struct Shipping {
	string zipCode;
	double taxRate{}, uspsRate{}, upsRate{}, fedexRate{};
};

void loadShipping(Shipping shippingArray[]) {
	ifstream readFile;
	readFile.open(R"(C:\Users\Andki\CLionProjects\COMP51_Andrew_Kim_Project_Four\zip code and shipping list.txt)");

	int x = 0;

	string zipCode;
	double taxRate, uspsRate, upsRate, fedexRate;
	while (readFile >> zipCode >> taxRate >> uspsRate >> upsRate >> fedexRate) {
        shippingArray[x].zipCode = zipCode;
        shippingArray[x].taxRate = taxRate;
        shippingArray[x].uspsRate = uspsRate;
        shippingArray[x].upsRate = upsRate;
        shippingArray[x].fedexRate = fedexRate;

		if (zipCode.length() > 5 || (taxRate < 0.0 || uspsRate < 0.0 || upsRate < 0.0 || fedexRate < 0.0)) {
			cout << "ERROR: Invalid data on line " << (x + 1) << ". Skipping over..." << endl;
			continue;
		}

		x++;
		if (x == 2678) //Hardcoded b/c stuck in infinite loop..
			break;
	}

	readFile.close();
}
int displayMenu() {
    cout << string(50, '\n');
	cout << "1) Create Customer Account" << endl;
	cout << "2) Shop for Items" << endl;
	cout << "3) Proceed to Check Out" << endl;
	cout << "4) Exit Store (without buying)" << endl;

	int option;
	cin >> option;
	while (cin.fail() || (option > 4 || option < 1)) {
		cin.clear();
		cin.ignore(128, '\n');
		cout << "ERROR: Please input an option from 1-4." << endl;
		cin >> option;
	}

	return option;
}
void promptUser(string &str, const string& prompt) {
	char iString[60];
	cout << prompt << endl;
	cin >> iString;
	str = iString;
	cin.getline(iString, 60);
	str = str + iString;
}
void createCustomer(string &name, string &address, string &city, string &zip) {
	promptUser(name, "What is your name?");
	promptUser(address, "What is your address?");
	promptUser(city, "What city do you live in?");
	promptUser(zip, "What is your zip code?");
}
void maintainCart(Item cart[], int &cartSize) {
	cout << "Enter an integer between 1-4 to purchase an item." << endl;
	cout << "1) Hut Tub Cover: $150.00" << endl;
	cout << "2) Pool Chemicals: $12.00" << endl;
	cout << "3) Bubbles: $18.00" << endl;
	cout << "4) Time Machine: $4000.00" << endl;

	Item hutTubCover("Hut Tub Cover", 150.00, 5);
	Item poolChemicals("Pool Chemicals", 12.00, 50);
	Item bubbles("Bubbles", 18.00, 10);
	Item timeMachine("Time Machine", 4000.00, 9001);

	int option;
	cin >> option;

	while (option > 4 || option < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(128, '\n');
		cout << "ERROR: Please enter an integer between 1-4." << endl;
		cin >> option;
	}

	cout << "How much would you like to purchase?" << endl;

	int purchaseAmount;
	cin >> purchaseAmount;
	while (purchaseAmount < 1 || cin.fail()) {
		cin.clear();
		cin.ignore(128, '\n');
		cout << "ERROR: Please enter an amount greater than 0." << endl;
		cin >> purchaseAmount;
	}

	Item itemToAdd;
	switch (option) {
        case 1:
            itemToAdd = hutTubCover;
            break;
        case 2:
            itemToAdd = poolChemicals;
            break;
        case 3:
            itemToAdd = bubbles;
            break;
        case 4:
            itemToAdd = timeMachine;
            break;
        default:
            cout << "ERROR WITH OPTION SWITCH CASE" << endl;
            return;
	}
	
	for (int x = 0; x < 4; x++) {
		if ((cart[x].getDescription() == hutTubCover.getDescription() && option == 1) ||
			(cart[x].getDescription() == poolChemicals.getDescription() && option == 2) ||
			(cart[x].getDescription() == bubbles.getDescription() && option == 3) ||
			(cart[x].getDescription() == timeMachine.getDescription() && option == 4)) {
			cart[x].addQuantity(purchaseAmount);
			return;
		}
	}

	cart[cartSize] = itemToAdd;
	cart[cartSize].addQuantity(purchaseAmount);
	cartSize++;
}
//Removed due to redundancy ??
/*
int displayReceipt(Item cart[4]) {
	int subtotal = 0;
	for (int x = 0; x < 4; x++) {
		cout << "Item: "<< cart[x].getDescription()
		    << "; Quantity - " << cart[x].getQuantity()
		    << "; Price - $" << cart[x].getPrice()
		    << "; Extended Amount - $" << (cart[x].getPrice() * cart[x].getQuantity()) << endl; //Not sure if this is correct.
		subtotal += cart[x].getPrice();
	}
	return subtotal;
}
 */
string endLine(const string& lastWord, string beginning) {
    unsigned int max = 73 - (beginning.length() + lastWord.length());
    for (unsigned int x = 0; x < max; x++) {
        beginning.append(" ");
    }
    return beginning + lastWord;
}
double calculateShipping(Item cart[], Shipping shippingArray[], const string& zip) {
    int shippingOption;
    cout << "Choose one of the following shipping methods:" << endl;
    cout << "1) USPS" << endl;
    cout << "2) UPS" << endl;
    cout << "3) FEDEX" << endl;

    cin >> shippingOption;
    while (shippingOption < 1 || shippingOption > 3 || cin.fail()) {
        cin.clear();
        cin.ignore(128, '\n');
        cout << "ERROR: Please input an option from 1-3." << endl;
        cin >> shippingOption;
    }

    double shippingRate = 0;

    for (int x = 0; x < 2678; x++) {
        if (shippingArray[x].zipCode == zip) {
            switch (shippingOption) {
                case 1:
                    shippingRate = shippingArray[x].uspsRate;
                    break;
                case 2:
                    shippingRate = shippingArray[x].upsRate;
                    break;
                case 3:
                    shippingRate = shippingArray[x].fedexRate;
                    break;
                default:
                    cout << "ERROR WITH SHIPPING OPTION SWITCH CASE" << endl;
                    return -1;
            }
            break;
        }
    }

    int weight = 0;
    for (int x = 0; x < 4; x++) {
        weight += (cart[x].getWeight() * cart[x].getQuantity());
    }

    if (weight >= 1 && weight <= 10) {
        return shippingRate;
    } else if (weight >= 11 && weight <= 50) {
        return (5 * shippingRate);
    } else if (weight > 50) {
        return (10 * shippingRate);
    }

    return -1;
}
double calculateTax(Shipping shippingArray[], const string& zip, double subtotal) {
    for (int x = 0; x < 2678; x++) {
        if (shippingArray[x].zipCode == zip) {
            return (subtotal * shippingArray[x].taxRate);
        }
    }
    return -1;
}
double calculateTotal(double subtotal, double shippingAmount, double taxAmount) {
    return (subtotal + shippingAmount + taxAmount);
}

string shrinkDouble(double shrink) {
    string toShrink = to_string(shrink);
    return toShrink.substr(0, toShrink.find('.') + 3);
}

void checkOut(Shipping shippingArray[], string &zipcode, Item cart[], const string& userName) {
    if (zipcode.empty()) {
        promptUser(zipcode, "What is your zip code?");
    }

    double subtotal = 0.00;

    ofstream writeFile;
    writeFile.open("invoice.txt");

    writeFile << "------------------------------ Receipt 101 ------------------------------" << endl;
    writeFile << "Cashier:                                                              BOT" << endl;
    writeFile << endLine(userName, "User:") << endl;
    writeFile << "-------------------------------------------------------------------------" << endl;

    for (int x = 0; x < 4; x++) {
        if (cart[x].getQuantity() > 0) {
            writeFile << "Item: " << cart[x].getDescription()
                      << "; Quantity - " << cart[x].getQuantity()
                      << "; Price - $" << cart[x].getPrice()
                      << "; Extended Amount - $" << (cart[x].getPrice() * cart[x].getQuantity())
                      << endl;
            subtotal += (cart[x].getPrice() * cart[x].getQuantity());
        }
    }

    writeFile << "-------------------------------------------------------------------------" << endl;

    double tax = calculateTax(shippingArray, zipcode, subtotal);
    double shipping = calculateShipping(cart, shippingArray, zipcode);

    if (tax < 0 || shipping < 0) {
        writeFile.clear();
        cout << "ERROR: Invalid zip code." << endl;
        return;
    }

    writeFile << endLine("$" + shrinkDouble(subtotal), "Subtotal:") << endl;
    writeFile << endLine("$" + shrinkDouble(tax), "Tax:") << endl;
    writeFile << endLine("$" + shrinkDouble(shipping), "Shipping:") << endl;
    writeFile << "-------------------------------------------------------------------------" << endl;
    writeFile << endLine("$" + shrinkDouble(calculateTotal(subtotal, shipping, tax)), "Total:") << endl;


    writeFile.close();

    ifstream readReceipt;
    readReceipt.open("invoice.txt");

    string read;
    if (readReceipt) {
        while (getline(readReceipt, read)) {
            cout << read << endl;
        }
    }

    readReceipt.close();
}

int main() {
	Shipping shippingArray[2678];
	loadShipping(shippingArray);

	cout << "Welcome to the Erots." << endl;

	string customerName = "NULL";
	string customerAddress;
	string customerCity;
	string customerZip;

	Item cart[4];
	int sizeOfCart = 0;

	int option = 0;
	while (option != 4) {
		option = displayMenu();
            switch (option) {
            case 1:
                createCustomer(customerName, customerAddress, customerCity, customerZip);
                break;
            case 2:
                maintainCart(cart, sizeOfCart);
                break;
            case 3:
                checkOut(shippingArray, customerZip, cart, customerName);
                option = 4;
            default:
                break;
		}
	}

	cout << "Goodbye!" << endl;

	return 0;
}
{% endhighlight %}
