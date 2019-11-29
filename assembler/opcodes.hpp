/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

#ifndef OPCODES_H
#define OPCODES_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

// Stores and manages opcodes for the Manchester Baby
class Opcodes
{
private:
  // Stores the opcodes we can process
  std::map<std::string, std::string> table;
  // Stores the Manchester Baby's default opcodes in the table
  void storeDefaults();

public:
  // Constructor
  Opcodes(bool extendedinstr);
  // Returns true if the variable is contained within the Symbols table
  bool isOpcode(std::string assembly);
  // Stores an opcode in the table
  void store(std::string assembly, int decimal);
  // Returns the binary value for an opcode stored in the table
  std::string getBinary(std::string assembly);
};

#endif