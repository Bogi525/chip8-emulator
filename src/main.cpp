#include <iostream>
#include "../inc/chip8.hpp"

using namespace std;

int main() {
    Chip8::getInstance().init("2-ibm-logo.ch8");
    Chip8::getInstance().printMemory();
    system("pause");
    Chip8::getInstance().runProgram();
    system("pause");

    // Create a Window
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Sample Title", 320, 128, SDL_WINDOW_RESIZABLE);
    SDL_Event event;
    bool finished = false;
    while (!finished) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                finished = true;
            } else if (event.type == SDL_EVENT_WINDOW_FOCUS_GAINED) {
                cout << "Focused";
            } else if (event.type == SDL_EVENT_WINDOW_FOCUS_LOST) {
                cout << "Unfocused";
            }
        }
    }
    SDL_Quit();
    system("pause");
    return 0;
}