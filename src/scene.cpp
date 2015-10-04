#include "scene.hpp"

Scene::Scene(SDL_Renderer *r) {
    DEBUG("[?] Initializing scene");
    renderer = r;

    pad.x = (SCREEN_WIDTH - PAD_WIDTH) / 2;
    pad.y = (SCREEN_HEIGHT - PAD_HEIGHT);
    pad.w = PAD_WIDTH;
    pad.h = PAD_HEIGHT;

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            bricks.push_back(Brick(renderer, j * BRICK_WIDTH + j, i * BRICK_HEIGHT + i, (Color)i));
        }
    }

    DEBUG("[!] Scene initialized");
}

Scene::~Scene() {}

void Scene::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &pad);
    for (int i = 0; i < BRICK_ROWS * BRICK_COLS; i++) {
        bricks[i].render();
    }
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
