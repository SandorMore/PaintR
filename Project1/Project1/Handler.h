#include <SDL2/SDL_main.h>
#include <SDL2/SDL.h>

class Handler {
public:
	Handler(SDL_Window* _window, SDL_Renderer* _renderer) :window(_window), renderer(_renderer) {}

	void entry() 
	{
		while(!close)
		{
			while (SDL_PollEvent(&event)) 
			{
				if (event.type == SDL_QUIT)
					close = true;

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
					close = true;

			}
		}
	}
	~Handler() 
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
	}
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	bool close = false;
};