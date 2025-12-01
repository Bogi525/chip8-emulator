#include <iostream>
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

    void init() {

    }

    void print() {
        cout << pc++;
    }

private:
    Chip8() {
        pc = PROGRAM_START_ADDR;
        i = 0;
        sp = 0;
        delay_timer = 0;
        sound_timer = 0;
    };

    vector<uint8_t> memory = vector<uint8_t>(MEM_SIZE);
    vector<uint8_t> gpr = vector<uint8_t>(GPR_COUNT);

    uint16_t pc;
    uint16_t i;
    
    vector<uint16_t> stack = vector<uint16_t>(16);
    uint16_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;
};