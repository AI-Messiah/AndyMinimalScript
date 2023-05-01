#include "Calculator.h"
namespace AndyInt {
	Calculator::Calculator()
	{
	}

	Calculator::~Calculator()
	{
	}

	double Calculator::Calculate(double val1, double val2, tokenName token)
	{
		double result = 0;
		bool trl = val1 != 0;
		bool trr = val2 != 0;
		try {
			switch (token) {
			case opAssignDirect:
				result = val2;
				break;
			case opExponent:
				result = pow(val1, val2);
				break;
			case opAssignMul:
			case opMultiply:
				result = val1 * val2;
				break;
			case opAssignDiv:
			case opDivide:
				result = val1 / val2;
				break;
			case opAssignMod:
			case opModular:
				result = fmod(val1, val2);
				break;
			case opAssignAdd:
			case opAdd:
				result = val1 + val2;
				break;
			case opAssignSub:
			case opSubtract:
				result = val1 - val2;
				break;
			case opBitAnd:
				result = long(val1) & long(val2);
				break;
			case opBitOr:
				result = long(val1) | long(val2);
				break;
			case opGreat:
				result = val1 > val2;
				break;
			case opLess:
				result = val1 < val2;
				break;
			case opEqual:
				result = val1 == val2;
				break;
			case opNotEqual:
				result = val1 != val2;
				break;
			case opGreatEqual:
				result = val1 >= val2;
				break;
			case opLessEqual:
				result = val1 <= val2;
				break;
			case opInvert:
				result = val1 == 0;
				break;
			case opAnd:
				result = (trl && trr) ? 1 : 0;
				break;
			case opOr:
				result = (trl || trr) ? 1 : 0;
				break;
			}


			return result;
		}
		catch (_exception e) {
			ahand.report(0);
			return 0;
		}
		return 0;
	}
}