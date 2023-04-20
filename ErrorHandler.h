#pragma once
#include <functional>
#include <vector>
#include <string>

struct errInfo {
	int errType, errLine;
	std::string errMes, lineText;
};

class ErrorHandler
{
public:
	void setHandler(std::function<void(errInfo)> ahan);
	void report(int errNum);
	bool beenReported = false;
	int curline = 0;
	std::string line;
	std::function<void(errInfo)> handler;
};

