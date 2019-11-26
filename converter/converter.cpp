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
long long  Bits[32];
int f;
int f1;
int f2;
long long final = 0;
long long decimal = 0;
long long values[10];
long long val[32];
long long lineNumber[10];
string FuncNumber[10];
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
    while (temp != 0)
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

// ***************************************** Deji's Binary to Decimal converter **************************************************************

/**
 * This is the final method that puts the final values of the array into an array.
 **/
void FillFinalArray()
{
    
    long long l = 0;
    for (int i = 0; i < 32; i++)
    {
        
        l = l +(val[i]*Bits[i]);

    }
    // cout<<" Reached counter  is  "<< f <<endl;
    // cout<<" l is  "<< l<<endl;
    values[f]=l;
    f++;
}
// This is the method that calculates the exponents of the array.
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
// This method initialises the array
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
void LineNumber(long long linNum[])
{
    long long m = 0;
    for (int i = 0; i < 5; i++)
    {
        if (linNum[i]<0)
        {
            linNum[i] = 0;
        }
        
        
        m = m +(linNum[i]*Bits[i]);

    }
    lineNumber[f2]=m;
    f2++;
}

void FunctionNumber( string v)
{
    FuncNumber[f1]=v;
    f1++;
}

// This is the method that reads the character file
int CharReader() {
  char letter;
  int i=0;
  int valcn=0;
  long long numCN = 0;
  long long lineNumber1[5];
  string FuncNumber1[3];
  string f;
  ifstream reader("BabyTest1-MC.txt");
  
  if( ! reader ) {
    cout << "Error opening input file" << endl;
    return 1;
  }
   final = 0;

  while(reader.get(letter)) {
   if (letter == '\n')
   {
       FillFinalArray();
       LineNumber(lineNumber1);
       FunctionNumber(f);
       valcn=0;
       numCN = 0;
       f = "";
   }
   else
   {
    char t = letter;
    long long b = 0;
    b = (long long) letter;
    b = b-48;
    val[valcn] = b; 
    if ( numCN <5)
    {
        // cout<< " b is  "<< b <<endl;
        // cout<< " letter  is  "<< letter <<endl;
        // cout<< " number  is  "<< numCN <<endl;
        lineNumber1[numCN]=b;
        numCN++;
    }
    else if (valcn <16 && valcn>12)
    {
        string  s( 1, letter);
        f = f+s;
        // cout<< " letter  is  "<< letter <<endl;
        
    }
    
    valcn++;
   }
  }