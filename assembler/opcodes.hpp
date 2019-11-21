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
  void store(std::string assembly, int decimal);
  std::string getBinary(std::string assembly);
};