#include <iostream>
#include "SDL2/SDL.h"
#include "breakout.h"
#include "scene.h"

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

    Scene scene(window, renderer);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        bool has_event = false;
        while (SDL_PollEvent(&e)) {
            has_event = true;
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_q:
                    quit = true;
                    break;
                case SDLK_LEFT:
                    scene.move_pad_relative(-KEY_MOVE_STEP);
                    break;
                case SDLK_RIGHT:
                    scene.move_pad_relative(KEY_MOVE_STEP);
                    break;
                }
            }
            if (e.type == SDL_MOUSEMOTION) {
                scene.move_pad(e.motion.x - PAD_WIDTH / 2);
            }
        }

        if (has_event) {
            scene.render();
        } else {
            SDL_Delay(1);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Exiting nicely" << std::endl;
    return 0;
}
