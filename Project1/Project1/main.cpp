#define SDL_MAIN_HANDLED
#include "Handler.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>

bool close = false;

void handle_input() {

}

int main(int argc, char** argv) {
	
	auto start = std::chrono::high_resolution_clock::now();
	
	if (SDL_Init(SDL_INIT_EVERYTHING)) 
	{
		std::cout << "Error during initialization: " << SDL_GetError();
		
		return 1;

	}

	SDL_Window* window = SDL_CreateWindow("PaintR", 100, 100, 1280, 720, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	Handler handler{window, renderer};

	// start the program
	handler.entry();

	auto end = std::chrono::high_resolution_clock::now();
		
	std::cout << "Run ended at: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start) << "\n";

	return 0;
}