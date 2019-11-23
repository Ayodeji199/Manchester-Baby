#include <iostream>
#include <string>
#include "instructions.cpp"

using namespace std;

int main(){
    string opcode;
    cin >> opcode;
    string out = parseInstruction(opcode);
    cout << out << endl;
    return 0;
}