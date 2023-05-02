#include "ErrorHandler.h"
namespace AndyInt {
	void ErrorHandler::setHandler(std::function<void(std::vector<errInfo>)> ahan) {
		handler = ahan;
	}

	void ErrorHandler::report(int errNum) {

		beenReported = true;
		errInfo info;
		info.errType = errNum;
		info.errMes = getMessage(errNum);
		info.errLine = curline;
		info.lineText = line;
		bool differ = true;
		for (int i = errors.size() - 1; i > -1; i--) {
			if (curline != errors.at(i).errLine) break;
			if (errNum == errors.at(i).errType) differ = false;
		}
		if (differ) {
			errors.push_back(info);
			if (reponce) {
				handler(errors);
				errors.clear();
			}
		}
	}

	void ErrorHandler::sendErrors()
	{
		if (errors.size() > 0) {
			handler(errors);
			errors.clear();
		}
	}

	std::string ErrorHandler::getMessage(int err)
	{
		switch (err) {
		case 0:
			return "Math error.";
		case 1:
			return "Could not find end of block.";
		case 2:
			return "Could not find if block.";
		case 3:
			return "Expected arguments.";
		case 4:
			return "Uneven parenthesis.";
		case 5:
			return "Unexpected tokens.";
		case 6:
			return "Missing a value type.";
		case 7:
			return "Variable not defined.";
		case 8:
			return "Variable out of scope.";
		case 9:
			return "Variable already defined.";
		case 10:
			return "Array out of bounds.";
		case 11:
			return "Invalid variable reference.";
		case 12:
			return "Only one decimal place can be assigned.";
		case 13:
			return "A variable is not indexed by a negative number.";
		case 14:
			return "Missing identifyer.";
		case 15:
			return "Duplicaate label.";
		case 16:
			return "Duplicate decimal point.";
		case 17:
			return "Word e is reserved for scientific notation.";
		case 18:
			return "Overflow detected in number.";
		case 19:
			return "Non direct assignment with undefined variable.";
		case 20:
			return "Only a variable can be assigned.";
		case 21:
			return "Nothing to assgin to.";
		case 22:
			return "Invalid structure.";
		case 23:
			return "Cannot get undefined variable.";
		case 24:
			return "Use of reserved word.";
		case 25:
			return "More than one identifyer without operator.";
		}
		return "Unknown error";
	}
}