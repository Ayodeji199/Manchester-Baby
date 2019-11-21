#include <../converter/converter.hpp>
#include <opcodes.hpp>

using namespace std;

vector<opcode> opcodes;

void storeOpcode(string assembly, int decimal) {
  opcode toStore;
  toStore.assembly = assembly;
  toStore.decimal = decimal;
  toStore.binary = decimalToBinary(decimal);
  opcodes.push_back(toStore);
}

void storeOpcodes() {
  storeOpcode("JMP", 0);
  storeOpcode("JRP", 1);
  storeOpcode("LDN", 2);
  storeOpcode("STO", 3);
  storeOpcode("SUB", 4);
  storeOpcode("CMP", 6);
  storeOpcode("STP", 7);
}