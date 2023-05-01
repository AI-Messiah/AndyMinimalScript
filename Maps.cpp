#include "Maps.h"


int prior[] = { 0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 5, 5, 5, 5, 6, 7, 8, 9, 9, 9, 9, 9, 9 };

Maps::Maps()
{
	tokenProperty tempProp;
	std::string temsym;
	tokenName temp[] = {opExponent, opMultiply, opDivide, opModular, opAdd, opSubtract, opBitAnd, opBitOr,	opGreat, opLess, opEqual, opNotEqual, opGreatEqual,	opLessEqual, opInvert, opAnd, opOr,	opAssignMul, opAssignDiv, opAssignMod, opAssignAdd,	opAssignSub, opAssignDirect };
	for (int i = 0; i < int(mathOps.length() / 2); i++) {
		priority[i] = prior[i];
		temsym = mathOps.substr(i * 2, 2);
		if (temsym.substr(1, 1) == " " && prior[i] < 9) temsym = temsym.substr(0, 1);
		convertedTokens[temsym] = temp[i];
		tempProp.type = (prior[i] < 9) ? Operator : Assignment;
		tempProp.internal = false;
		tempProp.ambiguous = (temsym == "-");
		convertedProperties[temp[i]] = tempProp;
	}
}

Maps::~Maps()
{
}
