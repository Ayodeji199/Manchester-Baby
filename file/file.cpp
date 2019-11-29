/*
    Max Kelly: 180004073
    Nick De Villiers: 180003967
    Max Fyall: 180011724
    Tadas Saltenis: 180015959
    Ayodeji Shote: 180004145
*/

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
  // Couunts through each line of the file
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
  // Displays a success message
  cout << "File " + filename + " successfully loaded" << endl;
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

// Saves the contents of a vector of lines to a file
void saveFile(vector<string> &fileLines, string filename)
{
  // Creates an object to write to a file
  ofstream fileToWrite;
  // Attempts to open the file using the stored filename
  int valid = openFileToWrite(&fileToWrite, filename);
  // Stores which line number we are currently saving
  int counter = 0;
  // Couunts through each line of the file
  while (valid == SUCCESS && counter < (int) fileLines.size())
  {
    // Stores a line in the file
    fileToWrite << fileLines[counter] << endl;
    // Increments the line number
    counter++;
  }
  // Closes the file
  fileToWrite.close();
  // Displays an error message and quits the program if we haven't successfully saved a file
  checkValidity(valid);
  // Displays a success message
  cout << "File " + filename + " successfully saved" << endl;
}

// Attempts to open a file to write to and returns if the function was successful
int openFileToWrite(ofstream *fileToWrite, string filename)
{
  // Opens the file object
  fileToWrite->open(filename);
  // Checks if the file is open
  if (fileToWrite->is_open())
  {
    return SUCCESS;
  }
  return FILE_NOT_SAVED;
}