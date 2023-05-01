#pragma once
#include <functional>
#include <vector>
#include <string>

	struct errInfo {
		int errType, errLine;
		std::string errMes, lineText;
	};
namespace AndyInt {
	class ErrorHandler
	{
	public:
		void setHandler(std::function<void(std::vector<errInfo>)> ahan);
		void report(int errNum);
		void sendErrors();
		bool beenReported = false;
		int curline = 0;
		std::string line;
		bool reponce = false;
	private:
		std::string getMessage(int err);
		std::vector<errInfo> errors;
		std::function<void(std::vector<errInfo>)> handler;
	};
}