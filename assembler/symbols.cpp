#include "symbols.hpp"

using namespace std;

// Constructor
Symbols::Symbols()
{
    num = 0;
}

// Stores a variable in the symbol table if it hasn't already been stored and assigns it a memory location
int Symbols::store(string var)
{
    // Checks if the variable is not already in the table
    if (table.find(var) == table.end())
    {
        // Stores the variable in the table
        table[var] = num;
    }
}

// Returns the memory location of a variable
int Symbols::get(string var)
{
    return table[var];
}