#include <iostream>
#include "SDL2/SDL.h"
#include "breakout.h"
#include "scene.h"

Scene::Scene(SDL_Window *w, SDL_Renderer *r) {
    window = w;
    renderer = r;

    pad.x = (SCREEN_WIDTH - PAD_WIDTH) / 2;
    pad.y = (SCREEN_HEIGHT - PAD_HEIGHT);
    pad.w = PAD_WIDTH;
    pad.h = PAD_HEIGHT;
}

Scene::~Scene() {}

void Scene::render() {
    SDL_SetRenderDrawColor(renderer, BG_COLOR);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, PAD_COLOR);
    SDL_RenderFillRect(renderer, &pad);
    SDL_RenderPresent(renderer);
}

void Scene::move_pad(int x) {
    pad.x = x;

    if (pad.x < 0) {
        pad.x = 0;
    } else if (pad.x > SCREEN_WIDTH - PAD_WIDTH) {
        pad.x = SCREEN_WIDTH - PAD_WIDTH;
    }
}

void Scene::move_pad_relative(int delta) {
    move_pad(pad.x + delta);
}
