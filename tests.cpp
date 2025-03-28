#include <gtest/gtest.h>

#include "functions.cpp"

TEST(GenerateNumbers, CheckLength) { // Test expected to pass
    int digits = 1 + rand() % 100; // Generates number from 1-100
    std::string number = generate_number(digits);
    int length = (number[0] == '-' ? number.length() - 1 : number.length());

    EXPECT_EQ(length, digits);
}

TEST(Number, getMaxLength) {
    EXPECT_EQ(get_max_length("-120", "1"), 4);
    EXPECT_EQ(get_max_length("-223", "-950"), 4);
    EXPECT_EQ(get_max_length("0", "690"), 3);
    EXPECT_EQ(get_max_length("-2", "864921657"), 9);
}

TEST(AdjustNumber, CheckNumber) { // Test expected to pass
    EXPECT_EQ(adjust_number("1", 1), "1");
    EXPECT_EQ(adjust_number("-1", 3), "-01");
    EXPECT_EQ(adjust_number("99", 5), "00099");
    EXPECT_EQ(adjust_number("-3", 2), "-3");
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