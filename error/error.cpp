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

    cout << "Error" << valid << ": ";

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

    default:
        cout << "Error Code is invalid or has not been fully implemented";
        break;
    }

    cout << endl;

    // Quits if an error code has occured
    exit(valid);
}