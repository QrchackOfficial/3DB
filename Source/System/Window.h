#pragma once
#include <SDL_video.h>

class Window {
private:
	SDL_Window* window = nullptr;
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int width = 800;
	int height = 600;
public:

	int getX() const {
		return x;
	}
	void setX(const int x) {
		this->x = x;
	}
	int getY() const {
		return y;
	}
	void setY(const int y) {
		this->y = y;
	}
	int getWidth() const {
		return width;
	}
	void setWidth(const int width) {
		this->width = width;
	}
	int getHeight() const {
		return height;
	}
	void setHeight(const int height) {
		this->height = height;
	}
	Window();
	~Window();
};

