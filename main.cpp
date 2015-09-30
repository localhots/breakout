#include <iostream>
#include "SDL2/SDL.h"

#define SCREEN_X 100
#define SCREEN_Y 100
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PAD_WIDTH 200
#define PAD_HEIGHT 20

#define KEY_MOVE_STEP 5

#define BG_COLOR 0, 0, 0, 255
#define PAD_COLOR 0, 0, 255, 255

int main(int argc, char const *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Breakout",
        SCREEN_X, SCREEN_Y,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
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

    // Setting background color to black
    SDL_SetRenderDrawColor(renderer, BG_COLOR);
    SDL_RenderClear(renderer);

    // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
    SDL_Rect pad = {
        .x = (SCREEN_WIDTH - PAD_WIDTH) / 2,
        .y = (SCREEN_HEIGHT - PAD_HEIGHT),
        .w = PAD_WIDTH,
        .h = PAD_HEIGHT
    };

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor(renderer, PAD_COLOR);

    // Render rect
    SDL_RenderFillRect(renderer, &pad);

    // Render the rect to the screen
    SDL_RenderPresent(renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_LEFT:
                    pad.x -= KEY_MOVE_STEP;
                    break;
                case SDLK_RIGHT:
                    pad.x += KEY_MOVE_STEP;
                    break;
                }
            }
            if (e.type == SDL_MOUSEMOTION) {
                pad.x = e.motion.x - PAD_WIDTH / 2;
            }

            if (pad.x < 0) {
                pad.x = 0;
            } else if (pad.x > SCREEN_WIDTH - PAD_WIDTH) {
                pad.x = SCREEN_WIDTH - PAD_WIDTH;
            }
        }

        // Re-rendering
        SDL_SetRenderDrawColor(renderer, BG_COLOR);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, PAD_COLOR);
        SDL_RenderFillRect(renderer, &pad);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Exiting nicely" << std::endl;
    return 0;
}
