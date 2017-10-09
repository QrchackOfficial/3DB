#include "System/Application.h"
#include "System/Log.h"

#include <SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
	Log l("debuglog.txt", true);
	new Application();
	//SDL_Init((SDL_INIT_VIDEO));
	//SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Delay(2000);
	return 0;
}
