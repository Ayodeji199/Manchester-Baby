#include "file.hpp"
#include "../error/error.hpp"

using namespace std;

// Loads a file and stores its contents as a vector of characters
void loadFile(vector<string> &fileLines, string filename)
{
  // Creates an object to read from a file
  ifstream fileToOpen;
  // Attempts to open the file using the stored filename
  int valid = openFile(&fileToOpen, filename);
  // Couunts through each character of the file
  while (valid == SUCCESS && !fileToOpen.eof())
  {
    // Creates a variable to store a line
    string line;
    // Gets a line from the file
    getline(fileToOpen, line);
    // Adds the line to the vector
    fileLines.push_back(line);
  }
  // Closes the file
  fileToOpen.close();
  // Checks if we have successfully imported lines
  if (valid == SUCCESS && fileLines.size() == 0)
  {
    valid = INVALID_FILE;
  }
  // Displays an error message and quits the program if we haven't successfully opened a file
  checkValidity(valid);
}

// Attempts to open a file and returns if the function was successful
int openFile(ifstream *fileToOpen, string filename)
{
  // Opens the file object
  fileToOpen->open(filename);
  // Checks if the file is open
  if (fileToOpen->is_open())
  {
    return SUCCESS;
  }
  return FILE_NOT_FOUND;
}