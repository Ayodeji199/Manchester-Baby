// Used to print to the console
#include <iostream>
// Imports error codes
#include "error.hpp"

using namespace std;

// Displays an error message to the user based on the apppropriate error code
// imported and quits the program, will do nothing if SUCCESS is passed
void checkValidity(int valid)
{
    switch (valid)
    {
    case SUCCESS:
        break;

    case UNEXPECTED_NULL_POINTER:
        cout << "Error: Function has been called using a null pointer" << endl;
        break;

    case INVALID_FILE:
        cout << "Error: A file has attempted to be imported that is invalid"
             << endl;
        break;
    case INVALID_FILENAME:
        cout << "Error: The filename passed as a parameter is invalid while "
                "attempting to save or load a file"
             << endl;
        break;
    case FILE_NOT_FOUND:
        cout << "Error: A file has attempted to be imported that doesn't exist"
             << endl;
        break;
    case FILE_NOT_SAVED:
        cout << "Error: A file cannot be saved in the location provided, this "
                "could be an invalid filename or there may be insufficient "
                "permissions for access"
             << endl;
        break;

    default:
        cout << "Error: Error Code is invalid or has not been fully implemented"
             << endl;
        cout << "Error Code Imported: " << valid << endl;
        break;
    }

    // Quits if an error code has occured
    if (valid != SUCCESS)
    {
        exit(valid);
    }
}