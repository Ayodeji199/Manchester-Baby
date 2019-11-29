/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

#include "opcodes.hpp"
#include "../converter/converter.hpp"

using namespace std;

// Constructor
Opcodes::Opcodes(bool extendedinstr)
{
  table = map<string,string>();
  storeDefaults();
  if (extendedinstr)
  {
    store("ADD",8);
  }
}

// Returns true if the variable is contained within the Opcodes table
bool Opcodes::isOpcode(string assembly)
{
  return table.find(assembly) != table.end();
}

// Stores an opcode in the table
void Opcodes::store(string assembly, int decimal)
{
  // TODO: Uncomment line when decimal to binary method is written
  table[assembly] = decimalToBinary(decimal, 3);
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
