#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <string>
#include <map>
#include <unordered_map>

// Stores memory locations of user defined variables
class Symbols
{
private:
    // Stores the symbols as a map which is essentially a hash table
    std::map<std::string, std::string> table;
    // Stores the number of items stored in the table and the number of memory locations we've used
    int num;
    // Stores the next free memory location to allocate data to in decimal
    int freeMemory;

public:
    // Constructor
    Symbols();
    // Returns true if the variable is contained within the Symbols table
    bool isSymbol(std::string var);
    // Stores a 32-bit variable in the symbol table if it hasn't already been stored and assigns it a memory location
    bool storeVar(std::string var);
    // Returns the memory location of a variable
    std::string get(std::string var);
};

#endif
