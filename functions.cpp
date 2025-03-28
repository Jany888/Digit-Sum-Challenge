#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


// Function generates a random positive or negative number
//     @digits: number of digits to generate, should be >=1
string generate_number(int digits) {

    if (digits < 1) {
        throw invalid_argument("Argument must be greater then 0.");
    }

    string number = "";

    // Number Generation
    number += to_string(1 + rand() % 9); // Ensure that the first digit is from 1-9
    for (int i = 0; i < digits - 1; i++) { // Since first digit is already generated we must do digits - 1
        number += to_string(rand() % 10); // Other digits can be from 0-9
    }

    // Return result number, but add if the number is possitive or negative using ternary operator
    return (rand() % 2 == 0 ? "-" : "") + number;
}

// Function takes a string and adjusts its length
//     @number: string that needs to be adjusted to a specific length
//     @length: number what the string needs to be adjusted to
string adjust_number(string number, int length) {

    if (length < number.length()) {
        throw invalid_argument("Length must be greater or equal to @number length.");
    }

    while(number.length() < length) {
        if (number[0] == '-') {
            number[0] = '0';
            number = '-' + number;
        } else {
            number = '0' + number;
        }
    }

    return number;
}

bool isGreater(string numberA, string numberB) {
    for (int i = 0; i < numberA.length(); i++) {
        if ((numberA[i] == '-' && numberB[i] == '0') || (numberB[i] == '-' && numberA[i] == '0') ) {
            continue;
        } else if (numberA[i] == '-' && numberB[i] > '0') {
            return false;
        } else if (numberB[i] == '-' && numberA[i] > '0') {
            return true;
        } else if (numberA[i] < numberB[i]) {
            return false;
        } else if (numberA[i] >= '0' && numberB[i] >= '0') {
            return true;
        }
    }
    return true;
}

string add_stringA_and_stringB(string numberA, string numberB) {
    int max_length = max(numberA.length(), numberB.length());

    numberA = adjust_number(numberA, max_length);
    numberB = adjust_number(numberB, max_length);

    if (!isGreater(numberA, numberB)) {
        swap(numberA, numberB);
    }

    bool pos = numberA[0] == numberB[0] || (numberA[0] != '-' && numberB[0] != '-');

    int carry = 0;
    for (int i = max_length; i > 0; i--) {
        int sum = 0;
        if (pos) { // Case when both numbers are either positive or negative
            if (numberA[i-1] == '-' || numberB[i-1] == '-') {
                if (carry != 0) {
                    numberA[0] = to_string(carry).back();
                }
                numberA[0] = '-';
                break;
            }
            sum = numberA[i-1] + numberB[i-1] - (2 * 48) + carry;
            numberA[i-1] = to_string(sum).back();
            carry = sum / 10;
        } else {
            if (numberA[i-1] == '-' || numberB[i-1] == '-') {
                numberA[i-1] = (numberA[i-1] == '-' && numberB[i-1] != '0' ? numberB[i-1] : numberA[i-1]);
                break;
            }
            carry = (numberA[i-1] < numberB[i-1] ? 1 : 0); 
            sum = numberA[i-1] - numberB[i-1] + (carry * 10);
            numberA[i-1] = to_string(sum).back();
            numberA[i-2] = (carry == 1 ? numberA[i-2] - 1 : numberA[i-2]);
        }
    }


    return numberA;
}