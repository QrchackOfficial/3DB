#pragma once
#include <SDL.h>
#include "Window.h"
#include "Log.h"

class Application {
private:
	bool running = true;
	Window* w;
	SDL_Event eventPending;
	Log* log;
public:
	void kill() {
		running = false;
	}

	void handleEvents(float dt);
	void drawFrame(float dt) const;
	void update(float dt);
	Application();
	~Application();
};

