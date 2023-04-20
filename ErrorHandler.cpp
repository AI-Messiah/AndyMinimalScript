#include "ErrorHandler.h"

void ErrorHandler::setHandler(std::function<void(errInfo)> ahan) {
	handler = ahan;
}

void ErrorHandler::report(int errNum) {

	beenReported = true;
	errInfo info;
	info.errType = errNum;
	//info.errMes = messages[errNum - 1];
	info.errLine = curline;
	info.lineText = line;
	handler(info);
}