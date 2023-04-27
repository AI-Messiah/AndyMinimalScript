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

struct varinc {
	int num;
	bool neg;
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
	std::vector<valFrom> Src;
	std::vector<double> Val;
	std::vector<varinc> Var;
	
	std::vector<OpNode> nodes;
};

