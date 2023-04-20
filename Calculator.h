#pragma once
#include <cmath>

enum tokenName {
	opNone,
	opExponent,
	opMultiply,
	opDivide,
	opModular,
	opAdd,
	opSubtract,
	opBitAnd,
	opBitOr,
	opGreat,
	opLess,
	opEqual,
	opNotEqual,
	opGreatEqual,
	opLessEqual,
	opInvert,
	opAnd,
	opOr,
	opAssignMul,
	opAssignDiv,
	opAssignMod,
	opAssignAdd,
	opAssignSub,
	opAssignDirect
};

class Calculator
{
public:
	Calculator();
	~Calculator();
	double Calculate(double val1, double val2, tokenName token);
};

