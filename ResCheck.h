#pragma once
#include "Variables.h"
#include "ascii.h"

class ResCheck
{
public:
	ResCheck();
	void Check(std::string text);
private:
	strmeth meth;
	std::vector<std::string> words;
};

