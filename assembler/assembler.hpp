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
    // Stores the path of the assembly file we are loading from
    std::string openFyall;
    // Stores the path of the binary file we are saving to
    std::string saveFyall;
    // Stores the number of words (32-bit binary) our memory can store
    int memoryWordSize;
    // Stores a pointer to the opcodes object used to manage opcodes
    Opcodes *opcodesObj;
    // Stores a pointer to the symbols object used to manage user-defined variables
    Symbols *symbolsObj;
    // Stores each line of the assembly file we are loading from
    std::vector<std::string> *line;
    // Stores each line of the binary code we are producing
    std::vector<std::string> *objectCode;

public:
    // Constructor
    Assembler();
    // Gets arguments and returns them as a vector
    std::vector<std::string> getArgs(int argc, char *argv[]);
    // The assembly loop
    void assembly();

    // Seperates a line into different components
    void splitLine(std::string line, std::vector<std::string> &token);
    // Goes through the line and decides what to do with each token
    void processLine(std::vector<std::string> &token);
    // Analyses an individual instruction for the first time to get symbols and verify syntax
    void analyseInstruction(std::string opcodeCandidate, std::string operandCandidate);
    
    // TODO: One of two save file methods
    // Prints converted line of code into file
    void printMachineCode(std::string var, std::string opCode, std::ofstream fileOut);
    // Prints converted line of code into file
    void printMachineCode(std::string fileOut);

    // Generates and stores object code for a particular line
    void genBinary(std::vector<std::string> &token);
    // 
    void storeInstruction(std::string opcodeCandidate, std::string operandCandidate);

    //
    std::string calcBlankBits();
    // 
    int calcZeros(int number);

    // Prints a vector to the screen
    void printVec(std::vector<std::string> &v);
    // Getter for the object code vector which stores the binary output
    std::vector<std::string> getObjectCode();

};

#endif