#include "System/Application.h"

#include <SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
	new Application();
	SDL_Init((SDL_INIT_VIDEO));
	SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(2000);
	return 0;
}