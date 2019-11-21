#include <string>
#include <map>
#include <unordered_map>

// Stores memory locations of user defined variables
class Symbols
{
private:
    // Stores the symbols as a map which is essentially a hash table
    std::map<std::string, int> table;
    // Stores the number of items stored in the table and the number of memory locations we've used
    int num;

public:
    // Constructor
    Symbols();
    // Stores a variable in the symbol table if it hasn't already been stored and assigns it a memory location
    int store(std::string var);
    // Returns the memory location of a variable
    int get(std::string var);
};
