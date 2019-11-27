#include "symbols.hpp"
#include "../converter/converter.hpp"
#include "../error/error.hpp"

using namespace std;

// Constructor
Symbols::Symbols(int memoryWordSize)
{
    this->memoryWordSize = memoryWordSize;
    num = 0;
    freeMemory = 5;
}

// Returns true if the variable is contained within the Symbols table
bool Symbols::isSymbol(string var)
{
    return table.find(var) != table.end();
}

// Stores a 5-bit operand in the symbol table if it hasn't already been stored and assigns it a memory location
int Symbols::storeOperand(string var)
{
    // Checks if the variable is not already in the table
    if (table.find(var) == table.end())
    {
        // Stores the variable with the next free memory location in the table
        // TODO: Uncomment when decimal to binary is written
        table[var] = decimalToBinary(freeMemory, 5);
        // Sets the next free memory location as we have now allocated 32 bits for the variable
        freeMemory += 1;
        //
        num++;
        //
        return true;
    }
    return false;
}

// Stores a 32-bit variable in the symbol table if it hasn't already been stored and assigns it a memory location
int Symbols::storeVar(string var)
{
    // Checks if the variable is not already in the table
    if (table.find(var) == table.end())
    {
        // Stores the variable with the next free memory location in the table
        try
        {
            table[var] = decimalToBinary(stoi(var), 32);
        }
        catch (const std::invalid_argument &)
        {
            checkValidity(INVALID_OPERAND);
        }
        //
        num++;
        //
        return true;
    }
    return false;
}

// Returns the memory location of a variable
string Symbols::get(string var)
{
    return table[var];
}