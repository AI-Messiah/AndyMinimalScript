#pragma once
#include "Process.h"

class Interface
{
public:
	void handleScript(std::string text);
	void setFunction(std::string name, std::function<double(std::vector<double>)> address);
	void setErrorHandler(std::function<void(std::vector<errInfo>)> ahan);
	AndyInt::OpNode debugTree(std::string text);
private:
	Process proc;
};

