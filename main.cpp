#include <iostream>
#include <string>

#include "functions.cpp"

int main(int argc, char* argv[]) {
    /* Seed random number generator, ensures different numbers each execution */
    srand(time(0));


    try {
        
        std::string result = "0";

        for (int i = 0; i < 50; i++) {
            std::string number = generate_number(i+1);
            std::cout << i+1 << ": " << number << std::endl;
            result = add_stringA_and_stringB(result, number);
        }

        // truncate leading 0 from result

        std::cout << std::endl << "First 10 digits are: " << (result[0] == '-' ? result.substr(0,11) : result.substr(0,10)) << std::endl;
    } catch (exception& e) {
        cerr << e.what() << endl;
        return -1;
    }
    
}