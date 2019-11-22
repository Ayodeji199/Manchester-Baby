#include <opcodes.hpp>
#include <../converter/converter.hpp>

using namespace std;

Opcodes::Opcodes() {
  storeDefaults();
}

// Returns true if the variable is contained within the Opcodes table
bool Opcodes::isOpcode(string assembly) {
  return table.find(assembly) != table.end();
}

void Opcodes::store(string assembly, int decimal)
{
  table[assembly] = decimalToBinary(decimal);
}

string Opcodes::getBinary(string assembly)
{
  return table[assembly];
}

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

