#include "System/Application.h"
#include "System/Log.h"

#include <SDL.h>

int main(int argc, char* argv[]) {
	Log l("debuglog.txt", true);
	Application _3DBApp = Application(l);
	return 0;
}