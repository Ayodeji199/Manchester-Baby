#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "../file/file.hpp"
#include <iostream>
#include <string>
#include <vector>

enum states
{
    SUCCESS,
    EXPECTED_SEMICOLON,
};

// The whole shabang
int assembly();

// Seperates a line into different components
int splitLine(std::string line, std::vector<std::string> &token);

// =================== ANCHOR - TEST FUNCTIONS ===================

int testTokenization(std::vector<std::string> token);

#endif