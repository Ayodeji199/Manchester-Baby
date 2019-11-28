#include "../converter/converter.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class BabySim
{

public:
    // potential arguments when executing. otherwise default
    int memoryWordSize; // bit size allowed to store in memory
    string fyallName;   // filename (fyallname xdddddd) to use when reading instructions
    bool extendedInstr; // use extended instructions if true, do not if false

    // variables to simulate baby functionality
    vector<string> babyMemory; // Baby Memory
    int currentInstruction;    // stores the line number of the current instruction
    int currentOpcode;         // stores the current opcode as an integer
    int accummulator;          // the temporary storage of the baby
    int answerLocation;        // a variable to store the location of our final answer
    bool stop;                 // a boolean to determine if our program is finshed

    BabySim(); // constructor to initialise variables

    vector<string> getArgs(int, char *[]);
    void assignArgs(vector<string>);

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
    memoryWordSize = 32;
    fyallName = "BabyTest1-MC.txt";
    extendedInstr = true;

    babyMemory = {};
    currentInstruction = 0;
    currentOpcode = 0;
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

/*=====================================================================================================
	If possible, assigns filename, memory size, extended instruction set arguments values from vector - TODO only the fyallname has been implemented
=====================================================================================================*/
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

int BabySim::incrementCI(int currentInstruction)
{
    currentInstruction++;

    return currentInstruction;
}

int BabySim::fetchAndDecode()
{
    string codeLine = babyMemory[currentInstruction];

    int lineNum = getLineNum(codeLine); // call method to get the line number

    currentOpcode = getOpcode(codeLine); // call method to get the opcode

    return lineNum;
}

int BabySim::getLineNum(string line)
{
    string lineNumB;

    for (int i = 0; i < 5; ++i)
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

    for (int i = 13; i < 16; ++i)
    {
        opcode = opcode + line[i];
    }

    int rp = opcode.size();
    int opNum = binaryConversion(opcode, rp); // call binary to decimal converter

    return opNum;
}

// run the a source code file through the baby
void BabySim::babyRun()
{
    int num = 0;

    cout << "Memory at Start" << endl;
    printMemory();

    while (!stop)
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
    int memItem = binaryConversion(babyMemory[lineNum], stringLength);

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

int main(int argc, char *argv[])
{
    BabySim obj;

    obj.assignArgs(obj.getArgs(argc, argv));

    obj.babyMemory = obj.readInCode();
    obj.babyRun();

    return 0;
}
