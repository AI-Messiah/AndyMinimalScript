#include "Interface.h"

void Interface::handleScript(std::string text)
{
	proc.varscan(text);
}

void Interface::setFunction(std::string name, std::function<double(std::vector<double>)> address)
{
	trans.setFunction(name, address);
}

void Interface::setErrorHandler(std::function<void(errInfo)> ahan)
{
	ahand.setHandler(ahan);
}

void Interface::debugfunc(std::string text)
{
	proc.maker.createTree(text);
}


