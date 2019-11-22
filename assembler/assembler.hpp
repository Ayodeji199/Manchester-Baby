
#include "../file/file.hpp"
#include <iostream>
#include <string>
#include <vector>

enum states
{
    SUCCESS,
    EXPECTED_SEMICOLON,
};

// Seperates a line into different components
int splitLine(std::string line, std::vector<std::string> &token);