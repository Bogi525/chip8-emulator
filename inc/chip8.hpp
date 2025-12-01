#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <SDL3/SDL.h>
#include "constants.hpp"

using namespace std;

class Chip8 {
public:
    Chip8(const Chip8&) = delete;
    Chip8(Chip8&&) = delete;

    static Chip8& getInstance() {
        static Chip8 inst;
        return inst;
    }

    void init(string rom) {
        pc = PROGRAM_START_ADDR;
        i = 0;
        sp = 0;
        delay_timer = 0;
        sound_timer = 0;
        stack = vector<uint16_t>(STACK_SIZE);
        gpr = vector<uint8_t>(GPR_COUNT);
        memory = vector<uint8_t>(MEM_SIZE);
        
        loadROM(rom);
    }

    void printROM() {
        cout << pc++;
    }

private:
    Chip8();

    void loadROM(string rom) {
        // Loading ROM...
        ifstream file(rom, ios::in | ios::binary | ios::ate);

        if (!file.is_open()) {
            cerr << "Error: could not open ROM";
            system("exit");
        }

        streampos fileSize = file.tellg();
        file.seekg(0, ios::beg);

        vector<uint8_t> buffer = vector<uint8_t>(fileSize);
        file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

        for (int i = 0; i < fileSize; i++) {
            cout << buffer[i];
        }
    }

    vector<uint8_t> memory;
    vector<uint8_t> gpr;

    uint16_t pc;
    uint16_t i;

    vector<uint16_t> stack;
    uint16_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;

    string installed_rom;
};