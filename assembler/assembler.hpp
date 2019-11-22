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
    // The assembly loop
    void assembly();
    // Seperates a line into different components
    void splitLine(std::string line, std::vector<std::string> &token);
    //
    void processLine(std::vector<std::string> &token);
    //
    void analyseInstruction(std::string opcodeCandidate, std::string operandCandidate);

    // =================== ANCHOR - TEST FUNCTIONS ===================
    void testTokenization(std::vector<std::string> token);
};

#endif