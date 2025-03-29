#include <iostream>

#include "functions.cpp"

int main(int argc, char* argv[]) {

    /* Seed random number generator, ensures different numbers each execution */
    srand(time(0));

    run(50);
    
}