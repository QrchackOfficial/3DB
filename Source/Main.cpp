#include "System/Application.h"
#include "System/Log.h"

#include <SDL.h>

#include <iostream>

int main(int argc, char* argv[]) {
	Log l("debuglog.txt", true);
	Application();
	return 0;
}