#include "Calculator.h"
#pragma STDC FENV_ACCESS on
namespace AndyInt {
	Calculator::Calculator()
	{
	}

	Calculator::~Calculator()
	{
	}

	double Calculator::Calculate(double val1, double val2, tokenName token)
	{
		std::feclearexcept(FE_ALL_EXCEPT);
		double result = 0;
		bool trl = val1 != 0;
		bool trr = val2 != 0;
	
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
			if (val1 < 18446744073709551616.0 && val2 < 18446744073709551616.0 && val1 >= 0 && val2 >= 0) {
				result = uint64_t(val1) & uint64_t(val2);
			}else{
				ahand.report(33);
			}
			break;
		case opBitOr:
			if (val1 < 18446744073709551616.0 && val2 < 18446744073709551616.0 && val1 >= 0 && val2 >= 0){
				result = uint64_t(val1) | uint64_t(val2);
			}else{
				ahand.report(33);
			}
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

		if (std::fetestexcept(FE_DIVBYZERO)) {
			ahand.report(0);
			return 0;
		}else if (std::fetestexcept(FE_INVALID)) {
			ahand.report(26);
			return 0;
		}else if (std::fetestexcept(FE_OVERFLOW)) {
			ahand.report(27);
			return 0;
		}else if (std::fetestexcept(FE_UNDERFLOW)) {
			ahand.report(28);
			return 0;
		}
		return result;		
	}
}