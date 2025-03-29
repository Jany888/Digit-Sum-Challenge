#include <gtest/gtest.h>
#include <cmath>

#include "functions.cpp"

/* Test expected to throw exception */
TEST(generate_number, CheckArguments) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int digits = -50 + rand() % 101;
        try {
            generate_number(digits);
            if (digits <= 0) {
                FAIL() << "Expected invalid_argument exception.";
            }
        } catch(invalid_argument const & e) {
            EXPECT_EQ(e.what(),string("Argument must be greater then 0."));
        } catch(...) {
            FAIL() << "Expected invalid_argument exception.";
        }
    }
}

TEST(generate_number, CheckLength) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int digits = 1 + rand() % 100; // Generates number from 1-100
        string number = generate_number(digits);
        int length = (number[0] == '-' ? number.length() - 1 : number.length());

        EXPECT_EQ(length, digits);
    }
}

TEST(generate_number, CheckCorrectCharacters) {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int digits = 1 + rand() % 100; // Generates number from 1-100
        string number = generate_number(digits);

        for (int y = 0; y < number.length(); y++) {
            if (number[y] != '-' && !(number[y] >= '0' && number[y] <= '9')) {
                FAIL() << "Unexpected characters in output.";
            }
        }
    }
}

TEST(adjust_number, CheckAdjustedNumber) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int digits = -9999 + rand() % 20000; // Generates number from -9999 to 9999
        string number = to_string(digits);

        int adjust_length = number.length() + rand() % 5;
        string adjusted_number = adjust_number(number, adjust_length);

        EXPECT_EQ(adjust_length, adjusted_number.length());

        int number_of_zeros = 0;
        number_of_zeros += adjust_length - number.length();
        if (number[0] == '-') {
            EXPECT_EQ(string(number_of_zeros, '0'), adjusted_number.substr(1, number_of_zeros));
        } else {
            EXPECT_EQ(string(number_of_zeros, '0'), adjusted_number.substr(0, number_of_zeros));
        }
    }

    for (int i = 0; i < 5; i++) {
        int digits = -9999 + rand() % 20000; // Generates number from -9999 to 9999
        string number = to_string(digits);

        try {
            adjust_number(number, number.length() - (1 + rand() % 5));
            FAIL() << "Length must be greater or equal to @number length.";
        } catch(invalid_argument const & e) {
            EXPECT_EQ(e.what(),string("Length must be greater or equal to @number length."));
        } catch(...) {
            FAIL() << "Length must be greater or equal to @number length.";
        }
    }
}

TEST(isGreater, BasicValidity) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int numberA = -9999 + rand() % 20000;
        int numberB = -9999 + rand() % 20000;

        string numberA_string = to_string(numberA);
        string numberB_string = to_string(numberB);

        int max_length = max(numberA_string.length(), numberB_string.length());

        numberA_string = adjust_number(numberA_string, max_length);
        numberB_string = adjust_number(numberB_string, max_length);

        EXPECT_EQ(isGreater(numberA_string, numberB_string), (abs(numberA) > abs(numberB)));
    }
}

void evaulate_result(int numberA, int numberB) {
    string numberA_string = to_string(numberA);
    string numberB_string = to_string(numberB);

    string result = add_stringA_and_stringB(numberA_string, numberB_string);
    string expected_result = to_string(numberA + numberB);

    EXPECT_EQ(result, expected_result);
}

TEST(add_stringA_and_stringB, AddingPositives) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int numberA = rand() % 999999;
        int numberB = rand() % 999999;

        evaulate_result(numberA, numberB);
    }
}

TEST(add_stringA_and_stringB, AddingNegatives) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int numberA = (1 + rand() % 999999) * -1; // -999,999 - -1
        int numberB = (1 + rand() % 999999) * -1;

        evaulate_result(numberA, numberB);
    }
}

TEST(add_stringA_and_stringB, AddingNegativeAndPositiveNumber) {
    srand(time(0));
    for (int i = 0; i < 100; i++) {
        int numberA = rand() % 999999;
        int numberB = (1 + rand() % 999999) * -1;

        evaulate_result(numberA, numberB);
        evaulate_result(numberB, numberA);
    }
}

TEST(add_stringA_and_stringB, Adding10RandomNumbersUpTo10Digits) {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        string result = "0";
        long long expected_result = 0;

        for (int y = 0; y < 10; y++) {
            long number = long(-pow(10, y+1) + 1) + rand() % (2 * long(pow(10, y+1)) - 1);
            expected_result += number;
            result = add_stringA_and_stringB(result, to_string(number));
        }

        EXPECT_EQ(result, to_string(expected_result));
    }
}