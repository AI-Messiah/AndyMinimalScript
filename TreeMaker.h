#pragma once
#include <sstream>
#include <iomanip>
#include "Maps.h"
#include "ascii.h"

enum valType {
	typeNum,
	typeVar,
	typeNode,
	typeFunc
};

class TreeMaker
{
public:
	OpNode createTree(std::string text);
private:
	strmeth meth;
	Maps smp;
	OpNode combvar(OpNode inod, std::string var);
	OpNode combfun(OpNode inod, int fun, bool internal);
	int countNodes(std::string text, int index);
	std::string calculate(double val1, double val2, tokenName token);
	bool hasPeren(std::string text);
	std::string fromNum(double val);	
	bool detComma(std::string text);
	OpNode numwithvar(double num, std::string var, tokenName token);
	OpNode varwithnum(std::string var, double num, tokenName token);
	OpNode varwithvar(std::string var1, std::string var2, tokenName token);
	OpNode varwithnode(std::string var, OpNode nod, tokenName token);
	OpNode nodewithvar(OpNode nod, std::string var, tokenName token);
	OpNode numwithnode(double num, OpNode nod, tokenName token);
	OpNode nodewithnum(OpNode nod, double num, tokenName token);
	OpNode nodewithnode(OpNode nod1, OpNode nod2, tokenName token);
	OpNode valwithfunc(double num, OpNode nod, tokenName token);
	OpNode funcwithval(OpNode nod, double num, tokenName token);
	OpNode varwithfunc(std::string var, OpNode nod, tokenName token);
	OpNode funcwithvar(OpNode nod, std::string var, tokenName token);
	OpNode funcwithnode(OpNode nod1, OpNode nod2, tokenName token);
	OpNode nodewithfunc(OpNode nod1, OpNode nod2, tokenName token);
	OpNode funcwithfunc(OpNode nod1, OpNode nod2, tokenName token);
	OpNode numwithfunc(double num, OpNode nod, tokenName token);
};

