#define PAD_WIDTH 200
#define PAD_HEIGHT 20

#define BG_COLOR 0, 0, 0, 255
#define PAD_COLOR 0, 0, 255, 255

class Scene {
public:
    Scene(SDL_Window *w, SDL_Renderer *r);
    ~Scene();

    void render();
    void move_pad(int x);
    void move_pad_relative(int delta);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect pad;
    SDL_Rect blocks[10];
};
