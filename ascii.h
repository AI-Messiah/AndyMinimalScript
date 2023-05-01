#pragma once

#include <string>
namespace AndyInt {
	class strmeth {
	public:
		int asc(std::string inv);
		std::string RepText(std::string text, std::string rep, int frm, int to);
		std::string emplace(std::string text, int frm, int to);
		std::string insertRet(std::string text, int place);
		std::string insertSpa(std::string text, int place);
	};
}