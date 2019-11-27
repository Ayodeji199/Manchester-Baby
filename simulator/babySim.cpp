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
    void babyRun();
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

    int rp = opcode.size();
    int opNum = stringtest(opcode, rp); // call binary to decimal converter

    return opNum;

}

void BabySim::babyRun()
{
    int num = 0;

     while(!stop)
     {

        currentInstruction = incrementCI(currentInstruction);
        num = fetchAndDecode();
        doInstruction(num);

     }

     cout << babyMemory[9] << endl;
     int length = babyMemory[9].size();
     cout << stringtest(babyMemory[9], length) << endl;
}

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
            cout << "Current Acum: "<< accummulator << endl; 
            break;
        case 3: 
            cout << "Current Acum: "<< accummulator << endl;
            babyMemory[lineNum] = decimalConversion(-(accummulator));
            cout << decimalConversion(accummulator) << endl;
            cout << "Stored: " << babyMemory[lineNum] <<endl;
            break;
        case 4: 
            accummulator -= memItem;
            cout << "Current Acum: "<< accummulator << endl;
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
    obj.babyRun();

    return 0;
}
