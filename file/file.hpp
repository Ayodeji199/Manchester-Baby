#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void loadFile(std::vector<std::string> &fileLines, std::string filename);
int openFile(std::ifstream *fileToOpen, std::string filename);