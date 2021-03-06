#import "brick.hpp"

Brick::Brick(SDL_Renderer *r, int x, int y, Color c) {
    renderer = r;
    brick.x = x;
    brick.y = y;
    brick.w = BRICK_WIDTH;
    brick.h = BRICK_HEIGHT;
    color = c;
    visible = true;
}

Brick::~Brick() {}

BounceDirection Brick::collide(int x1, int y1, int x2, int y2) {
    if (!(
        visible &&
        brick.x <= x2 &&
        brick.x + BRICK_WIDTH >= x1 &&
        brick.y <= y2 &&
        brick.y + BRICK_HEIGHT >= y1
    )) {
        return None;
    }

    if (y1 <= brick.y - BRICK_HEIGHT/2) {
        return Bottom;
    } else if (y1 >= brick.y + (BRICK_HEIGHT/2)) {
        return Top;
    } else if (x1 < brick.x) {
        return Left;
    } else if (x1 > brick.x) {
        return Right;
    } else {
        DEBUG("WTF!");
        return None;
    }
}

void Brick::destroy() {
    visible = false;
}

void Brick::render() {
    if (!visible) {
        return;
    }

    switch (color) {
    case RED:
        SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
        break;
    case ORANGE:
        SDL_SetRenderDrawColor(renderer, 255, 153, 51, 255);
        break;
    case YELLOW:
        SDL_SetRenderDrawColor(renderer, 255, 255, 51, 255);
        break;
    case GREEN:
        SDL_SetRenderDrawColor(renderer, 153, 255, 51, 255);
        break;
    case LIGHTBLUE:
        SDL_SetRenderDrawColor(renderer, 51, 255, 255, 255);
        break;
    case BLUE:
        SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
        break;
    case PURPLE:
        SDL_SetRenderDrawColor(renderer, 153, 51, 255, 255);
        break;
    }
    SDL_RenderFillRect(renderer, &brick);
}
