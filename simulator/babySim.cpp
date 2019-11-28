#include "../converter/converter.cpp"
#include "../error/error.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{

public:
    // potential arguments when executing. otherwise default
    int memoryWordSize;               // bit size allowed to store in memory
    string fyallName = "Subtraction"; // filename (fyallname xdddddd) to use when reading instructions
    bool extendedInstr;               // use extended instructions if true, do not if false

    // variables to simulate baby functionality
    vector<string> babyMemory; // Baby Memory
    int currentInstruction;    // stores the line number of the current instruction
    string currentOpcode;      // stores the current opcode as an integer
    int accummulator;          // the temporary storage of the baby
    int answerLocation;        // a variable to store the location of our final answer
    bool stop;                 // a boolean to determine if our program is finshed

    BabySim(); // constructor to initialise variables

    vector<string> getArgs(int argc, char *argv[]);
    void assignArgs(vector<string> args);
    void assignArgs(int argc, char *argv[]);

    vector<string> readInCode(); // temporary just to get the data

    int incrementCI(int currentInstruction); // increment the CI
    int fetchAndDecode();                    // fetch and decode our line number and opcode
    int getLineNum(string line);             // get the line number from a line of source code
    string getOpcode(string line);           // get the opcode from a line of source code
    void babyRun();                          // contains the baby algorithm
    void doInstruction(int);                 // contains the instruction set
    void printMemory();                      // prints the whole memory of the baby
    void printData();                        // prints values of baby
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

/*==============================================
	Gets arguments and returns them as a vector
==============================================*/
vector<string> BabySim::getArgs(int argc, char *argv[])
{
    vector<string> args = {}; // initialize the empty vector
    // go through each argument
    for (int i = 1; i < argc; i++)
    {
        // if argument isn't NULL
        if (argv[i] != NULL)
        {
            // add argument to the vector
            args.push_back(argv[i]);
            cout << "add_arg<" << argv[i] << ">" << endl;
        }
    }

    return args;
}

/*====================================================================================================
	If possible, assigns filename, memory size, extended instruction set arguments values from vector
====================================================================================================*/
void BabySim::assignArgs(vector<string> args)
{
    // if the amount of arguments is divisable by 2 and is equal or less than 6 (which would be 3 flags with a value each)
    if ((int)args.size() % 2 == 0 && (int)args.size() <= 6)
    {
        // for every flag
        for (int i = 0; i < (int)args.size(); i = i + 2)
        {
            // if the flag is -memsize
            if (args.at(i) == "-memsize")
            {
                // if the size to set isn't another flag (and isn't negative)
                if (args.at(i)[0] != '-')
                    try
                    {
                        // try to parse the integer
                        memoryWordSize = stoi(args.at(i + 1));
                        //if the size entered is less than 32 or more than 8192
                        if (memoryWordSize < 32 || memoryWordSize > 8192)
                        {
                            // display error
                            checkValidity(INVALID_MEMORY_SIZE);
                        }
                    }
                    catch (invalid_argument &e)
                    {
                        // display error if the value entered isn't an integer
                        checkValidity(INVALID_FILENAME);
                    }
                    catch (out_of_range &e)
                    {
                        // display error if the value entered is too big for a non-long integer
                        checkValidity(INVALID_MEMORY_SIZE);
                    }
            }

            // if the flag is -readname
            else if (args.at(i) == "-readname")
            {
                // assign name of fyall to read from (hehe max fyall get it)
                fyallName = args.at(i + 1);
            }

            // if the flag is -extended
            else if (args.at(i) == "-extended")
            {
                // if the value after is true/false/1/0
                if (args.at(i + 1) == "true" || args.at(i + 1) == "false" || args.at(i + 1) == "1" || args.at(i + 1) == "0")
                {
                    // assign if the extended instruction set should be used
                    istringstream(args.at(i + 1)) >> extendedInstr;
                }
                else
                {
                    // if it's not true/false/1/0, display error
                    checkValidity(INVALID_INPUT_PARAMETER);
                }
            }
        }
    }
    else
    {
        // display error
        checkValidity(INVALID_NUMBER_OF_ARGS);
    }
}

// This is essentially a combined verson of getArgs and assignArgs to make it work in the GUI
/*====================================================================================================
	If possible, assigns filename, memory size, extended instruction set arguments values from vector ( NOTE - GUI VERSION )
====================================================================================================*/
void BabySim::assignArgs(int argc, char *argv[])
{
    vector<string> args = {}; // initialize the empty vector
    // go through each argument
    for (int i = 1; i < argc; i++)
    {
        // if argument isn't NULL
        if (argv[i] != NULL)
        {
            // add argument to the vector
            args.push_back(argv[i]);
            cout << "add_arg<" << argv[i] << ">" << endl;
        }
    }

    // if the amount of arguments is divisable by 2 and is equal or less than 6 (which would be 3 flags with a value each)
    if ((int)args.size() % 2 == 0 && (int)args.size() <= 6)
    {
        // for every flag
        for (int i = 0; i < (int)args.size(); i = i + 2)
        {
            // if the flag is -memsize
            if (args.at(i) == "-memsize")
            {
                // if the size to set isn't another flag (and isn't negative)
                if (args.at(i)[0] != '-')
                    try
                    {
                        // try to parse the integer
                        memoryWordSize = stoi(args.at(i + 1));
                        //if the size entered is less than 32 or more than 8192
                        if (memoryWordSize < 32 || memoryWordSize > 8192)
                        {
                            // display error
                            checkValidity(INVALID_MEMORY_SIZE);
                        }
                    }
                    catch (invalid_argument &e)
                    {
                        // display error if the value entered isn't an integer
                        checkValidity(INVALID_FILENAME);
                    }
                    catch (out_of_range &e)
                    {
                        // display error if the value entered is too big for a non-long integer
                        checkValidity(INVALID_MEMORY_SIZE);
                    }
            }

            // if the flag is -readname
            else if (args.at(i) == "-readname")
            {
                // assign name of fyall to read from (hehe max fyall get it)
                fyallName = args.at(i + 1);
            }

            // if the flag is -extended
            else if (args.at(i) == "-extended")
            {
                // if the value after is true/false/1/0
                if (args.at(i + 1) == "true" || args.at(i + 1) == "false" || args.at(i + 1) == "1" || args.at(i + 1) == "0")
                {
                    // assign if the extended instruction set should be used
                    istringstream(args.at(i + 1)) >> extendedInstr;
                }
                else
                {
                    // if it's not true/false/1/0, display error
                    checkValidity(INVALID_INPUT_PARAMETER);
                }
            }
        }
    }
    else
    {
        // display error
        checkValidity(INVALID_NUMBER_OF_ARGS);
    }
}

// read in the data from file given from user if the file exist
vector<string> BabySim::readInCode()
{
    string line; // create string to store data from file
    vector<string> data;

    ifstream fp(fyallName);

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

    int lineNum = getLineNum(codeLine); // call method to get the line number

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
    for (int i = 0; i < 5; ++i)
    {
        lineNumB = lineNumB + line[i];
    }

    int size = lineNumB.size();                // get the size of our string
    int num = binaryToDecimal(lineNumB, size); // call binary to decimal converter

    // check if the line number we have aquired is outwith our maximum memory
    if (num > babyMemory.size())
    {
        checkValidity(INVALID_INPUT_PARAMETER);
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
    for (int i = 13; i < 16; ++i)
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
        checkValidity(MEMORY_EMPTY);
        exit(0);
    }

    if (babyMemory.size() > 32 /* this can be change to a defined varible when we get there */)
    {
        checkValidity(INVALID_MEMORY_SIZE);
        exit(0);
    }

    for (int i = 0; i < babyMemory.size(); ++i)
    {
        if (babyMemory[i].size() > 33 /* this can be change to a defined variable when we get there*/)
        {
            checkValidity(MEMORY_OVERLOAD);
            exit(0);
        }
    }

    // create variable to store line number
    int num = 0;

    int cycleNum = 0; // create variable to keep track of the number of cycles

    // print messages
    cout << "PROGRAM START" << endl;
    cout << endl;
    cout << "Memory Initialised:" << endl;

    printMemory(); // print the current state of the memory

    while (!stop) // while stop is false i.e. we haven't been told to stop
    {
        // increment the CI
        currentInstruction = incrementCI(currentInstruction);

        // get our opcode and line number. Line number is store in num variable
        num = fetchAndDecode();

        // go to the instruction set to carry out our instruction based on our current opcode
        doInstruction(num);

        cycleNum++; //

        cout << "Cycle " << cycleNum << " Finished" << endl;
        cout << endl;

        // print the baby memory after a cycle has finished
        printMemory();

        // print the values of baby variables
        printData();
    }

    int length = babyMemory[answerLocation].size(); // get the length our final answer's binary

    cout << "PROGRAM FINISHED" << endl;
    cout << endl;

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
    int memItem = binaryToDecimal(babyMemory[lineNum], stringLength);

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
        checkValidity(INVALID_OPCODE);
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
    cout << "The CI: " << currentInstruction << endl;
    cout << "The Opcode: " << currentOpcode << endl;
    cout << "The Accummulator: " << accummulator << endl;
    cout << "Stop: " << stop << endl;
    cout << endl;
}

int main(int argc, char *argv[])
{
    BabySim obj;

    obj.assignArgs(obj.getArgs(argc, argv));

    obj.babyMemory = obj.readInCode();
    obj.babyRun();
}
