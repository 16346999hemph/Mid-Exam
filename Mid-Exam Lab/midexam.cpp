#include <iostream>
#include <iomanip>

using namespace std;

// Function declarations
void fillOrder(int& l, int& m, int& s, int& o);
float shippingCost(int o);
void printReceipt(int l, int m, int s, int order, int o);

// Function to calculate shipping cost based on number of orders
float shippingCost(int o) {
    const float flatRate = 19.75f;
    return o * flatRate;
}

// Function to print the order receipt with price breakdown, tax, and shipping
void printReceipt(int l, int m, int s, int order, int o) {
    // Bar pricing constants
    float largeCost = 27.99f;
    float mediumCost = 21.99f;
    float smallCost = 14.99f;

    // Calculate total cost by size
    float largeTot = l * largeCost;
    float mediumTot = m * mediumCost;
    float smallTot = s * smallCost;

    // Compute tax and shipping
    float shipping = shippingCost(order);
    float subtotal = largeTot + mediumTot + smallTot;
    float tax = subtotal * 0.072f;
    float total = subtotal + tax + shipping;

    // Output formatting
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    // Display receipt
    cout << "\n========= ORDER RECEIPT =========\n";
    cout << "Chocolate Order #" << o + 1 << endl;

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
         << setw(12) << "$" << subtotal << endl;

    cout << "Tax Total:   " << setw(25) << "$" << tax << endl;
    cout << "Shipping:    " << setw(25) << "$" << shipping << endl;
    cout << "Total Cost:  " << setw(25) << "$" << total << endl;
    cout << "=================================\n\n";
}

// Function to fill a customer's chocolate order using the most efficient combination of bars
void fillOrder(int& l, int& m, int& s, int& o) {
    int poundsOrdered;

    cout << "\nPlease enter the number of pounds of chocolate you would like to order: ";
    cin >> poundsOrdered;

    // Determine maximum number of large bars that can be used
    int largeCt = poundsOrdered / 5;
    if (largeCt > l) largeCt = l;

    // Calculate remaining pounds after using large bars
    int tempOrder = poundsOrdered - largeCt * 5;

    // Determine maximum number of medium bars that can be used
    int mediumCt = tempOrder / 3;
    if (mediumCt > m) mediumCt = m;

    // Calculate remaining pounds after using medium bars
    tempOrder -= mediumCt * 3;

    // If not enough small bars to complete the order, notify the customer
    if (tempOrder > s) {
        int totalPossible = l * 5 + m * 3 + s;
        cout << "WARNING: Unable to fill order of " << poundsOrdered << " pounds.\n";
        cout << "We are short by " << poundsOrdered - totalPossible << " pounds.\n";
        cout << "We are sorry for the inconvenience.\n";
    } else {
        int smallCt = tempOrder;

        // Print the receipt
        printReceipt(largeCt, mediumCt, smallCt, poundsOrdered, o);

        // Deduct used bars from inventory
        l -= largeCt;
        m -= mediumCt;
        s -= smallCt;

        // Increment order number
        o++;
    }

    // Show remaining inventory after filling the order
    cout << "\nRemaining Inventory:\n";
    cout << "Large bars:  " << l << " (5 lbs each)\n";
    cout << "Medium bars: " << m << " (3 lbs each)\n";
    cout << "Small bars:  " << s << " (1 lb each)\n";

    // Prompt to process another order
    char refill;
    cout << "\nDo you want to fill another order? (Y/N): ";
    cin >> refill;

    if (toupper(refill) == 'Y') {
        fillOrder(l, m, s, o);
    } else {
        cout << "\nThank you. Returning to exit.\n";
    }
}

int main() {
    // Initial inventory counts
    int large = 620;   // Large bars: 5 lbs
    int medium = 500;  // Medium bars: 3 lbs
    int small = 700;   // Small bars: 1 lb
    int orderNumber = 0;

    char choice;

    // (only Fill Order or Exit)
    do {
        cout << "\n========= CHOCOLATE FACTORY =========\n";
        cout << "F - Fill an Order\n";
        cout << "E - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (toupper(choice)) {
            case 'F':
                fillOrder(large, medium, small, orderNumber);
                break;
            case 'E':
                cout << "Exiting program...\n";
                break;
            default:
                cout << "ERROR: Invalid option. Please enter F or E.\n";
        }
    } while (toupper(choice) != 'E');

    return 0;
}
