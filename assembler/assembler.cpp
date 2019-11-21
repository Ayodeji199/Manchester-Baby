#include "assembler.hpp"

using namespace std;

int main()
{
	vector<string> line = {}; // vector to store lines
	string filename =
		"BabyTest1-Assembler.txt"; // REVIEW - potential string for user input.
								   // can get rid of it if you want
	loadFile(line, filename);	  // load file and store lines into vector
	for (int i = 0; i < (int)line.size(); i++)
	{
		// TODO - this is gonna be the assembly loop
		vector<string> token = {};
		splitLine(line.at(i), token); // separates a line into different components
		for (int j = 0; j < (int)token.size(); j++)
		{
			cout << token.at(j) << " ";
		}
		cout << endl;
	}
	return 0;
}

/*=============================================
        Separates a line into different components
=============================================*/
int splitLine(string line, vector<string> token)
{
	//cout << line << endl;
	string chrs;
	for (int i = 0; i < (int)line.length(); i++)
	{
		if (line[i] == ';')
		{
			if (chrs.length() != 0)
			{
				token.push_back(chrs);
				chrs = "";
			}
			break;
		}
		if (line[i] != '\0' && line[i] != '\t')
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