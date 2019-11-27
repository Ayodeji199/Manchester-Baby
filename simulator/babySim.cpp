#include "../converter/converter.cpp";
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{
public:
    vector<string> babyMemory; // Memory for the Baby (RAM)
    int S;                     // Need to store S into this somehow with error checking
    int CI;
    string PI;
    int accummulator;
    bool stop;

    BabySim();
    vector<string> readInCode();
    int incrementCI(int CI);
    int fetchAndDecode();
    void doInstruction(string);
};

BabySim::BabySim()
{
    babyMemory = {};
    CI = 0;
    PI = " ";
    accummulator = 0;
    stop = false;
}

// read in the data from file given from user if the file exist
vector<string> BabySim::readInCode()
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

int BabySim::incrementCI(int CI)
{
    CI++;

    return CI;
}

int BabySim::fetchAndDecode()
{
    string codeLine = babyMemory[CI];

    int lineNum = getLine(codeLine);// call method to get the line number

    PI = // call method to get the opcode

    return lineNum;
}

int BabySim::getLine(string line)
{
    string lineNumB;

    for (int i = 0; i < 4 ; ++i)
    {
        lineNumB = lineNumB + line[i];
        cout << lineNumB << endl;
    }

    return 0;
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

void BabySim::doInstruction(string opcode) // This needs to be made into a case (opcodes will need to be made into enums) because the ifs are disgusting - TODO
{
    // if (opcode == "000")
    // {
    //     CI = S;
    // }
    // else if (opcode == "100")
    // {
    //     CI += S;
    // }
    // else if (opcode == "010")
    // {
    //     accummulator = -S;
    // }
    // else if (opcode == "110")
    // {
    //     S = accummulator;
    // }
    // else if (opcode == "001" || opcode == "101")
    // {
    //     accummulator -= S;
    // }
    // else if (opcode == "011")
    // {
    //     if (accummulator < 0)
    //     {
    //         CI++;
    //     }
    // }
    // else if (opcode == "111")
    // {
    //     stop = true;
    // }
    // else
    // {
    //     // idk how to stop ur dumbass code ur screwed lmao
    // }

    switch (opcode)
    {
        case "000": CI = S;
            break;
        case "100": CI += S;
            break;
        case "010": accummulator = -S;
            break;
        case "110": S = accummulator;
            break;
        case "001": accummulator -= S;
            break;
        case "101": accummulator -= S;
            break;
        case "011":  
        if (accummulator < 0)
        {
            CI++;
        }
            break;
        case "111": stop = true;
            break;
        default:
            break;
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
