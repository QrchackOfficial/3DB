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
			switch(e.type) {
				case SDL_QUIT:
					kill();
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_ESCAPE:
							kill();
							break;
						case SDLK_1:
							w.setBgColor(1.0, 0.0, 0.0);
							break;
						case SDLK_2:
							w.setBgColor(0.0, 1.0, 0.0);
							break;
						case SDLK_3:
							w.setBgColor(0.0, 0.0, 1.0);
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}
	}
}


Application::~Application() {
	std::cout << "Application is terminating...\n";
	SDL_Quit();
}
