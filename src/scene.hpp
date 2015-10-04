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
    void launch_ball();
private:
    void move_ball();

    SDL_Renderer *renderer;

    bool ball_moving;
    int ball_velx;
    int ball_vely;
    SDL_Rect ball;
    SDL_Rect pad;
    std::vector<Brick> bricks;
};
