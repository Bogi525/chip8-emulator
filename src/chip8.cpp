#include "../inc/chip8.hpp"

Chip8::Chip8() {}

void Chip8::init(string rom) {
        pc = PROGRAM_START_ADDR;
        i = 0;
        sp = 0;
        delay_timer = 0;
        sound_timer = 0;
        stack = vector<uint16_t>(STACK_SIZE);
        gpr = vector<uint8_t>(GPR_COUNT);
        memory = vector<uint8_t>(MEM_SIZE);
        display = vector<vector<bool>>(DISPLAY_HEIGHT, vector<bool>(DISPLAY_WIDTH, 0));
        setFunctionPointers();

        loadFontset();
        
        loadROM(rom);
    }

void Chip8::setFunctionPointers() {
    functions = {
        [this](uint16_t opcode) { this->group0(opcode); },
        [this](uint16_t opcode) { this->group1(opcode); },
        [this](uint16_t opcode) { this->group2(opcode); },
        [this](uint16_t opcode) { this->group3(opcode); },
        [this](uint16_t opcode) { this->group4(opcode); },
        [this](uint16_t opcode) { this->group5(opcode); },
        [this](uint16_t opcode) { this->group6(opcode); },
        [this](uint16_t opcode) { this->group7(opcode); },
        [this](uint16_t opcode) { this->group8(opcode); },
        [this](uint16_t opcode) { this->group9(opcode); },
        [this](uint16_t opcode) { this->groupA(opcode); },
        [this](uint16_t opcode) { this->groupB(opcode); },
        [this](uint16_t opcode) { this->groupC(opcode); },
        [this](uint16_t opcode) { this->groupD(opcode); },
        [this](uint16_t opcode) { this->groupE(opcode); },
        [this](uint16_t opcode) { this->groupF(opcode); }
    };
}

void Chip8::loadFontset() {
    for (int i = 0; i < chip8_fontset.size(); i++) {
        memory[FONTSET_START + i] = chip8_fontset[i];
    }
}

void Chip8::loadROM(string rom) {
    ifstream file(rom, ios::in | ios::binary | ios::ate);

    if (!file.is_open()) {
        cerr << "Error: could not open ROM";
        system("pause");
        system("exit");
    }

    streampos fileSize = file.tellg();
    file.seekg(0, ios::beg);

    vector<uint8_t> buffer = vector<uint8_t>(fileSize);
    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);

    for (int i = 0; i < fileSize; i++) {
        memory[pc + i] = buffer[i]; 
    }
}

void Chip8::printMemory() {
    for (int i = 0; i < MEM_SIZE; i++) {
        if (i % 2 == 0) cout << "0x" << setw(3) << hex << i << dec << ": ";
        cout << hex << setw(2) << setfill('0');
        cout << hex << setw(2) << static_cast<unsigned int>(memory[i]);
        cout << dec;
        if (i % 2 == 1) cout << '\n';
        else cout << ' ';
    }
}

void Chip8::runProgram() {
    while (!finished) {
        fetchInstruction();
        executeInstruction();
    }
}

void Chip8::fetchInstruction() {
    opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
}

void Chip8::executeInstruction() {
    finished = true; // placeholder
}

void Chip8::group0(uint16_t opcode) {

}

void Chip8::group1(uint16_t opcode) {

}

void Chip8::group2(uint16_t opcode) {

}

void Chip8::group3(uint16_t opcode) {

}

void Chip8::group4(uint16_t opcode) {

}

void Chip8::group5(uint16_t opcode) {

}

void Chip8::group6(uint16_t opcode) {

}

void Chip8::group7(uint16_t opcode) {

}

void Chip8::group8(uint16_t opcode) {

}

void Chip8::group9(uint16_t opcode) {

}

void Chip8::groupA(uint16_t opcode) {

}

void Chip8::groupB(uint16_t opcode) {

}

void Chip8::groupC(uint16_t opcode) {

}

void Chip8::groupD(uint16_t opcode) {

}

void Chip8::groupE(uint16_t opcode) {

}

void Chip8::groupF(uint16_t opcode) {

}