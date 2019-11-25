#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>

int binaryToDecimal(std::string binary);
int binaryToHex(int hex);

std::string decimalToBinary(int decimal, int bits);
int decimalToHex(int decimal);

std::string hexToBinary(int hex);
int hexToDecimal(int hex);

#endif