/*
 *  libbaseconvert library
 *  By Mateusz Przybyłowicz 2018
 *
 *  Converts positive decimal numbers to BASE 1 - 16 format.
 */

#include <climits>
#include <deque>
#include <iostream>
#include <limits>

using namespace std;

// Get user input
unsigned short int getBase() {
  unsigned short int input;
  do {
    cout << "Enter the desired base (1 - 16):" << endl;
    cin >> input;
    // Detect bad input
    if (!cin) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      input = 0;
    }
  } while (input == 0 || input > 17);

  return input;
}

// Get user input
unsigned int getDecimal() {
  unsigned int input;
  do {
    cout << "\nEnter a decimal:" << endl;
    cin >> input;
    // Detect bad input
    if (!cin) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      input = UINT_MAX;
    }
  } while (input == UINT_MAX);

  return input;
}

// Deal with the Decimal -> Unary conversion
deque<char> unaryConvert(unsigned int decimal) {
  deque<char> converted;
  while (decimal > 0) {
    converted.push_back('1');
    decimal--;
  }
  return converted;
}

// Deal with the Decimal -> Any conversion
deque<char> nConvert(unsigned int decimal, unsigned short int base) {
  unsigned int remainder;
  deque<char> converted;
  // Digits table for conversion
  char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
  while (decimal > 0) {
    remainder = decimal % base;
    decimal /= base;
    converted.push_front(digits[remainder]);
  }
  return converted;
}

// Display the converted number
void displayConverted(deque<char> converted) {
  while (!converted.empty()) {
    cout << converted.front();
    converted.pop_front();
  }
  cout << endl;
}

int main() {
  deque<char> converted;
  unsigned int decimal = getDecimal();
  unsigned short int base = getBase();
  if (decimal == 0) {
    cout << "0" << endl;
    return 0;
  }

  // Check if unary conversion is needed
  if (base == 1) {
    converted = unaryConvert(decimal);
  } else {
    converted = nConvert(decimal, base);
  }
  displayConverted(converted);
  return 0;
}
