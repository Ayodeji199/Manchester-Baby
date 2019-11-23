#include "assembler.hpp"
#include "../error/error.hpp"
#include <cmath>

using namespace std;

// int main()
// {
// 	Assembler assemblerObj = Assembler();
// 	assemblerObj.assembly();
// 	return SUCCESS;
// }

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
	// Stores the number of words (32-bit integers our memory can store)
	memoryWordSize = 32;
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
	loadFile(*line, filename);		   // load file and store lines into vector
	vector<vector<string>> components; // stores each component for each line

	// First Pass: Validates code, stores user-defined variables and assigns them memory locations
	for (int i = 0; i < (int)line->size(); i++) // go through each line
	{
		// TODO - ANY ASSEMBLY-RELATED FUNCTIONS GO IN THIS LOOP
		// NOTE - ASSEMBLY HAS TO BE DONE LINE BY LINE
		vector<string> token;		   // create vector to store the line's components
		splitLine(line->at(i), token); // separates a line into different components
		// testTokenization(token);
		processLine(token);
		components.push_back(token);
	}

	// Second Pass: Generates object code
	for (int i = 0; i < (int)components.size(); i++) // go through each line
	{
		genBinary(components[i]);
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
	// Loops through each component of the line
	for (int i = 0; i < (int)token.size(); i++)
	{
		// Checks if a token defines a user defined variable
		if (token[i].back() == ':')
		{
			// Deletes the ':' from the token and stores this as the name of the symbol we're storing
			string name = token[i].substr(0, token[i].size() - 2);
			// Stores the varialbe in the symbols table
			symbolsObj->storeVar(token[i + 1]);
		}
		else
		{
			analyseInstruction(token[i], token[i + 1]);
			// Increments counter by 1 as the next component is an operand and has already been analysed
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

void Assembler::genBinary(vector<string> &token)
{
	// Loops through each component of the line
	for (int i = 0; i < (int)token.size(); i++)
	{
		// Checks if a token defines a user defined variable
		if (token[i].back() == ':')
		{
			// Deletes the ':' from the token and stores this as the name of the symbol we're storing
			string name = token[i].substr(0, token[i].size() - 2);
			// Stores the memory location in the symbols table
			string memoryLocation = symbolsObj->get(token[i + 1]);
			//
			objectCode->push_back(memoryLocation);
		}
		else if (token[i] == "STP") {
			// Adds together each part of the 32-bit instruction
			string instruction = "0000000000000" + opcodesObj->getBinary("STP") + "0000000000000000";
			// Stores the binary in the object code
			objectCode->push_back(instruction);
		}
		else
		{
			//
			storeInstruction(token[i], token[i + 1]);
			// Increments counter by 1 as the next component is an operand and has already been analysed
			i++;
		}
	}
}

// Analyses an individual instruction for the first time to get symbols and verify syntax
void Assembler::storeInstruction(string opcodeCandidate, string operandCandidate)
{
	// Checks if the opcode candidate is a variable
	if (opcodeCandidate == "VAR")
	{
		// Extracts binary for the operand
		string instruction = symbolsObj->get(operandCandidate);
		// Stores the binary in the object code
		objectCode->push_back(instruction);
	}
	// Checks if the opcode candidate is not a standard opcode
	else
	{
		// Extracts the binary for the opcode stored
		string opcodeBinary = opcodesObj->getBinary(opcodeCandidate);
		// Extracts the binary for the operand stored
		string operandBinary = symbolsObj->get(operandCandidate);
		// Stores the number of blank bits that are needed to produce a 32 bit number
		string blankBits = calcBlankBits();
		// Adds together each part of the 32-bit instruction
		string instruction = operandBinary + blankBits + opcodeBinary + "0000000000000000";
		// Stores the binary in the object code
		objectCode->push_back(instruction);
	}
}

// Calculates the number of blank bits that are needed to produce a 32 bit number
string Assembler::calcBlankBits()
{
	if (memoryWordSize > 8192 || memoryWordSize < 0)
	{
		checkValidity(INVALID_MEMORY_SIZE);
	}
	// Calculates how many zeros we need to return
	int zeros = calcZeros(memoryWordSize);
	// Stores the blank bits we're returning
	string blankBits = "";
	// Adds "0" a number of times to the string
	for (int i = 0; i < zeros; i++)
	{
		blankBits += "0";
	}
	return blankBits;
}

int Assembler::calcZeros(int number)
{
	if (number == pow(2,13)) {
		return 0;
	}

	int zeros = calcZeros(number*2) + 1;
	return zeros;
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