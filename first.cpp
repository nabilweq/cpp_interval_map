#include <iostream>  // Include the standard I/O library

using namespace std;  // Use the standard namespace to avoid prefixing std::

int main() {
    // Declare a variable to hold the user's input
    int number;

    // Ask the user to enter a number
    cout << "Enter a positive integer: ";
    cin >> number;

    // Check if the number is positive
    if (number <= 0) {
        cout << "Please enter a positive integer!" << endl;
        return 1;
    }

    // Print a message and count down from the number to 1
    cout << "Counting down from " << number << " to 1:" << endl;

    for (int i = number; i > 0; --i) {
        cout << i << " ";
    }

    // Print a message when the countdown is complete
    cout << "\nLiftoff!" << endl;

    return 0;  // Indicate that the program ended successfully
}
