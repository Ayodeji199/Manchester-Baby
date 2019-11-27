#include "../converter/converter.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{
public:
    vector<string> babyMemory; // Memory for the Baby (RAM)
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
    void doInstruction(int);
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

    cout << "codeLine: "<< codeLine << endl;

    int lineNum = getLineNum(codeLine);// call method to get the line number

    currentOpcode = getOpcode(codeLine); // call method to get the opcode

    cout << "Line: " << lineNum << endl;
    cout << "Op: " << currentOpcode << endl;

    return lineNum;
}

int BabySim::getLineNum(string line)
{
    string lineNumB;

    for (int i = 0; i < 5 ; ++i)
    {
        lineNumB = lineNumB + line[i];
    }

    cout << "lineNum: " << lineNumB <<endl;

    int rp = lineNumB.size();
    int num = stringtest(lineNumB, rp); // call binary to decimal converter

    return num;
}

int BabySim::getOpcode(string line)
{
    string opcode;

    for (int i = 13; i < 16 ; ++i)
    {
        opcode = opcode + line[i];
    }

    cout << "op string: " << opcode <<endl;

    int rp = opcode.size();
    int opNum = stringtest(opcode, rp); // call binary to decimal converter

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

void BabySim::doInstruction(int lineNum) 
{
    int stringLength = babyMemory[lineNum].size();
    int memItem = stringtest(babyMemory[lineNum] ,stringLength);

    switch (currentOpcode)
    {
        case 0: 
            currentInstruction = memItem;
            break;
        case 1: 
            currentInstruction += memItem;
            break;
        case 2: 
            accummulator = -memItem;
            break;
        case 3: 
            memItem = accummulator;
            break;
        case 4: 
            accummulator -= memItem;
            break;
        case 5: 
            accummulator -= memItem;
            break;
        case 6:  
            if (accummulator < 0)
            {
                currentInstruction++;
            }
            break;
        case 7: 
            stop = true;
            cout << "gay stop" << endl;
            break;
        default:
            break;
    }
}

int main()
{
    BabySim obj;

    obj.babyMemory = obj.readInCode();
    obj.currentInstruction = obj.incrementCI(obj.currentInstruction);

    int num = obj.fetchAndDecode();

    obj.doInstruction(num);

    cout << "current accum: "<< obj.accummulator <<endl;

    return 0;
}
