#include "Application.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"


Application::Application() {
	std::cout << "Application started\n";
	if (SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "SDL initialized successfully\n";
	Window w;
	SDL_Delay(1000);
}


Application::~Application() {
	std::cout << "Application is terminating...\n";
	SDL_Quit();
}
