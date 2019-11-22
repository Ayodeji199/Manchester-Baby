#ifndef OPCODES_H
#define OPCODES_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

class Opcodes
{
private:
  std::map<std::string, std::string> table;
  void storeDefaults();

public:
  Opcodes();
  // Returns true if the variable is contained within the Symbols table
  bool isOpcode(string assembly);
  void store(std::string assembly, int decimal);
  std::string getBinary(std::string assembly);
};

#endif