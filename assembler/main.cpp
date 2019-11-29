#include "assembler.hpp"
#include "../error/error.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "Please make sure to enter the argument type, then value."
		 << endl
		 << "Arguments: [-memsize [INTEGER]] [-readname [STRING]] [-writename [STRING]] [-extended [BOOLEAN(true/false/1/0)]]"
		 << endl
		 << "Examples:" << endl
		 << "./assembler -memsize 64 -extended true" << endl
		 << "./assembler" << endl
		 << "./assembler -extended 0 -readname yourreadname.txt -memsize 64" << endl;

	Assembler assemblerObj = Assembler();
	assemblerObj.assignArgs(assemblerObj.getArgs(argc, argv));
	assemblerObj.assembly();
	return SUCCESS;
}