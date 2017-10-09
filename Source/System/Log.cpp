#include "Log.h"
#include <iostream>

std::streambuf* Log::getCoutBuf() {
	return std::cout.rdbuf();
}

Log::Log() {
	logStream.open("debug.log");
	coutbuf = getCoutBuf();
}

Log::Log(char* outFile) {
	logStream.open(outFile);
	coutbuf = getCoutBuf();
}

Log::Log(char* outFile, bool redirect) {
	logStream.open(outFile);
	coutbuf = getCoutBuf();
	setCoutRedirect(true);
}

void Log::setCoutRedirect(const bool redirect) const {
	if (redirect)
		std::cout.rdbuf(logStream.rdbuf());
	else
		std::cout.rdbuf(coutbuf);
}

void Log::print(char* message) {
	logStream << message << std::endl;
}

Log::~Log() {
	setCoutRedirect(false);
	logStream.close();
}
