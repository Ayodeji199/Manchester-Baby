#include "symbols.hpp"
#include "../converter/converter.hpp"

using namespace std;

// Constructor
Symbols::Symbols()
{
    // Initialises the table
    table = map<string,string>();
    // Stores the number of items stored in the table and the number of memory locations we've used
    num = 0;
    // Stores the next free memory location to allocate data to in decimal
    freeMemory = 0;
}

// Returns true if the variable is contained within the Symbols table
bool Symbols::isSymbol(string var)
{
    return table.find(var) != table.end();
}

// Stores a 32-bit variable in the symbol table if it hasn't already been stored and assigns it a memory location
bool Symbols::storeVar(string var)
{
    // Checks if the variable is not already in the table
    if (table.find(var) == table.end())
    {
        // Stores the variable with the next free memory location in the table
        table[var] = decimalToBinary(freeMemory, 32);
        // Sets the next free memory location as we have now allocated 32 bits for the variable
        freeMemory += 32;
        // Increments the number of items stored on the table
        num++;
        // Returns true since we have stored the variable
        return true;
    }
    // Returns false since we have not stored the variable
    return false;
}

// Returns the memory location of a variable
string Symbols::get(string var)
{
    return table[var];
}