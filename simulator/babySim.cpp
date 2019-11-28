#include "../converter/converter.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{

public:
    string fileToRead;
    // variables to simulate baby functionality
    vector<string> babyMemory; // Baby Memory
    int currentInstruction; // stores the line number of the current instruction
    string currentOpcode; // stores the current opcode as an integer
    int accummulator; // the temporary storage of the baby
    int answerLocation; // a variable to store the location of our final answer
    bool stop; // a boolean to determine if our program is finshed

    BabySim(); // constructor to initialise variables

    vector<string> readInCode(); // temporary just to get the data
    
    int incrementCI(int currentInstruction); // increment the CI
    int fetchAndDecode(); // fetch and decode our line number and opcode
    int getLineNum(string line); // get the line number from a line of source code
    string getOpcode(string line); // get the opcode from a line of source code
    void babyRun(); // contains the baby algorithm
    void doInstruction(int); // contains the instruction set
    void printMemory(); // prints the whole memory of the baby
    void printData(); // prints values of baby
};

/*
    Constructor
*/
BabySim::BabySim()
{
    // set default values
    babyMemory = {};
    currentInstruction = 0;
    currentOpcode = " ";
    accummulator = 0;
    answerLocation = 0;
    stop = false;
}

// read in the data from file given from user if the file exist
vector<string> BabySim::readInCode()
{
    string line; // create string to store data from file
    vector<string> data;

    ifstream fp(fileToRead);

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

/*
    Increment the current instruction to tell the baby what line to look at in memory
*/
int BabySim::incrementCI(int currentInstruction)
{
    currentInstruction++; // add one to variable

    return currentInstruction; // return integer value
}

/*
    Fetch and decode data from a line of machine code
*/
int BabySim::fetchAndDecode()
{
    string codeLine = babyMemory[currentInstruction]; // get our line of machine code

    int lineNum = getLineNum(codeLine);// call method to get the line number

    currentOpcode = getOpcode(codeLine); // call method to get the opcode

    return lineNum; // return our line number for use later on
}


/*
    Retreive the line number from line of machine code
*/
int BabySim::getLineNum(string line)
{
    string lineNumB; // create temporary variable

    // get the data we need from the line of machine code
    for (int i = 0; i < 5 ; ++i)
    {
        lineNumB = lineNumB + line[i];
    }

    int size = lineNumB.size(); // get the size of our string
    int num = binaryToDecimal(lineNumB, size); // call binary to decimal converter


    // check if the line number we have aquired is outwith our maximum memory
    if (num > babyMemory.size())
    {
        cout << "INVALID OPERATION - YOU HAVE RAN OUT OF MEMORY" << endl;
        exit(0);
    }

    return num; // return our line number as integer
}

/*
    Get the opcode from line of machine code
*/
string BabySim::getOpcode(string line)
{
    string opcode; // create temporary variable

    // get the data we need from the line of machine code
    for (int i = 13; i < 16 ; ++i)
    {
        opcode = opcode + line[i];
    }

    return opcode; // return our opcode as string

}

/*
    Run a source code through the baby
*/
void BabySim::babyRun()
{
    // check if our memory vector is empty
    if (babyMemory.empty())
    {
        cout << "MEMORY IS EMPTY - PLEASE CHECK YOUR SOURCE CODE" << endl;
        exit(0);
    }

    // create variable to store line number
    int num = 0;

    cout << "Memory at Start" << endl; // print message to show what the baby's memory is at the start of the program
    printMemory(); // print the current state of the memory

    while(!stop) // while stop is false i.e. we haven't been told to stop
    {  
        // increment the CI
        currentInstruction = incrementCI(currentInstruction);

        // get our opcode and line number. Line number is store in num variable
        num = fetchAndDecode();

        // go to the instruction set to carry out our instruction based on our current opcode
        doInstruction(num);

        // print the baby memory after a cycle has finished
        printMemory();

        // print the values of baby variables
        printData();

    }

     int length = babyMemory[answerLocation].size(); // get the length our final answer's binary

     // print the final answer in decimal format
     cout << "Final Answer: " << binaryToDecimal(babyMemory[answerLocation], length) << endl;
}

/*
    Performs instructions based on what the current opcode is
*/
void BabySim::doInstruction(int lineNum) 
{
    // get the length of our string in memory
    int stringLength = babyMemory[lineNum].size();

    // get the decimal number we require
    int memItem = binaryToDecimal(babyMemory[lineNum] ,stringLength);
    cout << "memitem is " << memItem << endl;

    // convert our opcode to a decimal number to use it for comparisons
    int convertedOpcode = binaryToDecimal(currentOpcode, currentOpcode.size());

    // use our decimal opcode for conversion
    switch (convertedOpcode)
    {
        case 0: // set current instruction to content of store location
            currentInstruction = memItem;
            break;
        case 1: // add content of store location to current instruction
            currentInstruction += memItem;
            break;
        case 2: // load data from store location in accumulator
            accummulator = -memItem;
            break;
        case 3: // store value from accumulator into storage
            babyMemory[lineNum] = decimalToBinary(accummulator, 32);
            answerLocation = lineNum;
            break;
        case 4: // subtract content of store location from accumulator
            accummulator -= memItem;
            break;
        case 5: // same as 4
            accummulator -= memItem;
            break;
        case 6: // increment current instruction if accumulator value is negative
            if (accummulator < 0)
            {
                currentInstruction++;
            }
            break;
        case 7: // stop program
            stop = true;
            break;
        default:
            // if we get an invalid opcode, print an error message and stop the program 
            cout << "INVALID OPCODE DETECTED - PLEASE CHECK YOUR SOURCE CODE FILE" << endl;
            exit(0);
            break;
    }
}

/*
    Print the everything in the baby's memory
*/
void BabySim::printMemory()
{
    cout << "Data in Memory" << endl;

    // print each line of our string vector
    for (int i = 0; i < babyMemory.size(); ++i)
    {
        cout << babyMemory[i] << endl;
    }

    cout << endl;
}

/*
    Print the current state of the CI, opcode, Accummulator and stop variables
*/
void BabySim::printData()
{
    // print our data
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
