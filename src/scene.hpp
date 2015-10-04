#include <vector>
#include "SDL2/SDL.h"
#include "breakout.hpp"
#import "brick.hpp"

class Scene {
public:
    Scene(SDL_Renderer *r);
    ~Scene();

    void render();
    void move_pad(int x);
    void move_pad_relative(int delta);
private:
    SDL_Renderer *renderer;

    SDL_Rect pad;
    std::vector<Brick> bricks;
};
