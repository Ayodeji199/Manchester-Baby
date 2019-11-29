/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "opcodes.hpp"
#include "symbols.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Assembler
{
private:
    std::string openFyall;
    std::string saveFyall;
    // Stores the number of words (32-bit integers our memory can store)
    int memoryWordSize;
    bool extendedinstr;
    Opcodes *opcodesObj;
    Symbols *symbolsObj;
    std::vector<std::string> *line;
    std::vector<std::string> *objectCode;

public:
    Assembler();

    // Gets arguments and returns them as a vector
    std::vector<std::string> getArgs(int argc, char *argv[]);

    // If possible, assigns filenames, memory size, extended instruction set arguments values from vector
    void assignArgs(std::vector<std::string> args);

    // If possible, assigns filenames, memory size, extended instruction set arguments values from vector ( NOTE - GUI VERSION )
    void assignArgs(int argc, char *argv);

    // The assembly loop
    void assembly();

    // Seperates a line into different components
    void splitLine(std::string line, std::vector<std::string> &token);

    // Goes through the line and decides what to do with each token
    void processLine(std::vector<std::string> &token);

    // Analyses an individual instruction for the first time to get symbols and verify syntax
    void analyseInstruction(std::string opcodeCandidate, std::string operandCandidate);
    // Prints converted line of code into file
    void printMachineCode(std::string var, std::string opCode, std::ofstream fileOut);
    //
    void genBinary(std::vector<std::string> &token);
    //
    void storeInstruction(std::string opcodeCandidate, std::string operandCandidate);
    //
    std::string calcBlankBits();
    //
    int calcZeros(int number);
    //
    void printVec(std::vector<std::string> &v);
    //
    std::vector<std::string> getObjectCode();

    // Prints converted line of code into file
    void printMachineCode(std::string fileOut);
};

#endif