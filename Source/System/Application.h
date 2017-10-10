#pragma once
#include <SDL.h>
#include "Window.h"

class Application {
private:
	bool running = true;
	Window* w;
	SDL_Event e;
public:
	void kill() {
		running = false;
	}

	void handleEvents();
	void drawFrame() const;
	void update(float dt);
	Application();
	~Application();
};

