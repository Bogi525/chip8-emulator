#include <iostream>
#include "../inc/chip8.hpp"

using namespace std;

int main() {
    Chip8::getInstance().init("2-ibm-logo.ch8");
    Chip8::getInstance().printMemory();
    system("pause");
    Chip8::getInstance().runProgram();
    system("pause");
    return 0;
}