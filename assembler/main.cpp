#include "assembler.hpp"
#include "../error/error.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	Assembler assemblerObj = Assembler();
	assemblerObj.assignArgs(assemblerObj.getArgs(argc,argv));
	assemblerObj.assembly();
	return SUCCESS;
}

// > CURRENT OUTPUT <
/*
	VAR 0 
	START: LDN NUM01 
	SUB NUM02 
	STO MYSUM 
	LDN MYSUM 
	STO MYSUM 
	END: STP 
	NUM01: VAR 1025 
	NUM02: VAR 621 
	MYSUM: VAR 0
*/