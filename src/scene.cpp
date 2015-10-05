#include "scene.hpp"

Scene::Scene(SDL_Renderer *r) {
    DEBUG("[?] Initializing scene");
    renderer = r;

    pad.x = (SCREEN_WIDTH - PAD_WIDTH) / 2;
    pad.y = SCREEN_HEIGHT - PAD_HEIGHT;
    pad.w = PAD_WIDTH;
    pad.h = PAD_HEIGHT;

    ball.x = SCREEN_WIDTH/2 - BALL_RADIUS;
    ball.y = SCREEN_HEIGHT/2 - BALL_RADIUS;
    ball.w = BALL_RADIUS * 2;
    ball.h = BALL_RADIUS * 2;
    ball_moving = true;
    ball_velx = 0;
    ball_vely = 0;
    launch_ball();

    for (int i = 0; i < BRICK_ROWS; i++) {
        for (int j = 0; j < BRICK_COLS; j++) {
            bricks.push_back(Brick(renderer, j * BRICK_WIDTH + j, i * BRICK_HEIGHT + i, (Color)i));
        }
    }

    DEBUG("[!] Scene initialized");
}

Scene::~Scene() {}

void Scene::render() {
    // Draw background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw pad
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &pad);

    // Draw bricks
    for (int i = 0; i < NUM_BRICKS; i++) {
        bricks[i].render();
    }

    // Draw ball
    move_ball();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ball);

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

void Scene::launch_ball() {
    ball.x = SCREEN_WIDTH/2 - BALL_RADIUS;
    ball.y = SCREEN_HEIGHT/2 - BALL_RADIUS;
    ball_moving = true;

    ball_velx = 3;
    ball_vely = 5;

    if (rand() > RAND_MAX/2) {
        ball_velx = -ball_velx;
    }
}

void Scene::move_ball() {
    if (!ball_moving) {
        return;
    }

    ball.x += ball_velx;
    ball.y += ball_vely;

    // Collisions

    // Left
    if (ball.x <= 0) {
        ball_velx = -ball_velx;
    }
    // Right
    if (ball.x >= SCREEN_WIDTH - 2*BALL_RADIUS) {
        ball_velx = -ball_velx;
    }
    // Top
    if (ball.y <= 0) {
        ball_vely = -ball_vely;
    }
    // Bottom
    if (ball.y >= SCREEN_HEIGHT) {
        launch_ball();
        DEBUG("Loser!");
    }
    // Pad
    if (ball.x >= pad.x && ball.x <= pad.x + PAD_WIDTH && ball.y + 2*BALL_RADIUS >= pad.y) {
        ball_vely = -ball_vely;
    }
    // Bricks
    for (int i = NUM_BRICKS; i >= 0; --i) {
        int x1 = ball.x;
        int y1 = ball.y;
        int x2 = ball.x + 2*BALL_RADIUS;
        int y2 = ball.y + 2*BALL_RADIUS;

        BounceDirection dir = bricks[i].collide(x1, y1, x2, y2);
        switch (dir) {
        case None:
            continue;
        case Top:
        case Bottom:
            ball_vely = -ball_vely;
            break;
        case Left:
        case Right:
            ball_velx = -ball_velx;
            break;
        }

        bricks[i].destroy();
    }
}
