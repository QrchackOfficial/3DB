#include "Application.h"
#include "Window.h"

#include <iostream>
#include <SDL.h>


void Application::handleEvents() {
	while (SDL_PollEvent(&eventPending)) {
		switch (eventPending.type) {
		case SDL_QUIT:
			kill();
			break;
		case SDL_KEYDOWN:
			switch (eventPending.key.keysym.sym) {
			case SDLK_ESCAPE:
				kill();
				break;
			case SDLK_1:
				w->setBgColor(0.2f, 0.0f, 0.0f);
				break;
			case SDLK_2:
				w->setBgColor(0.0f, 0.2f, 0.0f);
				break;
			case SDLK_3:
				w->setBgColor(0.0f, 0.0f, 0.2f);
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
	log = new Log("debuglog.txt", true);
	log->print("Application started");
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	log->print("SDL initialized successfully");
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
	log->print("Application is terminating...");
	delete w;
	delete log;
	SDL_Quit();
}
