#include "ErrorHandler.h"

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
	errors.push_back(info);
	if (reponce) {
		handler(errors);
		errors.clear();
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
	}
	return "Unknown error";
}
