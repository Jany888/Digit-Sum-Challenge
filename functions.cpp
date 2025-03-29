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

    if (length < int(number.length())) {
        throw invalid_argument("Length must be greater or equal to @number length.");
    }

    // Loop until string is the right length
    while(int(number.length()) < length) {
        // If the "number" is negative we need to keep '-' at the start and add a '0'
        // otherwise add a '0' at the start
        if (number[0] == '-') {
            number[0] = '0';
            number = '-' + number;
        } else { 
            number = '0' + number;
        }
    }

    return number;
}

// Function takes 2 strings and determines if the first parameter is greater
// returns true if the first parameter is greater
//     @numberA: string thats expected to be greater
//     @numberB: string thats expected to be lower
bool isGreater(string numberA, string numberB) {

    for (int i = 0; i < int(numberA.length()); i++) {
        // 1. If the numbers are equal we move on to the next index
        // 2. If one of the numbers is negative and the other starts with a '0', move on to the next index
        // 3. If the first number is negative and the second one is greater then '0' we know that second 
        //    number is greater, return false
        // 4. Same as the 2., but we know that first number is greater, return true
        // 5. We know that either of the numbers starts with '-', so we compare them
        // 6. otherwise it means numberA is greater
        if (numberA[i] == numberB[i]) { // 1.
            continue;
        } else if ((numberA[i] == '-' && numberB[i] == '0') || (numberB[i] == '-' && numberA[i] == '0') ) { // 2.
            continue;
        } else if (numberA[i] == '-' && numberB[i] > '0') { // 3.
            return false;
        } else if (numberB[i] == '-' && numberA[i] > '0') { // 4.
            return true;
        } else if (numberA[i] < numberB[i]) { // 5.
            return false;
        } else { // 6.
            return true;
        }
    }

    return false;
}

// Adds 2 strings numbers together and returns the result
//      @numberA: first number
//      @numberB: second number
string add_stringA_and_stringB(string numberA, string numberB) {

    // Adjusting number so they are equal length,
    // setting max_length to avoid 
    int max_length = max(numberA.length(), numberB.length()) + 1;
    numberA = adjust_number(numberA, max_length);
    numberB = adjust_number(numberB, max_length);

    // Finding out which abs() of the numbers is greater to make calculation easier,
    // then swapping the numbers so that numberA is greater then numberB
    if (!isGreater(numberA, numberB)) {
        swap(numberA, numberB);
    }

    string result = "";

    // Determines if both numbers are either positive or negative
    bool sameSign = numberA[0] == numberB[0] || (numberA[0] != '-' && numberB[0] != '-');

    int carry = 0;
    for (int i = max_length; i > 0; i--) {
        int sum = 0;
        if (numberA[i-1] == '-' || numberB[i-1] == '-') {
            break;
        }
        if (sameSign) {
            sum = numberA[i-1] + numberB[i-1] - (2 * 48) + carry;
            result = to_string(sum).back() + result;
            carry = sum / 10;
        } else {
            carry = (numberA[i-1] < numberB[i-1] ? 1 : 0); 
            sum = numberA[i-1] - numberB[i-1] + (carry * 10);
            result = to_string(sum).back() + result;
            numberA[i-2] = (carry == 1 ? numberA[i-2] - 1 : numberA[i-2]);
        }
    }

    if (numberA[0] == '-') {
        result = '-' + result;
    }

    // Truncate leading zeros
    int start = (result[0] == '-') ? 1 : 0;
    while (start < result.length() - 1 && result[start] == '0') {
        start++;
    }

    return (result[0] == '-') ? "-" + result.substr(start) : result.substr(start);
}