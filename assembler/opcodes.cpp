#include <opcodes.hpp>
#include <../converter/converter.hpp>

using namespace std;

vector<opcode> opcodes;

void storeOpcode(string assembly, int decimal) {
    opcode toStore;
    toStore.assembly = assembly;
    toStore.decimal = decimal;
    toStore.binary = decimalToBinary(decimal);
    opcodes.push_back(toStore);
}