#include "assembler.hpp"
#include "opcodes.hpp"
#include "symbols.hpp"

using namespace std;

int main()
{
	vector<string> line = {};					 // vector to store lines
	string filename = "BabyTest1-Assembler.txt"; // REVIEW - potential string for user input
	loadFile(line, filename);					 // load file and store lines into vector

	for (int i = 0; i < (int)line.size(); i++) // go through each line
	{
		// TODO - this is gonna be the assembly loop

		vector<string> token = {};	// create vector to store the line's components
		splitLine(line.at(i), token); // separates a line into different components

		// loop for testing. outputs the line's tokens (components) separated by spaces
		for (int j = 0; j < (int)token.size(); j++)
		{
			cout << token.at(j) << " ";
		}
		// at the end of the test loop, output \n
		if ((int)token.size() != 0)
		{
			cout << endl;
		}
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

	Opcodes opcodesObj = Opcodes();
	Symbols symbolsObj = Symbols();

	return 0;
}

/*=============================================
    Separates a line into different components
=============================================*/
int splitLine(string line, vector<string> &token)
{
	string chrs = "";
	for (int i = 0; i < (int)line.length(); i++)
	{
		// if the character is ;
		if (line[i] == ';')
		{
			// if there is a component to add
			if (chrs.length() != 0)
			{
				// add component to vector
				token.push_back(chrs);
				chrs = "";
			}
			break;
		}
		// if the character isn't \0, a tab or a whitespace
		if (line[i] != '\0' && line[i] != '\t' && line[i] != ' ')
		{
			// add character to component
			chrs += line[i];
		}
		// if there is a component to add
		else if (chrs.length() != 0)
		{
			// add component to vector
			token.push_back(chrs);
			chrs = "";
		}
	}

	return 0;
}

// Analyses an instruction
int analyseInstruction(string opcodeCandidate, string operandCandidate, Opcodes &opcodeObj, Symbols &symbolObj) {
	if (opcodeCandidate == "VAR")
	{
		symbolObj.storeVar(operandCandidate);
	}
	if (opcodeObj.isOpcode(opcodeCandidate))
	{
		// TODO: Store some indication to store opcode in object code in second pass
	}
	else {
		// TODO: Invalid opcode
	}
}