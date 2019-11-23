#include <iostream>
#include <string>

using namespace std;


string parseInstruction(string opcode){
    if (opcode == "000"){
        return "JMP";
    } else if (opcode == "100"){
        return "JRP";
    } else if (opcode == "010"){
        return "LDN";
    } else if (opcode == "110"){
        return "STO";
    } else if (opcode == "001"){
        return "SUB";
    } else if (opcode == "101"){
        return "SUB";
    } else if (opcode == "011"){
        return "CMP";
    } else if (opcode == "111"){
        return "STP";
    } else {
        return "invalid opcode";
    }
}