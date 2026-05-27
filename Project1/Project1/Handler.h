#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;

struct Mouse {
    int x = 0, y = 0;
};

struct Color {
    uint8_t r, g, b;
};

class Handler {
public:
    Handler(SDL_Window* _window, SDL_Renderer* _renderer)
        : window(_window), renderer(_renderer)
    {
        pixels = new Color[WIDTH * HEIGHT];
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24,
            SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    }

    void fill(Color c = { 0, 0, 0 }) 
    {
        for (int i = 0; i < WIDTH * HEIGHT; i++)
            pixels[i] = c;
    }

    void setPixel(int x, int y, Color c) 
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            pixels[y * WIDTH + x] = c;
    }

    void render() {
        SDL_UpdateTexture(texture, nullptr, pixels, WIDTH * sizeof(Color));
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    void __cdecl mouse_action() 
    {
        pixels[mouse.y * WIDTH + mouse.x] = { 123, 220, 23 };
    }

    void entry() {
        fill();
        while (!close) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) close = true;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) close = true;
                if (event.type == SDL_MOUSEMOTION) {
                    mouse.x = event.motion.x;
                    mouse.y = event.motion.y;
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    mouse_action();
                }
            }
            printf("Mouse y: %d, mouse x: %d\n", mouse.y, mouse.x);
            render();
        }
    }

    ~Handler() 
    {
        delete[] pixels;
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Event event;
    Mouse mouse;
    Color* pixels;
    bool close = false;
};