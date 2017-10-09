#pragma once
#include <SDL_video.h>

class Window {
private:
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;
	float bgColor[3] = {0.0f, 0.0f, 0.0f};
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int width = 800;
	int height = 600;
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
	Window();
	~Window();
};

