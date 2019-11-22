#include <opcodes.hpp>
#include <../converter/converter.hpp>

using namespace std;

// Constructor
Opcodes::Opcodes() {
  storeDefaults();
}

// Returns true if the variable is contained within the Opcodes table
bool Opcodes::isOpcode(string assembly) {
  return table.find(assembly) != table.end();
}

// Stores an opcode in the table
void Opcodes::store(string assembly, int decimal)
{
  table[assembly] = decimalToBinary(decimal);
}

// Returns the binary value for an opcode stored in the table
string Opcodes::getBinary(string assembly)
{
  return table[assembly];
}

// Stores the Manchester Baby's default opcodes in the table
void Opcodes::storeDefaults()
{
  store("JMP", 0);
  store("JRP", 1);
  store("LDN", 2);
  store("STO", 3);
  store("SUB", 4);
  store("CMP", 6);
  store("STP", 7);
}

