#pragma once
#include "ascii.h"
#include "TreeMaker.h"
#include "ResCheck.h"
#include <mutex>

enum charType {
	noChar,
	textChar,
	numChar,
	operChar
};

enum lineType {
	emptyLine,
	varLine,
	funLine,
	defLine,
	ifLine,
	elseLine,
	whileLine,
	gotoLine,
	labelLine,
	exitLine
};

struct Line {
	double val;
	std::string labname;
	lineType type;
	AndyInt::tokenName equtype;
	AndyInt::OpNode op1, op2;
	int line1, line2, whret;
	bool whilend;
	bool ifend;
};

class Process
{
public:
	Process();
	void Preptext(std::string text);
	void convert(std::string text);
	void shutDown();
	
	AndyInt::TreeMaker maker;
private:
	
	void Run();
	Line newLine();
	int findline(int linenum);
	int findend(std::string text, int loc, int linenum);
	bool contrun = true;
	std::map<std::string, lineType> match;
	std::string opers = "^*/\\+&|!=<>";
	AndyInt::ResCheck res;
	AndyInt::Maps amap;
	AndyInt::strmeth meth;
	std::vector<Line> lines;
	std::vector<std::string> textlines;
};

