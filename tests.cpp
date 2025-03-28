#include <gtest/gtest.h>

#include "functions.cpp"

/* Test expected to throw exception */
TEST(GenerateNumber, CheckArguments) {
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int digits = -50 + rand() % 101;
        try {
            generate_number(digits);
            if (digits <= 0) {
                FAIL() << "Expected invalid_argument exception.";
            }
        } catch(invalid_argument const & e) {
            EXPECT_EQ(e.what(),std::string("Argument must be greater then 0."));
        } catch(...) {
            FAIL() << "Expected invalid_argument exception.";
        }
    }
}

/* Test expected to pass */
TEST(GenerateNumber, CheckLength) {
    for (int i = 0; i < 10; i++) {
        int digits = 1 + rand() % 100; // Generates number from 1-100
        std::string number = generate_number(digits);
        int length = (number[0] == '-' ? number.length() - 1 : number.length());

        EXPECT_EQ(length, digits);
    }
}

/* Test expected to pass */
TEST(GenerateNumber, CheckCorrectCharacters) {
    for (int i = 0; i < 10; i++) {
        int digits = 1 + rand() % 100; // Generates number from 1-100
        std::string number = generate_number(digits);

        for (int y = 0; y < number.length(); y++) {
            if (number[y] != '-' && !(number[y] >= '0' && number[y] <= '9')) {
                FAIL() << "Unexpected characters in output.";
            }
        }
    }
}

/* Test expected to pass */
TEST(AdjustNumber, CheckAdjustedNumber) {
    for (int i = 0; i < 10; i++) {
        int digits = -9999 + rand() % 20000; // Generates number from -9999 to 9999
        std::string number = std::to_string(digits);

        int adjust_length = number.length() + rand() % 5;
        std::string adjusted_number = adjust_number(number, adjust_length);

        EXPECT_EQ(adjust_length, adjusted_number.length());

        int number_of_zeros = 0;
        number_of_zeros += adjust_length - number.length();
        if (number[0] == '-') {
            EXPECT_EQ(std::string(number_of_zeros, '0'), adjusted_number.substr(1, number_of_zeros));
        } else {
            EXPECT_EQ(std::string(number_of_zeros, '0'), adjusted_number.substr(0, number_of_zeros));
        }
    }

    for (int i = 0; i < 5; i++) {
        int digits = -9999 + rand() % 20000; // Generates number from -9999 to 9999
        std::string number = std::to_string(digits);

        try {
            adjust_number(number, number.length() - (1 + rand() % 5));
            FAIL() << "Length must be greater or equal to @number length.";
        } catch(invalid_argument const & e) {
            EXPECT_EQ(e.what(),std::string("Length must be greater or equal to @number length."));
        } catch(...) {
            FAIL() << "Length must be greater or equal to @number length.";
        }
    }
}

TEST(AddNumbers, AddingPositives) {
    EXPECT_EQ(add_stringA_and_stringB("120", "1"), "121");
    EXPECT_EQ(add_stringA_and_stringB("1", "2"), "3");
    EXPECT_EQ(add_stringA_and_stringB("5398", "690"), "6088");
    EXPECT_EQ(add_stringA_and_stringB("17169301", "864921657"), "882090958");
}

TEST(AddNumbers, AddingNegatives) {
    EXPECT_EQ(add_stringA_and_stringB("-120", "-1"), "-121");
    EXPECT_EQ(add_stringA_and_stringB("-1", "-2"), "-3");
    EXPECT_EQ(add_stringA_and_stringB("-5398", "-690"), "-6088");
    EXPECT_EQ(add_stringA_and_stringB("-17169301", "-864921657"), "-882090958");
}

TEST(AddNumbers, AddingNegativeAndPositive) {
    EXPECT_EQ(add_stringA_and_stringB("-120", "1"), "-119");
    EXPECT_EQ(add_stringA_and_stringB("1", "-120"), "-119");
    EXPECT_EQ(add_stringA_and_stringB("1", "-2"), "-1");
    EXPECT_EQ(add_stringA_and_stringB("-2", "1"), "-1");
    EXPECT_EQ(add_stringA_and_stringB("5398", "-690"), "4708");
    EXPECT_EQ(add_stringA_and_stringB("-690", "5398"), "4708");
    EXPECT_EQ(add_stringA_and_stringB("17169301", "-864921657"), "-847752356");
    EXPECT_EQ(add_stringA_and_stringB("-864921657", "17169301"), "-847752356");
}