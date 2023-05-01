#pragma once
#include "Operators.h"
#include "Variables.h"
#include "ascii.h"

enum valType {
	typeNone,
	typeNum,
	typeVar,
	typeNode,
	typeFunc
};

class VarDetect
{
public:
	bool isAccepted(std::string text, int pla);
	void clear();
	varinc getVal();
	double getNum();	
	std::string varnam;
	bool neg = false;
	valType type = typeNone;
	double val = 0;
	bool node = false;
private:
	void haniden();
	bool hasiden = false;
	bool hasspa = false;
	bool decimal = false;
	bool numneg = false;
	bool expneg = false;
	bool hase = false;
	int dplas = 0;	
	int exp = 0;
	strmeth meth;
	
	
};

