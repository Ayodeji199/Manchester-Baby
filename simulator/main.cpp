#include "babySim.hpp"
#include "../file/file.hpp"

// using namespace std;

extern "C"
{
    int main(int argc, char *argv[])
    {
        BabySim obj = BabySim("simulator/Subtraction");

        obj.assignArgs(obj.getArgs(argc, argv));
        loadFile(obj.babyMemory, obj.fyallName);

        obj.babyRun();
    }
}