#pragma once
#include <SDL_video.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class Window {
private:
	SDL_Window* window = nullptr;
	SDL_GLContext ctx = nullptr;
	float bgColor[3] = {0.0f, 0.0f, 0.2f};

	// Window settings
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int width = 800;
	int height = 600;

	GLuint VertexArrayID;

	GLuint VertexBuffer;
	GLuint ColorBuffer;

	GLuint programID;
	GLuint MatrixID;

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 MVP;


	void setupOpenGL();
	SDL_GLContext getContext();
	SDL_Window* Window::createWindow(char* title, int width, int height);
	void resetSeed();

public:
	static const int center = SDL_WINDOWPOS_CENTERED;

	void setWindowSize(const int width, const int height) const {
		SDL_SetWindowSize(window, width, height);
	}
	void setBgColor(const float r, const float g, const float b) {
		bgColor[0] = r;
		bgColor[1] = b;
		bgColor[2] = g;
	}
	void setWindowPosition(const int x, const int y) const {
		SDL_SetWindowPosition(window, x, y);
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void redraw();
	float getRandom();
	Window();
	~Window();
};

