#include "assembler.hpp"
#include "../error/error.hpp"
#include "../file/file.hpp"
#include <cmath>

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

/*==============
    Constructor
==============*/
Assembler::Assembler()
{
	// openFyall = "assembler/test.txt";
	openFyall = "assembler/BabyTest1-Assembler.txt";
	saveFyall = "assembler/output.txt";
	// Stores the number of words (32-bit integers our memory can store)
	memoryWordSize = 32;
	extendedinstr = true;
	opcodesObj = new Opcodes();
	symbolsObj = new Symbols(memoryWordSize);
	line = new vector<string>; // vector to store lines
	objectCode = new vector<string>;
}

// REVIEW needs checking if it works since I don't want to mess up Max's tester
/*==============================================
	Gets arguments and returns them as a vector
==============================================*/
vector<string> Assembler::getArgs(int argc, char *argv[])
{
	vector<string> args = {}; // initialize the empty vector
	// go through each argument
	for (int i = 1; i < argc; i++)
	{
		// if argument isn't NULL
		if (argv[i] != NULL)
		{
			// add argument to the vector
			args.push_back(argv[i]);
			cout << "add_arg<" << argv[i] << ">" << endl;
		}
	}

	return args;
}

// REVIEW needs checking if it works since I don't want to mess up Max's tester
/*=====================================================================================================
	If possible, assigns filenames, memory size, extended instruction set arguments values from vector
=====================================================================================================*/
void Assembler::assignArgs(vector<string> args)
{
	// if the amount of arguments is divisable by 2 and is equal or less than 8 (which would be 4 flags with a value each)
	if ((int)args.size() % 2 == 0 && (int)args.size() <= 8)
	{
		// for every flag
		for (int i = 0; i < (int)args.size(); i = i + 2)
		{
			// TIL you can't do string switches. A sad day.

			// if the flag is -memsize
			if (args.at(i) == "-memsize")
			{
				// if the size to set isn't another flag (and isn't negative)
				if (args.at(i)[0] != '-')
					try
					{
						// try to parse the integer
						memoryWordSize = stoi(args.at(i + 1));
						//if the size entered is less than 32
						if (memoryWordSize < 32)
						{
							// display error
							checkValidity(INVALID_MEMORY_SIZE);
						}
					}
					catch (invalid_argument &e)
					{
						// display error if the value entered isn't an integer
						checkValidity(INVALID_FILENAME);
					}
					catch (out_of_range &e)
					{
						// display error if the value entered is too big for a non-long integer
						checkValidity(INVALID_MEMORY_SIZE);
					}
			}

			// if the flag is -readname
			else if (args.at(i) == "-readname")
			{
				// assign name of fyall to read from (hehe max fyall get it)
				openFyall = args.at(i + 1);
			}

			// if the flag is -writename
			else if (args.at(i) == "-writename")
			{
				// assign name of fyall to write to (hehe max fyall get it)
				saveFyall = args.at(i + 1);
			}

			// if the flag is -extended
			else if (args.at(i) == "-extended")
			{
				// if the value after is true/false/1/0
				if (args.at(i + 1) == "true" || args.at(i + 1) == "false" || args.at(i + 1) == "1" || args.at(i + 1) == "0")
				{
					// assign if the extended instruction set should be used
					istringstream(args.at(i + 1)) >> extendedinstr;
				}
				else
				{
					// if it's not true/false/1/0, display error
					checkValidity(INVALID_INPUT_PARAMETER);
				}
			}
		}
	}
	else
	{
		// display error
		checkValidity(INVALID_NUMBER_OF_ARGS);
	}
}

/*=============================================
    Converts an assembly file to a binary file
===============================================*/
void Assembler::assembly()
{
	loadFile(*line, openFyall);		   // load file and store lines into vector
	vector<vector<string>> components; // stores each component for each line

	// First Pass: Validates code, stores user-defined variables and assigns them memory locations
	for (int i = 0; i < (int)line->size(); i++) // go through each line
	{
		vector<string> token;		   // create vector to store the line's components
		splitLine(line->at(i), token); // separates a line into different components
		processLine(token);			   //
		components.push_back(token);   //
	}

	// Second Pass: Generates object code
	for (int i = 0; i < (int)components.size(); i++) // go through each line
	{
		genBinary(components[i]);
	}
	// Saves object code to output file
	saveFile(*objectCode, saveFyall);

	// printMachineCode(saveFyall);
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

/*===============================================================
	Goes through the line and decides what to do with each token
===============================================================*/
void Assembler::processLine(vector<string> &token)
{
	// Loops through each component of the line
	for (int i = 0; i < (int)token.size(); i++)
	{
		// Checks if a token defines a user defined variable
		if (token[i].back() == ':')
		{
			// Deletes the ':' from the token and stores this as the name of the symbol we're storing
			string name = token[i].substr(0, token[i].size() - 1);
			// Stores the variable in the symbols table
			symbolsObj->storeOperand(name);
		}
		else
		{
			// Checks if there is an opcode and an operand to process
			// this is not the case with STP instruction
			if ((int)token.size() > i + 1)
			{
				// Analyses the opcode and operand together as an instruction
				analyseInstruction(token[i], token[i + 1]);
				// Increments counter by 1 as the next component is an operand and has already been analysed
				i++;
			}
			else
			{
				// Analyses the opcode
				analyseInstruction(token[i], "");
			}
		}
	}
}

/*=========================================================================================
	Analyses an individual instruction for the first time to get symbols and verify syntax
=========================================================================================*/
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

/*==================================
	Prints converted code into file
==================================*/
void Assembler::printMachineCode(string filenameOut)
{
	// open file to write
	ofstream fileOut;
	fileOut.open(filenameOut);

	// check if file opened properly
	if (fileOut)
	{
		// for each line
		for (int i = 0; i < (int)objectCode->size(); i++)
		{
			// print machine code
			cout << objectCode->at(i) << endl;
			fileOut << objectCode->at(i) << endl;
		}

		fileOut.close();
	}
	else
	{
		// display error
		checkValidity(FILE_NOT_FOUND);
	}
}

/*==================================
	Generates the binary object code
==================================*/
void Assembler::genBinary(vector<string> &token)
{
	// Loops through each component of the line
	for (int i = 0; i < (int)token.size(); i++)
	{
		// Checks if a token defines a user defined variable
		if (token[i].back() == ':')
		{
			// Deletes the ':' from the token and stores this as the name of the symbol we're finding
			// string name = token[i].substr(0, token[i].size() - 1);
			// Lookups the memory location in the symbols table for the variable
			// string memoryLocation = symbolsObj->get(token[i + 1]);
			// Stores the line for the object code
			// objectCode->push_back(memoryLocation);
		}
		// Checks if we dealing with a STP instruction
		else if (token[i] == "STP")
		{
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

/*=====================================================================================
	Stores an individual instruction to the binary object code
=====================================================================================*/
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

/*=============================================================================
Calculates the number of blank bits that are needed to produce a 32 bit number
=============================================================================*/
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
	if (number == pow(2, 13))
	{
		return 0;
	}

	int zeros = calcZeros(number * 2) + 1;
	return zeros;
}

void Assembler::printVec(vector<string> &v)
{
	cout << endl;
	cout << "Printing Vector:" << endl;
	for (int i = 0; i < (int)v.size(); i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;
}

vector<string> Assembler::getObjectCode()
{
	return *objectCode;
}