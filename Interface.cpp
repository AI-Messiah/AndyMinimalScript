#include "Interface.h"

void Interface::handleScript(std::string text)
{
	proc.Preptext(text);
	//proc.convert(text);
}

void Interface::setFunction(std::string name, std::function<double(std::vector<double>)> address)
{
	AndyInt::trans.setFunction(name, address);
}

void Interface::setErrorHandler(std::function<void(std::vector<errInfo>)> ahan)
{
	AndyInt::ahand.setHandler(ahan);
}

void Interface::shutdown()
{
	proc.shutDown();
}






