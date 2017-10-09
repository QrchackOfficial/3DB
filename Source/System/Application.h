#pragma once
class Application {
private:
	bool running = true;
public:
	void kill() {
		running = false;
	}
	Application();
	~Application();
};

