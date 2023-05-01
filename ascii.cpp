#include "ascii.h"

int strmeth::asc(std::string inv)
{
	if (inv.length() > 0) {
		return (int)inv.substr(0, 1).c_str()[0];
	}else{
		return 0;
	}
}

std::string strmeth::RepText(std::string text, std::string rep, int frm, int to)
{
	std::string ret = "";
	if (frm > -1 && to > 0 && frm < text.length()) {
		if (frm > 0) ret = text.substr(0, frm);
		ret += rep;
		if (to < text.length() - 1) ret += text.substr(to, text.length() - to);
	}
	return ret;
}

std::string strmeth::emplace(std::string text, int frm, int to)
{
	std::string ret = "";
	if (frm > -1 && to > 0 && frm < text.length()) {
		if (frm > 0) ret = text.substr(0, frm);
		ret += "#";
		if (to < text.length() - 1) ret += text.substr(to, text.length() - to);
	}
	return ret;
}

std::string strmeth::insertRet(std::string text, int place)
{
	std::string ret = "";
	if (place < text.length()) {
		ret = text.substr(0, place);
		ret += "\n";
		ret += text.substr(place, text.length() - place + 1);
	}
	return ret;
}

std::string strmeth::insertSpa(std::string text, int place)
{
	std::string ret = "";
	if (place < text.length()) {
		ret = text.substr(0, place);
		ret += " ";
		ret += text.substr(place, text.length() - place + 1);
	}
	return ret;
}
