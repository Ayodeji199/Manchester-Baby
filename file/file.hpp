#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

enum states {
  SUCCESS,
  FILE_NOT_FOUND,
  FILE_INVALID,
};

int loadFile(std::vector<std::string>& fileLines, std::string filename);
int openFile(std::ifstream* fileToOpen, std::string filename);

#endif