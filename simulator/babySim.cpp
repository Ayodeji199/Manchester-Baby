#include "../converter/converter.cpp";
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class babySim
{
public:

    vector<string> babyMemory; // Memory for the Baby (RAM)
    int CI;
    int PI;
    int accummulator;
    bool stop;


    babySim();
    vector<string> readInCode();
    int incrementCI(int CI);
    void fetchData();
    void decode();
    void execute();
    
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
        cout<< "Error Opening File, Please try again"<<endl;
        exit(0); // End the program
    }

    // loop until there is no data left in the file
    while(getline(fp, line))
    {
        data.push_back(line);
    }

    fp.close(); // close the file stream

    return data; // return our string
}

int babySim::incrementCI(int CI)
{
    CI++;

    return CI;
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

string parseInstruction(string opcode){
    if (opcode == "000"){
        return "JMP";
    } else if (opcode == "100"){
        return "JRP";
    } else if (opcode == "010"){
        return "LDN";
    } else if (opcode == "110"){
        return "STO";
    } else if (opcode == "001"){
        return "SUB";
    } else if (opcode == "101"){
        return "SUB";
    } else if (opcode == "011"){
        return "CMP";
    } else if (opcode == "111"){
        return "STP";
    } else {
        return "invalid opcode";
    }
}


int main()
{
    babySim obj;

    obj.babyMemory = obj.readInCode();

    int i = 0;

    while(!obj.babyMemory[i].empty())
    {
        cout << obj.babyMemory[i] << endl;
        i++;
    }

    obj.CI = obj.incrementCI(obj.CI);
    obj.fetchData();

    cout << obj.CI << endl;

    return 0;
}


