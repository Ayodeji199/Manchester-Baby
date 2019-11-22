#include "assembler.hpp"
#include "../error/error.hpp"

using namespace std;

int main()
{
	Assembler assemblerObj = Assembler();
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

Assembler::Assembler()
{
	opcodesObj = new Opcodes();
	symbolsObj = new Symbols();
	line = new vector<string>;			  // vector to store lines
	filename = "BabyTest1-Assembler.txt"; // REVIEW - potential string for user input
	objectCode = new vector<string>;
}

/*====================
    The assembly loop
====================*/
void Assembler::assembly()
{
	loadFile(*line, filename); // load file and store lines into vector

	for (int i = 0; i < (int)line->size(); i++) // go through each line
	{
		vector<string> token;		   // create vector to store the line's components
		splitLine(line->at(i), token); // separates a line into different components
		testTokenization(token);
		processLine(token);
	}
}

/*=============================================
    Separates a line into different components
=============================================*/
void Assembler::splitLine(string line, vector<string> &token)
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
}

void Assembler::processLine(vector<string> &token)
{
	for (int i = 0; i < (int) token.size(); i++)
	{
		// Checks if a token defines a method
		if (token[i].back() == ':')
		{
			string method = token[i].substr(0, token[i].size() - 2);
		}
		else
		{
			analyseInstruction(token[i], token[i + 1]);
			i++;
		}
	}
}

// Analyses an individual instruction for the first time to get symbols and verify syntax
void Assembler::analyseInstruction(string opcodeCandidate, string operandCandidate)
{
	// Checks if the opcode candidate is a variable
	if (opcodeCandidate == "VAR")
	{
		// Stores the variable in the symbols table
		symbolsObj->storeVar(operandCandidate);
	}
	// Checks if the opcode candidate is not a standard opcode
	else if (!opcodesObj->isOpcode(opcodeCandidate))
	{
		// Displays an error message and quits the program
		checkValidity(INVALID_OPCODE);
	}
}

// =================== ANCHOR - TEST FUNCTIONS ===================

void Assembler::testTokenization(vector<string> token)
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
}