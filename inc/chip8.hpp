#include <iostream>
#include <fstream>
#include <cstdint>
#include <iomanip>
#include <functional>
#include <random>
#include <vector>
#include <SDL3/SDL.h>
#include "constants.hpp"

using namespace std;

using InstrPtr = function<void(uint16_t opcode)>;

class Chip8 {
public:
    Chip8(const Chip8&) = delete;
    Chip8(Chip8&&) = delete;

    static Chip8& getInstance() {
        static Chip8 inst;
        return inst;
    }

    void init(string rom);
    void printMemory();
    void cycle();
    void render(SDL_Renderer* renderer);
    void updateKeyboardState(SDL_Event& event);

private:
    Chip8();

    void setFunctionPointers();
    void loadROM(string rom);
    void loadFontset();

    void fetchInstruction();
    void executeInstruction();

    void group0(uint16_t opcode);
    void group1(uint16_t opcode);
    void group2(uint16_t opcode);
    void group3(uint16_t opcode);
    void group4(uint16_t opcode);
    void group5(uint16_t opcode);
    void group6(uint16_t opcode);
    void group7(uint16_t opcode);
    void group8(uint16_t opcode);
    void group9(uint16_t opcode);
    void groupA(uint16_t opcode);
    void groupB(uint16_t opcode);
    void groupC(uint16_t opcode);
    void groupD(uint16_t opcode);
    void groupE(uint16_t opcode);
    void groupF(uint16_t opcode);

    vector<uint8_t> memory;
    vector<uint8_t> gpr;
    vector<vector<bool>> display;

    uint16_t pc;
    uint16_t i;
    uint16_t opcode;

    vector<uint16_t> stack;
    uint16_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;

    string installed_rom;

    std::vector<uint8_t> chip8_fontset = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    vector<InstrPtr> functions;

    vector<bool> keys = vector<bool>(16, false);

    bool finished = false;
};