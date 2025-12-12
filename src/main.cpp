#include <iostream>
#include "../inc/chip8.hpp"

using namespace std;

int main() {

    // SDL Initialization
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        system("pause");
        system("exit");
    }

    Chip8::getInstance().init("Airplane.ch8");
    Chip8::getInstance().printMemory();
    system("pause");

    SDL_Window* window = SDL_CreateWindow(
        "Chip-8 Emulator",
        DISPLAY_WIDTH * DISPLAY_SCALE,
        DISPLAY_HEIGHT * DISPLAY_SCALE,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    bool running = true;
    SDL_Event event;

    uint32_t lastCPUTime = SDL_GetTicks();
    uint32_t lastFrameTime = SDL_GetTicks();
    uint32_t lastTimerUpdate = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = false;

            if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
                Chip8::getInstance().updateKeyboardState(event);
            }
        }

        uint32_t now = SDL_GetTicks();

        if (now - lastCPUTime >= CPU_DELAY_MS) {
            Chip8::getInstance().cycle();
            lastCPUTime = now;
        }

        if (now - lastFrameTime >= FRAME_DELAY_MS) {
            Chip8::getInstance().render(renderer);
            lastFrameTime = now;
        }

        if (now - lastTimerUpdate >= TIMER_DELAY_MS) {
            Chip8::getInstance().decrementTimer();
            lastTimerUpdate = now;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


    SDL_Quit();
    system("pause");
    return 0;
}