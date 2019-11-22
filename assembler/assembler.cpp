#include "assembler.hpp"
#include "opcodes.hpp"
#include "symbols.hpp"

using namespace std;

int main()
{
	if (assembly() != SUCCESS)
	{
		return 1;
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

	return SUCCESS;
}

/*====================
    The whole shabang
====================*/
int assembly()
{
	Opcodes opcodesObj = Opcodes();
	Symbols symbolsObj = Symbols();

	vector<string> line = {};					 // vector to store lines
	string filename = "BabyTest1-Assembler.txt"; // REVIEW - potential string for user input
	loadFile(line, filename);					 // load file and store lines into vector

	for (int i = 0; i < (int)line.size(); i++) // go through each line
	{
		// TODO - this is gonna be the assembly loop

		vector<string> token = {};					 // create vector to store the line's components
		if (splitLine(line.at(i), token) != SUCCESS) // separates a line into different components
		{
			return 5; // no enum for this yet im just kinda using a random number for now as a general fail
		}
		if (testTokenization(token) != SUCCESS)
		{
			return 5; // no enum for this yet im just kinda using a random number for now as a general fail
		}
	}

	return SUCCESS;
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

	return SUCCESS;
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
	return 0;
}

// =================== ANCHOR - TEST FUNCTIONS ===================

int testTokenization(vector<string> token)
{
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
	return SUCCESS;
}