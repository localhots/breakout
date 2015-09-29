#include <iostream>
#include <unistd.h>
#include "SDL2/SDL.h"

int main(int argc, char const *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Breakout",      // Title
        100, 100,        // X, Y
        640, 480,        // Width, Height
        SDL_WINDOW_SHOWN // Visibility
    );
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, // Window
        -1,     // Video driver. -1 means "any compatible"
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC // Options
    );
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "Sleeping for a second..." << std::endl;
    usleep(1000000);

    std::cout << "Exiting nicely" << std::endl;
    return 0;
}
