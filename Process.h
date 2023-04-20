#pragma once
#include "ascii.h"
#include "TreeMaker.h"

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
	tokenName equtype;
	OpNode op1, op2;
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
	std::map<std::string, lineType> match;
	TreeMaker maker;
private:
	void Run();
	Line newLine();
	int findline(int linenum);
	int findend(std::string text, int loc, int linenum);
	
	Maps amap;
	strmeth meth;
	std::vector<Line> lines;
};

