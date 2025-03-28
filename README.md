## Task

Create a program that can calculate 50 numbers, where the first number is 1-digit, the second number is 2-digit, … the 50th number is 50-digit.

*Example:*  
1\. number 1  
2\. number 32  
3\. number -105  
...  
49\. number -3456789012345678901234567890123456789012345678901  
50\. number -23456789012345678901234567890123456789012345678901  

**What the program should do:**
1. Randomly generate 50 numbers, where the first digit will be generated from the numbers 1 – 9, to maintain the equality of the order of the number with its digits, and each subsequent digit will be randomly generated from the numbers 0 – 9
2. Randomly generate a sign (in this case, whether it is positive or negative number)
3. Add these 50 numbers and display only the first 10 digits of the result

**What the source code should contain:**
1. Comment the code, where it will be clear what the code does
2. Use only English names of functions/methods
3. Primarily use an object-oriented language (we agreed on C++)
4. Use only standard data types. It should not contain libraries/data types that can work with large numbers
5. Write tests that verify that the functions/methods work correctly

## Build

After clone, only run for the first time:
```bash
    cmake -S . -B build
```

Build/Re-build project with:
```bash
    cmake --build build -j 12
```


Run tests with:
```bash
    ./build/tests
```

Run main with:
```bash
    ./build/main
```