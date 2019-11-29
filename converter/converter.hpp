/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "../error/error.hpp"
#include <iostream>
#include <locale>
#include <algorithm>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <iomanip>
#include <stdlib.h> 

long long binaryArrarytoDecimal(long long val[] , int length);
long long exponent(int power);
void Arrayinitilizer();
long long binaryToDecimal(std::string binary, int length);

std::string decimalToBinary(long long decimal, int bits);

#endif