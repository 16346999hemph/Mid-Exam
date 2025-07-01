#include <iostream>
#include <iomanip> 

char printMenu();
void printInventory(int l, int m, int s);
void orderInventory(int& l, int& m, int& s);
void fillOrder(int& l, int& m, int& s, int& o);
float shippingCost(int o);
void printReceipt(int l, int m, int s, int order, int o);
using namespace std;

/*The most recent inventory of supply shows the chocolate inventory in the warehouse to be:
pre-existing inventory 620 - large (5 pounds each) sale price: $27.99
pre-existing inventory 500 - medium (3 pounds each) sale price: $21.99
pre-existing inventory 700 - small (1 pound each) sale price: $14.99 
b. The warehouse will fill orders as efficiently as possible using the fewest combination of large (5 pounds
each), medium (3 pounds each) and small (1 pound each) bars from the available stock.
c. The warehouse must update the total bars on hand and report the total.
d. The warehouse should use sequential numbers to track the orders made*/

void orderInventory(int& l, int& m, int& s) {
	int bars = 0;
	char size = ' ';
	cout << "Enter the number of bars needed: " << endl;
	cin >> bars;

	if (bars < 0) {
		cout << "ERROR: You cannot order a negative number of bars." << endl;
		return;
	}

	if (bars == 0 || bars > 1000) {
		cout << "No bars ordered." << endl;
		return;
	}

	if (l + m + s == 0) {
		cout << "ERROR: No bars available in inventory. Please order more bars." << endl;
		return;
	}


	cout << "What size do you want? (Enter L, M, or S): " << endl;
	cin >> size;

	switch (toupper(size)) {

	case 'L':
		cout << "An additional " << bars << "ordered. New total of large bars: " << (bars + l) << "." << endl;
		l = l + bars;
		break;

	case 'M':
		cout << "An additional " << bars << " ordered. New total of medium bars: " << (bars + m) << "." << endl;
		m = m + bars;
		break;
	case 'S':
		cout << "An additional " << bars << " ordered. New total of small bars: " << (bars + s) << "." << endl;
		s = s + bars;
		break;

	default:
		cout << "WARNING: " << size << " is not a valid size. Please enter L, M, or S." << endl;
		break;
	}


}

void fillOrder(int& l, int& m, int& s, int& o) {
	int poundsOrdered;
	cout << "\nPlease enter the number of pounds of chocolate you would like to order: ";
	cin >> poundsOrdered;

	int largeCt = poundsOrdered / 5;
	if (largeCt > l) largeCt = l;

	int tempOrder = poundsOrdered - largeCt * 5;
	int mediumCt = tempOrder / 3;
	if (mediumCt > m) mediumCt = m;

	tempOrder -= mediumCt * 3;
	if (tempOrder > s) {
		int totalPossible = l * 5 + m * 3 + s;
		cout << "WARNING: Unable to fill order of " << poundsOrdered << " pounds. We are "
			<< poundsOrdered - totalPossible << " pounds short. We are sorry for the inconvenience.\n";
	}
	else {
		int smallCt = tempOrder;
		printReceipt(largeCt, mediumCt, smallCt, poundsOrdered, o);
		l -= largeCt;
		m -= mediumCt;
		s -= smallCt;
		o++;
	}

	cout << "Remaining Inventory" << endl;
	cout << "Large bars:  " << l << " (5 lbs each)" << endl;	
	cout << "Medium bars: " << m << " (3 lbs each)" << endl;	
	cout << "Small bars:  " << s << " (1 lb each)" << endl;	

	cout << "Do you want to fill another order? (Y/N): ";
	char refill; 

	cin >> refill;

	if (toupper(refill) == 'Y') {
		fillOrder(l, m, s, o);
	} else {
		cout << "\nReturning to main menu." << endl;
	}


}


float shippingCost(int o) {
	const float flatRate = 19.75f;
	return o * flatRate;
}


void printReceipt(int l, int m, int s, int order, int o) {
	// Pricing constants
	float largeCost = 27.99f;
	float mediumCost = 21.99f;
	float smallCost = 14.99f;

	// Calculate individual totals
	float largeTot = l * largeCost;
	float mediumTot = m * mediumCost;
	float smallTot = s * smallCost;

	// Shipping and tax
	float shipping = shippingCost(order); // number of orders so far
	float totalCost1 = largeTot + mediumTot + smallTot;
	float tax = totalCost1 * 0.072f;
	float totalCost2 = totalCost1 + tax + shipping;

	// Formatting
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	cout << "\n========= ORDER RECEIPT =========\n";
	cout << "Chocolate Order #" << o + 1 << endl;  // assuming order number starts at 0

	cout << left;
	cout << "Large Bars:  " << setw(4) << l
		<< setw(7) << (l * 5) << "lbs"
		<< setw(12) << "$" << largeTot << endl;

	cout << "Medium Bars: " << setw(4) << m
		<< setw(7) << (m * 3) << "lbs"
		<< setw(12) << "$" << mediumTot << endl;

	cout << "Small Bars:  " << setw(4) << s
		<< setw(7) << s << "lbs"
		<< setw(12) << "$" << smallTot << endl;

	cout << "\nSub Total:   "
		<< setw(13) << (l * 5 + m * 3 + s) << "lbs"
		<< setw(12) << "$" << totalCost1 << endl;

	cout << "Tax Total:   " << setw(25) << "$" << tax << endl;
	cout << "Shipping:    " << setw(25) << "$" << shipping << endl;
	cout << "Total Cost:  " << setw(25) << "$" << totalCost2 << endl;

	cout << "=================================\n\n";
}

char printMenu() {
	char choice;
	cout << "\n========= CHOCOLATE FACTORY MENU =========\n";
	cout << "F - Fill an Order\n";
	cout << "P - Print Inventory\n";
	cout << "O - Order Inventory\n";
	cout << "E - Exit\n";
	cout << "Enter your choice: ";
	cin >> choice;
	return toupper(choice); // Normalize input to uppercase
}

void printInventory(int l, int m, int s) {
	cout << "\n========= CURRENT INVENTORY =========\n";
	cout << "Large Bars (5 lbs each):  " << l << endl;
	cout << "Medium Bars (3 lbs each): " << m << endl;
	cout << "Small Bars (1 lb each):   " << s << endl;
	cout << "=====================================\n";
}

int main() {
	int large = 620;  // 5lbs
	int medium = 500; // 3lbs
	int small = 700;  // 1lb
	int orderNumber = 0;
	char choice;

	do {
		cout << "\nCHOCOLATE FACTORY" << endl;
		cout << "F. Fill Order\nP. Print Inventory\nO. Order Inventory\nE. Exit" << endl;
		cin >> choice;

		switch (toupper(choice)) {
		case 'F':
			fillOrder(large, medium, small, orderNumber);
			break;
		case 'P':
			printInventory(large, medium, small);
			break;
		case 'O':
			orderInventory(large, medium, small);
			break;
		case 'E':
			cout << "Exiting program..." << endl;
			break;
		default:
			cout << "ERROR: " << choice << " is not a valid option." << endl;
		}

	} while (toupper(choice) != 'E');

	return 0;

}