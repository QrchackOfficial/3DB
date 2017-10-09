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
	void setWindowSize(const int width, const int height) const {
		SDL_SetWindowSize(window, width, height);
	}
	void setWindowPosition(const int x, const int y) {
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
	Window();
	~Window();
};

