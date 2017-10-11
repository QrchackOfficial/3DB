#include "Application.h"
#include <iostream>
#include <SDL.h>
#include "Window.h"


void Application::handleEvents() {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			kill();
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_ESCAPE:
				kill();
				break;
			case SDLK_1:
				// w->setBgColor(1.0, 0.0, 0.0);
				break;
			case SDLK_2:
				// w->setBgColor(0.0, 1.0, 0.0);
				break;
			case SDLK_3:
				// w->setBgColor(0.0, 0.0, 1.0);
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


void Application::drawFrame() const {
	w->redraw();
}

void Application::update(float dt) {
	drawFrame();
	handleEvents();
}

Application::Application() {
	l = new Log("debuglog.txt", true);
	l->print("Application started");
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	l->print("SDL initialized successfully");
	w = new Window();

	// Main loop
	while (running) {
		static double timeLast = SDL_GetTicks();
		double timeCurrent = SDL_GetTicks();
		float timeDelta = float(timeCurrent - timeLast);

		update(timeDelta);

		timeLast = timeCurrent;
	}
}


Application::~Application() {
	l->print("Application is terminating...");
	delete w;
	delete l;
	SDL_Quit();
}
