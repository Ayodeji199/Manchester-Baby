#include "../converter/converter.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{

public:
    // variables to simulate baby functionality
    vector<string> babyMemory; // Baby Memory
    int currentInstruction; // stores the line number of the current instruction
    int currentOpcode; // stores the current opcode as an integer
    int accummulator; // the temporary storage of the baby
    int answerLocation; // a variable to store the location of our final answer
    bool stop; // a boolean to determine if our program is finshed

    BabySim(); // constructor to initialise variables

    vector<string> readInCode();
    
    int incrementCI(int currentInstruction);
    int fetchAndDecode();
    int getLineNum(string line);
    int getOpcode(string line);
    void babyRun();
    void doInstruction(int);
    void printMemory();
    void printData();
};

BabySim::BabySim()
{
    babyMemory = {};
    currentInstruction = 0;
    currentOpcode = 0;
    accummulator = 0;
    answerLocation = 0;
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

    currentOpcode = getOpcode(codeLine); // call method to get the opcode

    return lineNum;
}

int BabySim::getLineNum(string line)
{
    string lineNumB;

    for (int i = 0; i < 5 ; ++i)
    {
        lineNumB = lineNumB + line[i];
    }

    int rp = lineNumB.size();
    int num = binaryConversion(lineNumB, rp); // call binary to decimal converter

    return num;
}

int BabySim::getOpcode(string line)
{
    string opcode;

    for (int i = 13; i < 16 ; ++i)
    {
        opcode = opcode + line[i];
    }

    int rp = opcode.size();
    int opNum = binaryConversion(opcode, rp); // call binary to decimal converter

    return opNum;

}

void BabySim::babyRun()
{
    int num = 0;

    cout << "Memory at Start" << endl;
    printMemory();

    while(!stop)
    {

        currentInstruction = incrementCI(currentInstruction);
        num = fetchAndDecode();
        doInstruction(num);
        printMemory();
        printData();

    }

     int length = babyMemory[answerLocation].size();
     cout << "Final Answer: " << binaryConversion(babyMemory[answerLocation], length) << endl;
}

void BabySim::doInstruction(int lineNum) 
{
    int stringLength = babyMemory[lineNum].size();
    int memItem = binaryConversion(babyMemory[lineNum] ,stringLength);

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
            babyMemory[lineNum] = decimalConversion(-(accummulator));
            answerLocation = lineNum;
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
            break;
        default:
            break;
    }
}

void BabySim::printMemory()
{
    cout << "Data in Memory" << endl;

    for (int i = 0; i < babyMemory.size(); ++i)
    {
        cout << babyMemory[i] << endl;
    }
     cout << endl;
}

void BabySim::printData()
{
    cout << "The Current line we are getting instructions from: " << currentInstruction << endl;
    cout << "The Current Opcode: " << currentOpcode << endl;
    cout << "The Current state of the accummulator: " << accummulator << endl;
    cout << "Current state of stop: " << stop << endl;
    cout << endl;
}

int main()
{
    BabySim obj;

    obj.babyMemory = obj.readInCode();
    obj.babyRun();

    return 0;
}
