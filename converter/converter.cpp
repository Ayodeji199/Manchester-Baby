#include "converter.hpp"
#include "../error/error.hpp"
#include <iostream>
#include <locale>
#include <algorithm>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdlib.h> 
using namespace std;
// This is the array that holds the values of two to the 32nd power starting from 1
long long  Bits[32];
/**
 * This is the method that takes in the int,
 *  multiplies it by the exponent of its 
 * current position then adds them together
 */
long long test(long long val[] , int length)
{
    long long m = 0;
    for (int i = 0; i < length; i++)
    {
        m = m + (val[i] * Bits[i]);
    }
    return m;   
}
/**
 * This is the method that helpes to calculate the exponent in the array
 */
long long exponent(int power)
{
    long long base = 1;
    
    long long ex =2;
    for (int i = 0; i < power; i++)
    {
       base = base * ex;
    }
    return base;
}
/**
 *The purpose of this method is to initialise the first 2 values of the array
 */
void Arrayinitilizer()
{
    Bits[0]=1;
    Bits[1]=2;
    for (int i = 2; 0 < 32; i++)
    {
        Bits[i] = exponent(i);
        if (i == 31)
        {
           break;
        }
        
    }
    
}
/**
 * This is the method for the binary conversion 
 * It takes in a string and the length of the string then converts it to binary
 */
long long binaryToDecimal(string bi , int length)
{
    Arrayinitilizer();
    long long finalval = 0;
    long long dumb[32];
        for (int i = 0; i < length; i++)
        {
            int ia = (int)bi[i];
            dumb[i]=ia - 48;
        }
    finalval = test(dumb,length);

    return finalval;
}



string decimalToBinary(long long decimalNum, int bits)
{
    // initialise variables for conversion algorithm
    string convertedBinary;
    long long temp = decimalNum;
    long long binaryVal;
    int i = 0;

    // while loop runs 8 times to allow return value to be in 8 bit binary form
    while (i != bits)
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

        i++;
    }

    cout << convertedBinary << endl;

    return convertedBinary; // return the converted binary as a string
}
