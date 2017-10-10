#include "Window.h"

#include <SDL.h>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

void Window::redraw() {
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window);
}

Window::Window() {

	// Disable legacy OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Request an OpenGL 3.2 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow("", x, y, width, height, SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	// Get OpenGL context
	context = SDL_GL_CreateContext(window);

	// Enable v-sync
	SDL_GL_SetSwapInterval(1);

	// Initialize GLEW
	glewExperimental = GL_TRUE; // We want OpenGL 3.0 and later
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	// OpenGL setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);

	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
