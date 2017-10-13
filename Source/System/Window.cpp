#include "Window.h"

#include <SDL.h>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../OpenGL/LoadShader.hpp"
#include <ctime>

void Window::redraw() {
	using glm::vec3;

	// Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Compute model transform
	View = glm::lookAt(
		vec3(4, 3, 3), // Camera position
		vec3(0, 0, 0), // Look up at the origin
		vec3(0, 1, 0) // Head is up
	);

	// Compute and send transformation matrix
	// to the vertex shader
	MVP = Projection * View * Model;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Enable shaders
	glUseProgram(programID);

	// First attribute buffer - vertices
	glEnableVertexAttribArray(0);
	// Select vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	glVertexAttribPointer(
		0, // attribute
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalize?
		0, // stride
		nullptr // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		nullptr
	);

	// Draw starting from vertex 0
	// 12 triangles
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

	// Cleanup
	glDisableVertexAttribArray(0);

	// Swap buffer
	SDL_GL_SwapWindow(window);
}

/**
 * \return A random float value in the 0.0-1.0 range
 */
float Window::getRandom() {
	return float(rand()) / float(RAND_MAX);
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
	programID = loadShader(
		"..\\Source\\Shaders\\VertexShader.glsl",
		"..\\Source\\Shaders\\FragmentShader.glsl"
	);

	// Get a handle for MVP uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// OpenGL setup

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept elements that are closer than the previous ones
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, width, height);


	// Static model data
	static const GLfloat gVertexData[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	// Seed random generator
	const unsigned int seed = static_cast<unsigned int>(time(nullptr));
	srand(seed);

	// Generate colors
	static GLfloat gColorData[12 * 3 * 3];
	for (int v = 0; v < 12 * 3; v++) {
		gColorData[3 * v + 0] = getRandom();
		gColorData[3 * v + 1] = getRandom();
		gColorData[3 * v + 2] = getRandom();
	}

	// Generate and select vertex array
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Matrices for model
	Projection = glm::perspective(
		glm::radians(45.0f), // FoV
		float(width) / float(height), // Aspect ratio
		0.1f, 100.f // 0.1u - 100u
	);


	// Generate and select vertex buffer
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Send vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(gVertexData),
		gVertexData,
		GL_STATIC_DRAW
	);

	// Generate and select color buffer
	glGenBuffers(1, &ColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);

	// Send color data
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(gColorData),
		gColorData,
		GL_STATIC_DRAW
	);

	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
