#include "Window.h"

#include <SDL.h>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include "../OpenGL/LoadShader.h"

void Window::redraw() {

	// Background
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable shaders
	glUseProgram(programID);

	// First attribute buffer - vertices
	glEnableVertexAttribArray(0);
	// Select vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glVertexAttribPointer(
		0,			// attribute
		3,			// size
		GL_FLOAT,	// type
		GL_FALSE,	// normalize?
		0,			// stride
		nullptr		// array buffer offset
	);

	// Draw starting from vertex 0
	// 3 total vertices
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Cleanup
	glDisableVertexAttribArray(0);

	// Swap buffer
	SDL_GL_SwapWindow(window);
}

Window::Window() {

	// Disable legacy OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Request an OpenGL 3.3 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

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

	// Load shaders
	programID = LoadShader(
		"..\\Source\\Shaders\\VertexShader.glsl",
		"..\\Source\\Shaders\\FragmentShader.glsl"
	);

	// OpenGL setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, width, height);

	// Generate and select vertex array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Static model data
	static const GLfloat gVertexData[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};

	// Generate and select vertex buffer
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Send vertex data
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(gVertexData),
				 gVertexData,
				 GL_STATIC_DRAW
	);

	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
