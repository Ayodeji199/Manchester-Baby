#include "assembler.hpp"
#include "opcodes.hpp"
#include "symbols.hpp"
#include "../error/error.hpp"

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
	vector<string> objectCode;
	// firstPass(token, opcodesObj, symbolsObj);

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

int firstPass(vector<string> &token, Opcodes &opcodesObj, Symbols &symbolsObj)
{
	for (int i = 0; i < (int)token.size(); i++)
	{
		// Checks if a token defines a method
		if (token[i].back() == ':')
		{
			string method = token[i].substr(0, token[i].size() - 2);
		}
		else
		{
			analyseInstruction(token[i],token[i+1],opcodesObj,symbolsObj);
			i++;
		}
	}
}

// Analyses an instruction for the first time to get symbols and verify syntax
int analyseInstruction(string opcodeCandidate, string operandCandidate, Opcodes &opcodesObj, Symbols &symbolsObj)
{
	// Checks if the opcode candidate is a variable
	if (opcodeCandidate == "VAR")
	{
		// Stores the variable in the symbols table
		symbolsObj.storeVar(operandCandidate);
	}
	// Checks if the opcode candidate is a normal opcode
	if (opcodesObj.isOpcode(opcodeCandidate))
	{
	}
	// Runs if the opcode candidate isn't valid
	else
	{
		// Displays an error message and quits the program
		checkValidity(INVALID_OPCODE);
	}
}