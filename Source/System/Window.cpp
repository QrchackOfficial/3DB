#include "Window.h"
#include <SDL.h>
#include <iostream>

Window::Window() {
	window = SDL_CreateWindow("", x, y, width, height, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_DestroyWindow(window);
}
