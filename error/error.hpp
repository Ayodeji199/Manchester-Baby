#ifndef ERROR_H
#define ERROR_H

/*=============================================
    General Codes
=============================================*/
// Everything is awesome
#define SUCCESS 0
// Pointer is unexpectedly null
#define UNEXPECTED_NULL_POINTER 1
// A parameter to a function is invalid
#define INVALID_INPUT_PARAMETER 2

/*=============================================
    Application Specific Codes
=============================================*/
// Saving and loading file errors
#define INVALID_FILE 100
#define INVALID_FILENAME 101
#define FILE_NOT_FOUND 102
#define FILE_NOT_SAVED 103

// Assembler specific errors
#define INVALID_OPCODE 200
#define INVALID_OPERAND 201
#define INVALID_MEMORY_SIZE 202
#define INVALID_NUMBER_OF_ARGS 203

// Displays an error message to the user based on the apppropriate error code
// imported and quits the program, will do nothing if SUCCESS is passed
void checkValidity(int valid);

#endif