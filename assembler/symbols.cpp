#include "symbols.hpp"

using namespace std;

// Constructor
Symbols::Symbols()
{
    num = 0;
    freeMemory = 0;
}

// Returns true if the variable is contained within the Symbols table
bool Symbols::isSymbol(string var)
{
    return table.find(var) != table.end();
}

// Stores a 32-bit variable in the symbol table if it hasn't already been stored and assigns it a memory location
int Symbols::storeVar(string var)
{
    // Checks if the variable is not already in the table
    if (table.find(var) == table.end())
    {
        // Stores the variable with the next free memory location in the table
        table[var] = freeMemory;
        // Sets the next free memory location as we have now allocated 32 bits for the variable
        freeMemory += 32;
        //
        num++;
        //
        return true;
    }
    return false;
}

// Returns the memory location of a variable
int Symbols::get(string var)
{
    return table[var];
}