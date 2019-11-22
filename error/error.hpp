#ifndef ERROR_H
#define ERROR_H

// Everything is awesome
#define SUCCESS 0

// Pointer is unexpectedly null
#define UNEXPECTED_NULL_POINTER -1

// Saving and loading file errors
#define INVALID_FILE -200
#define INVALID_FILENAME -201
#define FILE_NOT_FOUND -202
#define FILE_NOT_SAVED -203

#define INVALID_INPUT_PARAMETER -101

// Displays an error message to the user based on the apppropriate error code
// imported and quits the program, will do nothing if SUCCESS is passed
void checkValidity(int valid);

#endif