#include "../inc/chip8.hpp"

Chip8::Chip8() {}

void Chip8::init(string rom) {
        pc = PROGRAM_START_ADDR;
        i = 0;
        sp = -1;
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

void Chip8::cycle() {
    fetchInstruction();
    executeInstruction();
    //cout << hex << opcode << dec << '\n';
}

void Chip8::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {

            if (display[y][x]) {

                SDL_FRect rect = {
                    float(x * DISPLAY_SCALE),
                    float(y * DISPLAY_SCALE),
                    float(DISPLAY_SCALE),
                    float(DISPLAY_SCALE)
                };

                SDL_RenderFillRect(renderer, &rect);
            }

        }
    }

    SDL_RenderPresent(renderer);
}

void Chip8::updateKeyboardState(SDL_Event& event) {
    bool isPressed = (event.type == SDL_EVENT_KEY_DOWN);

    switch(event.key.key) {
        case SDLK_0:
            keys[0] = isPressed;
            cout << isPressed;
            break;
        case SDLK_1:
            keys[1] = isPressed;
            cout << isPressed;
            break;
        case SDLK_2:
            keys[2] = isPressed;
            cout << isPressed;
            break;
        case SDLK_3:
            keys[3] = isPressed;
            cout << isPressed;
            break;
        case SDLK_Q:
            keys[4] = isPressed;
            cout << isPressed;
            break;
        case SDLK_W:
            keys[5] = isPressed;
            cout << isPressed;
            break;
        case SDLK_E:
            keys[6] = isPressed;
            cout << isPressed;
            break;
        case SDLK_R:
            keys[7] = isPressed;
            cout << isPressed;
            break;
        case SDLK_A:
            keys[8] = isPressed;
            cout << isPressed;
            break;
        case SDLK_S:
            keys[9] = isPressed;
            cout << isPressed;
            break;
        case SDLK_D:
            keys[10] = isPressed;
            cout << isPressed;
            break;
        case SDLK_F:
            keys[11] = isPressed;
            cout << isPressed;
            break;
        case SDLK_Z:
            keys[12] = isPressed;
            cout << isPressed;
            break;
        case SDLK_X:
            keys[13] = isPressed;
            cout << isPressed;
            break;
        case SDLK_C:
            keys[14] = isPressed;
            cout << isPressed;
            break;
        case SDLK_V:
            keys[15] = isPressed;
            cout << isPressed;
            break;
    }
}

void Chip8::fetchInstruction() {
    opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
}

void Chip8::executeInstruction() {
    uint8_t group = (opcode & 0xf000) >> 12;
    functions[group](opcode);
}

void Chip8::group0(uint16_t opcode) {
    switch (opcode) {
    case 0x00e0: // Clear the display
        for (int i = 0; i < DISPLAY_HEIGHT; i++) {
            for (int j = 0; j < DISPLAY_WIDTH; j++) {
                display[i][j] = 0;
            }
        }
        break;

    case 0x00ee: // RET
        pc = stack[sp--];
        break;
    default:
        cerr << "Error: Invalid instruction";
        break;
    }
}

void Chip8::group1(uint16_t opcode) {
    // JMP
    uint16_t addr = opcode & 0xfff;
    pc = addr;
}

void Chip8::group2(uint16_t opcode) {
    // CALL
    stack[++sp] = pc;
    uint16_t addr = opcode & 0xfff;
    pc = addr;
}

void Chip8::group3(uint16_t opcode) {
    // BEQ (REG, CONST)
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    if (gpr[reg] == byte) {
        pc += 2;
    }
}

void Chip8::group4(uint16_t opcode) {
    // BNE (REG, CONST)
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    if (gpr[reg] != byte) {
        pc += 2;
    }
}

void Chip8::group5(uint16_t opcode) {
    // BEQ (REG, REG)
    uint16_t reg1 = (opcode & 0x0f00) >> 8;
    uint16_t reg2 = (opcode & 0x00f0) >> 4;
    if (gpr[reg1] == gpr[reg2]) {
        pc += 2;
    }
}

void Chip8::group6(uint16_t opcode) {
    // LD
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    gpr[reg] = byte;
}

void Chip8::group7(uint16_t opcode) {
    // ADD (REG, CONST)
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    gpr[reg] += byte;
}

void Chip8::group8(uint16_t opcode) {
    uint16_t last_byte = opcode & 0x000f;
    switch (last_byte) {
        case 0x0: { // LD (REG, REG) 
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            gpr[reg1] = gpr[reg2];
            break;
        }
        case 0x1: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            gpr[reg1] |= gpr[reg2];
            break;
        }
        case 0x2: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            gpr[reg1] &= gpr[reg2];
            break;
        }
        case 0x3: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            gpr[reg1] ^= gpr[reg2];
            break;
        }
        case 0x4: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            uint8_t res = gpr[reg1] + gpr[reg2];
            if (res < gpr[reg1]) VF = 1;
            else VF = 0;
            gpr[reg1] = res;
            break; 
        }
        case 0x5: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            if (gpr[reg1] > gpr[reg2]) VF = 1;
            else VF = 0;
            gpr[reg1] -= gpr[reg2];
            break;
        }
        case 0x6: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            VF = gpr[reg1] & 1;
            gpr[reg1] >>= 1;
            break;
        }
        case 0x7: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            uint16_t reg2 = (opcode & 0x00f0) >> 4;
            if (gpr[reg2] > gpr[reg1]) VF = 1;
            else VF = 0;
            gpr[reg1] = gpr[reg2] - gpr[reg1];
            break;
        }
        case 0xe: {
            uint16_t reg1 = (opcode & 0x0f00) >> 8;
            VF = gpr[reg1] >> 7 & 1;
            gpr[reg1] <<= 1;
            break;
        }
        default:
            break;
    }
}

void Chip8::group9(uint16_t opcode) {
    // BNE (REG, REG)
    uint16_t reg1 = (opcode & 0x0f00) >> 8;
    uint16_t reg2 = (opcode & 0x00f0) >> 4;
    if (gpr[reg1] != gpr[reg2]) {
        pc += 2;
    }
}

void Chip8::groupA(uint16_t opcode) {
    // LD I, addr
    uint16_t val = opcode & 0x0fff;
    i = val;
}

void Chip8::groupB(uint16_t opcode) {
    // JMP to NNN + V0
    uint16_t val = opcode & 0x0fff;
    pc = val + gpr[0x0];
}

void Chip8::groupC(uint16_t opcode) {
    // RNG
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    gpr[reg] = (rand() % 256) & byte;
}

void Chip8::groupD(uint16_t opcode) {
    // Draw on the display
    uint16_t reg1 = (opcode & 0x0f00) >> 8;
    uint16_t reg2 = (opcode & 0x00f0) >> 4;
    uint8_t byte = opcode & 0x000f;
    bool collision = false;
    for (int row = 0; row < byte; row++) {
        uint8_t to_draw = memory[this->i + row];
        int y = (gpr[reg2] + row) % DISPLAY_HEIGHT;
        for (int bit = 0; bit < SPRITE_MAX_WIDTH; bit++) {
            int x = (gpr[reg1] + bit) % DISPLAY_WIDTH;
            bool pixel_to_draw = (to_draw & (0x80 >> bit)) ? 1 : 0;
            if (display[y][x] && pixel_to_draw) collision = true;
            display[y][x] = pixel_to_draw ^ display[y][x];
        }
    }
    if (collision) VF = 1;
    else VF = 0;
}

void Chip8::groupE(uint16_t opcode) {
    uint16_t reg = (opcode & 0x0f00) >> 8;
    uint8_t byte = opcode & 0x00ff;
    switch (byte) {
        // SKP
        case 0x9e: {
            if (keys[gpr[reg]]) {
                pc += 2;
            }
            break;
        }
        // SKNP
        case 0xa1: {
            if (!keys[gpr[reg]]) {
                pc += 2;
            }
            break;
        }
        default:
            break;
    }
}

void Chip8::groupF(uint16_t opcode) {
    
}