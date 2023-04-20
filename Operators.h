#pragma once
#include "Globalize.h"

#include <string>
#include <vector>

enum valFrom {
	valNone,
	valVar,
	valValue,
	valNode,
	valIndexed,
	valFixed,
	valInternal,
	valExternal
};


class OpNode
{
public:
	OpNode();
	~OpNode();
	
	double evaluate();
	void clear();
	
	bool assign(tokenName tok, double ival);
	tokenName oper = opNone;
	bool empty = false;
	int  levels = 0;
	bool left = false;
	
	std::vector<valFrom> Src;
	std::vector<double> Val;
	std::vector<int> Var;
	
	std::vector<OpNode> nodes;
};

