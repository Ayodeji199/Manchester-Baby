// Used to print to the console
#include <iostream>
// Imports error codes
#include "error.hpp"

using namespace std;

// Displays an error message to the user based on the apppropriate error code
// imported and quits the program, will do nothing if SUCCESS is passed
void checkValidity(int valid)
{
    if (valid == SUCCESS)
    {
        return;
    }

    cout << endl
         << "Error " << valid << ": ";

    switch (valid)
    {
    case UNEXPECTED_NULL_POINTER:
        cout << "Function has been called using a null pointer";
        break;

    case INVALID_FILE:
        cout << "A file has attempted to be imported that is invalid";
        break;

    case INVALID_FILENAME:
        cout << "The filename passed as a parameter is invalid while "
                "attempting to save or load a file";
        break;

    case FILE_NOT_FOUND:
        cout << "A file has attempted to be imported that doesn't exist";
        break;

    case FILE_NOT_SAVED:
        cout << "A file cannot be saved in the location provided, this "
                "could be an invalid filename or there may be insufficient "
                "permissions for access";
        break;

    case INVALID_INPUT_PARAMETER:
        cout << "Invalid Input detected. Please try again ";
        break;

    case INVALID_MEMORY_SIZE:
        cout << "Invalid or unsupported memory size input detected. "
                "This could be caused by the input not being an integer "
                "or the input size being invalid/unsupported";

    case INVALID_NUMBER_OF_ARGS: // REVIEW - there might be too many endlines here, not sure.
        cout << "Invalid number of arguments when executing the assembler. "
                "Please make sure to enter the argument type, then value."
             << endl
             << "Arguments: [-memsize [INTEGER]] [-readname [STRING]] [-writename [STRING]] [-extended [BOOLEAN(true/false/1/0)]]"
             << endl
             << "Examples:" << endl
             << "./assembler -memsize 64 -extended true" << endl
             << "./assembler" << endl
             << "./assembler -extended 0 -writename yourwritename.txt -readname yourreadname.txt -memsize 64";
    case MEMORY_EMPTY:
        cout << "Your program has not been loaded into memory."
             << "This is probably because the file you chose is empty." << endl;
    case MEMORY_OVERLOAD:
        cout << "A line in your program has exceeded the specified line limit."
             << "Please adjust this to fit the memory size specified."<< endl;
    default:
        cout << "Error Code is invalid or has not been fully implemented";
        break;
    }

    cout << endl;

    // Quits if an error code has occured
    exit(valid);
}