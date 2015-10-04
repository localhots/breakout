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

    bool collides_with(int x1, int y1, int x2, int y2);
    void destroy();
    void render();
private:
    SDL_Renderer *renderer;

    SDL_Rect brick;
    Color color;
    bool visible;
};
