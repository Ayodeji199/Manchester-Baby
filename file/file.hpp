/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void loadFile(std::vector<std::string> &fileLines, std::string filename);
void saveFile(std::vector<std::string> &fileLines, std::string filename);

int openFile(std::ifstream *fileToOpen, std::string filename);
int openFileToWrite(std::ofstream *fileToWrite, std::string filename);
#endif