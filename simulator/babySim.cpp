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
    int currentInstruction;
    int currentOpcode;
    int accummulator;
    bool stop;

    BabySim();
    vector<string> readInCode();
    int incrementCI(int currentInstruction);
    int fetchAndDecode();
    int getLineNum(string line);
    int getOpcode(string line);
    void doInstruction(string);
};

BabySim::BabySim()
{
    babyMemory = {};
    currentInstruction = 0;
    currentOpcode = 0;
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

int BabySim::incrementCI(int currentInstruction)
{
    currentInstruction++;

    return currentInstruction;
}

int BabySim::fetchAndDecode()
{
    string codeLine = babyMemory[currentInstruction];

    int lineNum = getLineNum(codeLine);// call method to get the line number

    currentOpcode = // call method to get the opcode

    return lineNum;
}

int BabySim::getLineNum(string line)
{
    string lineNumB;

    for (int i = 0; i < 4 ; ++i)
    {
        lineNumB = lineNumB + line[i];
    }

    int num = // call binary to decimal converter

    return num;
}

int BabySim::getOpcode(string line)
{
    string opcode;

    for (int i = 12; i < 15 ; ++i)
    {
        opcode = opcode + line[i];
    }

    int opNum = // call binary to decimal converter

    return opNum;

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

void BabySim::doInstruction() 
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

    switch (currentOpcode)
    {
        case 0: currentInstruction = S;
            break;
        case 1: currentInstruction += S;
            break;
        case 2: accummulator = -S;
            break;
        case 3: S = accummulator;
            break;
        case 4: accummulator -= S;
            break;
        case 5: accummulator -= S;
            break;
        case 6:  
            if (accummulator < 0)
            {
                currentInstruction++;
            }
            break;
        case 7: stop = true;
            break;
        default:
            break;
    }
}

int main()
{
    BabySim obj;

    obj.babyMemory = obj.readInCode();

    obj.doInstruction("011");
    obj.fetchAndDecode();

    cout << obj.currentInstruction << endl;

    return 0;
}
