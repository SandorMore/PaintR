#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>

constexpr inline int WIDTH = 1920;
constexpr inline int HEIGHT = 1080;


typedef struct {
	int mouseX;
	int mouseY;
} Mouse;

typedef struct {
	uint8_t r, g, b;
} Color;

class Handler {
public:
	Handler(SDL_Window* _window, SDL_Renderer* _renderer) :window(_window), renderer(_renderer) 
	{
		mouse = new Mouse;
		mouse->mouseX = 0;
		mouse->mouseY = 0;

		pixels = new Color * [HEIGHT];
		for (int i = 0; i < HEIGHT; i++)
			pixels[i] = new Color[WIDTH];
	}

	void fill() 
	{
		for (size_t y = 0; y < HEIGHT; ++y) 
		{
			for (size_t x = 0; x < WIDTH; ++x) 
			{
				pixels[y][x] = { 0,0,0 };
			}
		}
	}

	void render(SDL_Renderer* renderer) 
	{
		for (size_t y = 0; y < HEIGHT; ++y)
		{
			for (size_t x = 0; x < WIDTH; ++x)
			{
				Color& c = pixels[y][x];

				SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);

	}

	void entry() 
	{
		fill();
		while(!close)
		{
			
			while (SDL_PollEvent(&event)) 
			{
				if (event.type == SDL_QUIT)
					close = true;

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
					close = true;
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);


			render(renderer);
		}
	}
	~Handler() 
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		
		for (int i = 0; i < HEIGHT; i++)
			delete[] pixels[i];
		delete[] pixels;

		delete mouse;
		mouse = nullptr;
	}
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Mouse* mouse;
	SDL_Event event;
	bool close = false;
	Color** pixels;
};