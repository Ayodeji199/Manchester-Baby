#include <string>
#include <vector>

class BabySim
{

public:
    // potential arguments when executing. otherwise default
    int memoryWordSize;                    // bit size allowed to store in memory
    std::string fyallName = "BabyTest1-MC.txt"; // filename (fyallname xdddddd) to use when reading instructions
    bool extendedInstr;                    // use extended instructions if true, do not if false

    // variables to simulate baby functionality
    std::vector<std::string> babyMemory; // Baby Memory
    int currentInstruction;              // stores the line number of the current instruction
    std::string currentOpcode;           // stores the current opcode as an integer
    int accummulator;                    // the temporary storage of the baby
    int answerLocation;                  // a variable to store the location of our final answer
    bool stop;                           // a boolean to determine if our program is finshed

    BabySim();                // constructor to initialise variables
    BabySim(char* fyallName); // constructor to initialise variables with custom fyallName

    std::vector<std::string> getArgs(int argc, char *argv[]);
    void assignArgs(std::vector<std::string> args);

    std::vector<std::string> readInCode(); // temporary just to get the data

    int incrementCI(int currentInstruction); // increment the CI
    int fetchAndDecode();                    // fetch and decode our line number and opcode
    int getLineNum(std::string line);        // get the line number from a line of source code
    std::string getOpcode(std::string line); // get the opcode from a line of source code
    void babyRun();                          // contains the baby algorithm
    void doInstruction(int);                 // contains the instruction set
    void printMemory();                      // prints the whole memory of the baby
    void printData();                        // prints values of baby
};