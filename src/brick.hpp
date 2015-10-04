#include "SDL2/SDL.h"
#include "breakout.hpp"

typedef enum Color {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    LIGHTBLUE,
    BLUE,
    PURPLE
} Color;

class Brick {
public:
    Brick(SDL_Renderer *r, int x, int y, Color c);
    ~Brick();

    void render();
private:
    SDL_Renderer *renderer;

    SDL_Rect brick;
    Color color;
};
