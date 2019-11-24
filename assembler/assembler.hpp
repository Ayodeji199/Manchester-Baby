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
    std::string filenameOut;
    // Stores the number of words (32-bit integers our memory can store)
    int memoryWordSize;
    Opcodes *opcodesObj;
    Symbols *symbolsObj;
    std::vector<std::string> *line;
    std::vector<std::string> *objectCode;

public:
    Assembler();

    //Gets arguments and returns them as a vector
    std::vector<std::string> getArgs(int argc, char *argv[]);

    // The assembly loop
    void assembly();

    // Seperates a line into different components
    void splitLine(std::string line, std::vector<std::string> &token);

    // Goes through the line and decides what to do with each token
    void processLine(std::vector<std::string> &token);

    // Analyses an individual instruction for the first time to get symbols and verify syntax
    void analyseInstruction(std::string opcodeCandidate, std::string operandCandidate);
    //
    void genBinary(std::vector<std::string> &token);
    //
    void storeInstruction(std::string opcodeCandidate, std::string operandCandidate);
    //
    std::string calcBlankBits();
    //
    int calcZeros(int number);

    // Prints converted line of code into file
    void printMachineCode(std::string fileOut);
};

#endif