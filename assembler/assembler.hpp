#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "opcodes.hpp"
#include "symbols.hpp"
#include "../file/file.hpp"
#include <iostream>
#include <string>
#include <vector>

class Assembler
{
private:
    Opcodes *opcodesObj;
    Symbols *symbolsObj;
    std::vector<std::string> *line;
    std::string filename;
    std::vector<std::string> *objectCode;

public:
    Assembler();
    // The whole shabang
    int assembly();
    //
    int splitLines();
    // Seperates a line into different components
    int splitLine(std::string line, std::vector<std::string> &token);
    //
    int firstPass(std::vector<std::string> &token);
    //
    int analyseInstruction(std::string opcodeCandidate, std::string operandCandidate);

    // =================== ANCHOR - TEST FUNCTIONS ===================
    int testTokenization(std::vector<std::string> token);
};

#endif