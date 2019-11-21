#include <string>
#include <vector>

struct opcode {
  std::string assembly;
  std::string binary;
  int decimal;
};

void storeOpcode(std::string assembly, int decimal);