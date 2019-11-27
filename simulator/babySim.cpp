#include "../converter/converter.cpp";
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class babySim // dont use lowercase as the first letter in a class name pls ty - FIXME <---------------
{
public:
    vector<string> babyMemory; // Memory for the Baby (RAM)
    int S;                     // Need to store S into this somehow with error checking
    int CI;
    int PI;
    int accummulator;
    bool stop;

    babySim();
    vector<string> readInCode();
    void fetchData();
    void decode();
    void execute();
    void doInstruction(string);
};

babySim::babySim()
{
    babyMemory = {};
    CI = 0;
    PI = 0;
    accummulator = 0;
}

// read in the data from file given from user if the file exist
vector<string> babySim::readInCode()
{
    string line; // create string to store data from file
    vector<string> data;

    ifstream fp("BabyTest1-MC.txt");

    if (!fp) // check if the file failed to open
    {
        // print error message
        cout << "Error Opening File, Please try again" << endl;
        exit(0); // End the program
    }

    // loop until there is no data left in the file
    while (getline(fp, line))
    {
        data.push_back(line);
    }

    fp.close(); // close the file stream

    return data; // return our string
}

void babySim::fetchData()
{
    string codeLine = babyMemory[CI];
}

void babySim::decode()
{
}

void babySim::execute()
{
}

// void babyRun()
// {
//  // read in data from the file and store into the memory.
//  // NOTE: Memory Space 0 i.e. the first memory location, must remain empty

//  while(stop)
//  {
//      // call methods to run the baby
//      // likly be
//      // increment our CI
//      // fetch data from memory
//      // decode
//      // execute
//      // display everything that is happening
//  }
// }

void babySim::doInstruction(string opcode) // This needs to be made into a case (opcodes will need to be made into enums) because the ifs are disgusting - TODO
{
    if (opcode == "000")
    {
        CI = S;
    }
    else if (opcode == "100")
    {
        CI += S;
    }
    else if (opcode == "010")
    {
        accummulator = -S;
    }
    else if (opcode == "110")
    {
        S = accummulator;
    }
    else if (opcode == "001" || opcode == "101")
    {
        accummulator -= S;
    }
    else if (opcode == "011")
    {
        if (accummulator < 0)
        {
            CI++;
        }
    }
    else if (opcode == "111")
    {
        // idk how to stop ur dumbass code ur screwed lmao
    }
    else
    {
        // idk how to stop ur dumbass code ur screwed lmao
    }
}

int main()
{
    babySim obj;

    obj.babyMemory = obj.readInCode();

    int i = 0;

    while (!obj.babyMemory[i].empty())
    {
        cout << obj.babyMemory[i] << endl;
        i++;
    }

    obj.doInstruction("011");
    obj.fetchData();

    cout << obj.CI << endl;

    return 0;
}
