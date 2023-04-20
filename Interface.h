#pragma once
#include "Process.h"

class Interface
{
public:
	void handleScript(std::string text);
	void setFunction(std::string name, std::function<double(std::vector<double>)> address);
	void setErrorHandler(std::function<void(errInfo)> ahan);
	
private:
	Process proc;
};

