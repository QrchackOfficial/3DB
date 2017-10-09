#include "Application.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"


Application::Application() {
	std::cout << "Application started\n";
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "SDL initialized successfully\n";
	Window w;
	SDL_Event e;
	while (running) {
		w.redraw();

		// Handle events
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				kill();

		}
	}
}


Application::~Application() {
	std::cout << "Application is terminating...\n";
	SDL_Quit();
}
