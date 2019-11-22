#include "converter.hpp"
#include "../error/error.hpp"
#include <iostream>
#include <locale>
#include <algorithm>

using namespace std;

int binaryToDecimal(string binary)
{
      // error checking, check if the string is empty, check if the string is in 8 bit binary format
        if (binary.empty())
        {
            // print an error message if any of the above conditions are true
            checkValidity(INVALID_INPUT_PARAMETER);
        }

        // initialise variables for error check algorithm
        int i = 0;
        string tempString;

        // while loop runs thorugh the inputed string checking if any of the elements are not a 1 or a 0
        while (binary[i] != '\0')
        {
            // set the temporary variable to the element in the string
            tempString = binary[i];

            // use the compare function to check if the element is a 0 (i.e. does it return 0)
            if (tempString.compare("0") != 0)
            {
                // if the element is not a 0 then it must be a 1, use compare function to check
                if (tempString.compare("1") != 0)
                {
                    // if the element is not a 1 then it is invalid. Print an error messages to signal this
                   checkValidity(INVALID_INPUT_PARAMETER);
                }
            }

             i++; // add one to the counter variable to move to the next element in the string

        }

        reverse(binary.begin(), binary.end()); // format the binary so that our answer is correct

        // initialise variables for conversion algorithm
        // Conversion algorithm was aquired from https://www.geeksforgeeks.org/program-binary-decimal-conversion/
        long int temp = stol(binary); // note we convert the user's string to an integer using the stoi function
        int convertedDecimal = 0;
        int base = 1;
        int lastNum;

        // while loop runs until the temporary varible reaches 0
        while (temp != 0)
        {
            // get the last number in the binary sequence
            lastNum = temp % 10;

            // move the temporary variable down to the next number in the sequence
            temp = temp / 10;

            // add the result of the last number * base to the convert variable
            convertedDecimal += lastNum * base;

            // increment the base up to the next base of 8 bit binary, the final base being 128
            base = base * 2;
        }
        // end of conversion algorithm

        return convertedDecimal; // return the converted decimal number
}

string decimalConversion(long long int decimalNum)
{
    // initialise variables for conversion algorithm
    string convertedBinary;
    long long int temp = decimalNum;
    long long int binaryVal;

    // while loop runs 8 times to allow return value to be in 8 bit binary form
    while (temp!=0)
    {
        binaryVal = temp % 2; // get the binary value be getting the remainder of decimal number / 2
        temp = temp / 2;      // divide the decimal number by 2

        if (binaryVal == 0) // check if the binary value is 0
        {
            convertedBinary += "0"; // if so, add a 0 to the binary string
        }
        else if (binaryVal == 1) // check if the binary value is 1
        {
            convertedBinary += "1"; // if so, add a 1 to the binary string
        }
    }

    return convertedBinary; // return the converted binary as a string
}
