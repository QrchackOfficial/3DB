#pragma once
#include <fstream>

class Log {
private:
	bool redirectCout = false;
	std::streambuf* coutbuf;
	std::ofstream logStream;
	static std::streambuf* getCoutBuf();
public:
	Log();
	Log(char* outFile);
	Log(char* outFile, bool redirect);
	~Log();
	void setCoutRedirect(bool redirect) const;
	void print(char* message);
};

