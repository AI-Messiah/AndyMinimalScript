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
	}
	return "Unknown error";
}
