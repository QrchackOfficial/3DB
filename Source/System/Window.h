#pragma once
#include <SDL_video.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/mat4x4.hpp>

class Window {
private:
	SDL_Window* window = nullptr;
public:
	SDL_Window* getWindow() const { return window; }
private:
	SDL_GLContext ctx = nullptr;
	float bgColor[3] = {0.0f, 0.0f, 0.2f};

	// Window settings
	int x = SDL_WINDOWPOS_CENTERED;
	int y = SDL_WINDOWPOS_CENTERED;
	int width = 800;
	int height = 600;

	GLuint VertexArrayID;

	GLuint VertexBuffer;
	GLuint Texture;
	GLuint TextureID;
	GLuint UVBuffer;

	GLuint programID;
	GLuint MatrixID;

	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 MVP;
	glm::vec3 cameraPosition = glm::vec3(0, 0, 5);
	glm::vec3 direction;
	glm::vec3 up;

	float hAngle = 3.14f;
	float vAngle = 0.0f;
	float FoV = 45.0f;
	float cameraSpeed = 0.1f;
	float mouseSpeed = 0.0005f;
	int mouseX, mouseY;

	void setupOpenGL();
	SDL_GLContext getContext();
	SDL_Window* Window::createWindow(char* title, int width, int height);
	void resetSeed();

public:
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(hAngle - 3.14f / 2.0f),
		0,
		cos(hAngle - 3.14f / 2.0f)
	);
	bool isActive = true;
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

	void redraw(float dt);

	glm::vec3 getCameraPosition() const {
		return cameraPosition;
	}

	float getFoV() const {
		return FoV;
	}

	float getCameraSpeed() const {
		return cameraSpeed;
	}

	float getMouseSpeed() const {
		return mouseSpeed;
	}
	void setCameraPosition(const glm::vec3& camera_position) {
		cameraPosition = camera_position;
	}
	void setFoV(float fov) {
		FoV = fov;
	}
	void setCameraSpeed(float speed) {
		cameraSpeed = speed;
	}
	void setMouseSpeed(float speed) {
		mouseSpeed = speed;
	}
	glm::vec3 getDirection() const {
		return direction;
	}
	float getRandom();
	Window();
	~Window();
};
