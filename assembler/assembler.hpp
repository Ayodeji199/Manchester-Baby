#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "opcodes.hpp"
#include "symbols.hpp"
#include <iostream>
#include <string>
#include <vector>

class Assembler
{
private:
    std::string filename;
    // Stores the number of words (32-bit integers our memory can store)
    int memoryWordSize;
    Opcodes *opcodesObj;
    Symbols *symbolsObj;
    std::vector<std::string> *line;
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
    //
    void genBinary(std::vector<std::string> &token);
    //
    void storeInstruction(std::string opcodeCandidate, std::string operandCandidate);
    //
    std::string calcBlankBits();
    //
    int calcZeros(int number);

    // =================== ANCHOR - TEST FUNCTIONS ===================
    void testTokenization(std::vector<std::string> token);
};

#endif