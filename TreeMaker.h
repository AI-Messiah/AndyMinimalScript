#pragma once
#include <sstream>
#include <iomanip>
#include "Maps.h"
#include "ascii.h"
#include "VarDetect.h"

class TreeMaker
{
public:
	OpNode createTree(std::string text);
private:
	
	VarDetect vdet[2];
	std::string acChars = ",-.0123456789#abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ^*/\\+&|!=<>";
	strmeth meth;
	Maps smp;
	OpNode combvar(OpNode inod, varinc var);
	OpNode combfun(OpNode inod, int fun, bool neg, bool internal);
	int countNodes(std::string text, int index);	
	bool hasPeren(std::string text);
	std::string fromNum(double val);	
	bool detComma(std::string text);
	OpNode numwithvar(double num, varinc var, tokenName token);
	OpNode varwithnum(varinc var, double num, tokenName token);
	OpNode varwithvar(varinc var1, varinc var2, tokenName token);
	OpNode varwithnode(varinc var, OpNode nod, tokenName token);
	OpNode nodewithvar(OpNode nod, varinc var, tokenName token);
	OpNode numwithnode(double num, OpNode nod, tokenName token);
	OpNode nodewithnum(OpNode nod, double num, tokenName token);
	OpNode nodewithnode(OpNode nod1, OpNode nod2, tokenName token);
	OpNode valwithfunc(double num, OpNode nod, tokenName token);
	OpNode funcwithval(OpNode nod, double num, tokenName token);
	OpNode varwithfunc(varinc var, OpNode nod, tokenName token);
	OpNode funcwithvar(OpNode nod, varinc var, tokenName token);
	OpNode funcwithnode(OpNode nod1, OpNode nod2, tokenName token);
	OpNode nodewithfunc(OpNode nod1, OpNode nod2, tokenName token);
	OpNode funcwithfunc(OpNode nod1, OpNode nod2, tokenName token);
	OpNode numwithfunc(double num, OpNode nod, tokenName token);
};

