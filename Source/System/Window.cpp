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
#include "Loaders/LoadBMP.hpp"

void Window::redraw(float dt) {
	using glm::vec3;

	// Background color
	glClearColor(bgColor[0], bgColor[1], bgColor[2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable shaders
	glUseProgram(programID);

	if (isActive) {
		// Get mouse position
		SDL_GetMouseState(&mouseX, &mouseY);
		SDL_WarpMouseInWindow(window, width / 2, height / 2);

		// Compute new orientations
		hAngle += mouseSpeed * dt * float(width / 2 - mouseX);
		vAngle += mouseSpeed * dt * float(height / 2 - mouseY);
	}

	direction = vec3(
		cos(vAngle) * sin(hAngle),
		sin(vAngle),
		cos(vAngle) * cos(hAngle)
	);

	// Up vector
	up = cross(right, direction);

	// Compute and send transformation matrix
	// to the vertex shader
	Projection = glm::perspective(
		glm::radians(FoV),
		float(width) / float(height), // Aspect ratio
		0.1f, 100.f // 0.1u - 100u
	);
	View = glm::lookAt(
		cameraPosition, // Camera position
		cameraPosition + direction, // Look up at the origin
		up // Head is up
	);
	MVP = Projection * View * Model;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(TextureID, 0);

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
	glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
	glVertexAttribPointer(
		1,
		2,
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
	glDisableVertexAttribArray(1);

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

	// Enable face culling
	// (don't draw polygons inside the cube)
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

	Texture = loadBMP("texture.bmp");
	TextureID = glGetUniformLocation(programID, "inTexture");

	// Generate and select vertex buffer
	glGenBuffers(1, &VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);

	// Send vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		mCube.getVertexDataSize(),
		mCube.getVertexData(),
		GL_STATIC_DRAW
	);

	// Generate and select UV buffer
	glGenBuffers(1, &UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);

	// Send UV data
	glBufferData(
		GL_ARRAY_BUFFER,
		mCube.getUVDataSize(),
		mCube.getUVData(),
		GL_STATIC_DRAW
	);

	// Hide cursor
	SDL_ShowCursor(false);

	std::cout << "Window created successfully at " << width << "x" << height << "\n";
}


Window::~Window() {
	std::cout << "Window is being destroyed\n";
	SDL_GL_DeleteContext(ctx);
	SDL_DestroyWindow(window);
}
