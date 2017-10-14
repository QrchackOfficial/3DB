#include "Window.h"
#include "../OpenGL/Model.hpp"

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

void Window::setupOpenGL() {
	// Disable legacy OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Request an OpenGL 3.3 context
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

SDL_GLContext Window::getContext() {
	SDL_GLContext ctx = SDL_GL_CreateContext(window);

	// Enable v-sync
	SDL_GL_SetSwapInterval(1);

	// Initialize GLEW
	glewExperimental = GL_TRUE; // We want OpenGL 3.0 and later
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW\n";
		exit(EXIT_FAILURE);
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept elements that are closer than the previous ones
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glViewport(0, 0, width, height);

	return ctx;
}

SDL_Window* Window::createWindow(char* title, int width, int height) {
	SDL_Window* w = SDL_CreateWindow("", x, y, width, height, SDL_WINDOW_OPENGL);
	if (!w) {
		std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	return w;
}

void Window::resetSeed() {
	// Seed random generator
	const unsigned int seed = static_cast<unsigned int>(time(nullptr));
	srand(seed);
}

Window::Window() {
	using ::Model;

	resetSeed();
	setupOpenGL();
	window = createWindow("", width, height);
	ctx = getContext();

	programID = loadShader(
		"..\\Source\\Shaders\\VertexShader.glsl",
		"..\\Source\\Shaders\\FragmentShader.glsl"
	);

	Model mCube{};

	// Get a handle for MVP uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

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

	int vds = mCube.getVertexDataSize();
	int cds = mCube.getColorDataSize();

	// Send vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		mCube.getVertexDataSize(),
		mCube.getVertexData(),
		GL_STATIC_DRAW
	);

	// Generate and select color buffer
	glGenBuffers(1, &ColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBuffer);

	// Send color data
	glBufferData(
		GL_ARRAY_BUFFER,
		mCube.getColorDataSize(),
		mCube.getColorData(),
		GL_STATIC_DRAW
	);

	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
}
