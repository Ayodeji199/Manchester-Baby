#include "assembler.hpp"

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
		if ((int)token.size() != 0) // at the end of the test loop, ends the line
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
			if (chrs.length() != 0)
			{
				token.push_back(chrs);
				chrs = "";
			}
			break;
		}
		if (line[i] != '\0' && line[i] != '\t' && line[i] != ' ')
		{
			chrs += line[i];
		}
		else if (chrs.length() != 0)
		{
			token.push_back(chrs);
			chrs = "";
		}
	}

	return 0;
}
