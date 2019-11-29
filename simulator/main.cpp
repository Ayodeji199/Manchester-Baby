#include "babySim.hpp"
#include <iostream>
#include "../file/file.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Please make sure to enter the argument type, then value."
         << endl
         << "Arguments: [-memsize [INTEGER]] [-readname [STRING]] [-extended [BOOLEAN(true/false/1/0)]]"
         << endl
         << "Examples:" << endl
         << "./simulator -memsize 64 -extended true" << endl
         << "./simulator" << endl
         << "./simulator -extended 0 -readname yourreadname.txt -memsize 64" << endl;

    BabySim obj = BabySim();

    obj.assignArgs(obj.getArgs(argc, argv));
    loadFile(obj.babyMemory, obj.fyallName);

    obj.babyRun();
}