#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <vector>
#include <atomic>
#include <mutex>
#include <thread>

int main(int argc, char** argv) {
	std::cout << "Start!" << "\n";
	return 0;
}