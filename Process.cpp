#include "Process.h"

Process::Process()
{
	std::string mnames[] = {"def", "if", "else", "while", "goto", "exit"};
	lineType mtypes[] = { defLine, ifLine, elseLine, whileLine, gotoLine, exitLine };
	for (int i = 0; i < 5; i++) match.insert(std::make_pair(mnames[i], mtypes[i]));
}

void Process::Preptext(std::string text)
{
	std::string result;
	std::string pic;
	bool nfirst = false;
	bool nlast = true;
	int retcnt = 0;
	for (int i = 0; i < text.length(); i++) {
		pic = text.substr(i, 1);
		if (pic != " " && pic != "\t") nfirst = true;
		if (pic == "#") nlast = false;
		if (pic == "\n" || pic == "\f" || pic == "\r") {
			retcnt++;
			if (retcnt == 1) result += "\n";
		}else{
			if (nfirst && nlast) result += pic;
			retcnt = 0;
		}
	}
	varscan(result);
}

void Process::varscan(std::string text)
{
	int linenum = 0;
	std::string pic;
	int ipic;
	bool ldef = false;
	bool lgt = false;
	std::string expdef;
	std::string expvar;
	std::string cmpprt;
	std::string whole;
	Line aline = newLine();
	int size = 0;
	bool paropen = false;
	bool parclose = false;
	lineType holdWord = emptyLine;
	double asig = 0;
	bool decimal = false;
	bool neg = false;
	int dplas = 0;
	bool canneg = false;
	int whocnt = 0;
	int parcnt = 0;
	std::string insparen = "";
	bool setval = false;
	for (int i = 0; i < text.length(); i++) {
		pic = text.substr(i, 1);
		if (pic != "\n") {
			whole += pic;
			whocnt++;
			if (parcnt != 0) insparen += pic;
		}else{
			int non = 0;
		}
		ipic = meth.asc(pic);
		
		if (pic == " ") {
			if (ldef) {
				canneg = false;

			}
			else {
				
			}
			cmpprt = "";
		}
		else if (pic == ":") {
			if (expdef != "") holdWord = labelLine;
		}
		else if (pic == "(") {
			paropen = true;
			if (ldef) size = 0;			
			parcnt++;
		}
		else if (pic == ")") {
			parclose = true;
			parcnt--;
		}
		else if(pic == "." || pic == "-" || (ipic > 47 && ipic < 58)) {
			if (ldef) {
				if (paropen && ipic > 47 && ipic < 58) {
					size *= 10;
					size += ipic - 48;
				}
				else{
					if (pic == ".") {
						decimal = true;
					}
					else if (pic == "-") {
						canneg = true;
					}else{
						if (decimal) {
							dplas++;
							asig += pow(10, -dplas) * (ipic - 48);
						}else{
							asig *= 10;
							asig += ipic - 48;
						}
					}
				}
			}else {

			}
		}
		else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
			if (holdWord == emptyLine) holdWord = funLine;
			int thisend;
			int befend;
			if (!ldef && !lgt) {
				expdef += pic;
				if (match.contains(expdef)) {
					ldef = false;
					holdWord = match[expdef];
					aline.type = holdWord;
					switch (match[expdef]) {

					case defLine:
						ldef = true;
						break;
					case ifLine:
						aline.line1 = findend(text, i, linenum) + 1;
						break;
					case elseLine:
						thisend = findend(text, i, linenum) + 1;
						befend = findline(linenum);
						lines.at(befend).line2 = thisend;
						break;
					case whileLine:
						aline.line1 = findend(text, i, linenum) + 1;
						break;
					case gotoLine:
						lgt = true;
						break;
					}

				}
			}
			else {
				expvar += pic;
			}

		}
		else if (pic == "{") {
			vars.IncScope();
		}
		else if (pic == "}") {
			vars.DecScope();
		}
		else if (pic == "\n") {			
			linenum++;
			switch (holdWord) {
			case funLine:
				aline.op1 = maker.createTree(whole.substr(0, whole.length()));
				break;
			case varLine:
				aline.op2 = maker.createTree(whole.substr(0, whole.length()));
				break;
			case defLine:
				if (size == 0) size = 1;
				vars.Create(expvar, asig ,setval ,size);
				if (setval) size = -1;
				aline.line1 == size;
				aline.val == asig;
				aline.labname = expvar;
				break;
			case ifLine:
				insparen = insparen.substr(0, insparen.length() - 1);
				aline.op1 = maker.createTree(insparen);
				
				break;
			case elseLine:
				
				break;
			case whileLine:
				insparen = insparen.substr(0, insparen.length() - 1);
				aline.op1 = maker.createTree(insparen);				
				break;
			case gotoLine:
				aline.labname = expdef;
				break;
			case labelLine:
				aline.labname = expdef;
				aline.type = labelLine;
				break;
			}
			aline.type = holdWord;
			lines.push_back(aline);
			aline = newLine();
			ldef = false;
			expdef = "";
			expvar = "";
			holdWord = emptyLine;
			whole = "";
			decimal = false;
			neg = false;
			dplas = 0;
			canneg = false;
			whocnt = 0;
			insparen = "";
			parcnt = 0;
			size = 0;
			asig = 0;
			setval = false;
		}else{
			cmpprt += pic;
			if (holdWord == defLine && pic == "=") setval = true;			
			if (cmpprt.length() < 3) {
				for (int i = 0; i < amap.asdOps.length() / 2; i++) {
					std::string cmp = amap.asdOps.substr(i * 2, 2);
					//if (cmp.substr(1, 1) == " ") cmp = cmp.substr(0, 1);
					if (cmp == cmpprt && holdWord != defLine) {
						holdWord = varLine;
						if (cmp == "=") {
							aline.op1 = maker.createTree(whole.substr(0, whocnt - 2));
						}else{
							aline.op1 = maker.createTree(whole.substr(0, whocnt - 3));
						}
						whole = "";
						aline.equtype = amap.convertedTokens[cmp];
					}
				}
			}
		}
	}
	int labcnt = 0;
	for (int i = 0; i < lines.size(); i++) {
		Line curlin = lines.at(i);
		if (curlin.type == labelLine) {
			for (int j = 0; j < lines.size(); j++) {
				Line seclin = lines.at(j);
				if (i != j && curlin.labname == seclin.labname) {
					if (seclin.type == labelLine) {
						//report error
					}else{
						seclin.line1 = i;
					}					
				}
			}
		}
		else if (curlin.type == whileLine) {
			int whend = curlin.line1 - 1;
			if (whend < lines.size()) {
				lines.at(whend).whilend = true;
				lines.at(whend).whret = i;
			}
		}
		else if (curlin.type == ifLine && curlin.line2 > -1) {
			int whend = curlin.line1;
			if (whend < lines.size()) {
				lines.at(whend).ifend = true;
				lines.at(whend).whret = curlin.line2;
			}
		}
		
	}
	vars.clear();
	Run();
}

void Process::Run()
{
	int linenum = 0;
	Line current;
	double val;
	tokenName tok;
	bool hasval;
	while (linenum < lines.size()) {
		current = lines.at(linenum);
		if (current.ifend || current.whilend) {
			linenum = current.whret;
		}
		else {
			switch (current.type)
			{
			case defLine:
				hasval = current.line1 < 0;
				if (current.line1 < 0) current.line1 = 0;
				vars.Create(current.labname, current.val, hasval, current.line1);
				break;
			case varLine:
				val = current.op2.evaluate();
				tok = current.equtype;
				current.op1.assign(tok, val);
				break;
			case funLine:
				current.op1.evaluate();
				break;
			case ifLine:
				val = current.op1.evaluate();
				if (val == 0) linenum = current.line1;
				break;
			case whileLine:
				val = current.op1.evaluate();
				if (val == 0) linenum = current.line1;
				break;

			case gotoLine:
				linenum = current.line1;
				break;
			case exitLine:
				return;
			}
		}
		if (current.type != gotoLine && !(current.ifend || current.whilend)) linenum++;
	}
	int non = 0;
}

Line Process::newLine()
{
	Line ret;
	ret.type = emptyLine;
	ret.labname = "";
	ret.line1 = -1;
	ret.line2 = -1;
	ret.whret = -1;
	ret.whilend = false;
	ret.ifend = false;
	return ret;
}

int Process::findline(int linenum)
{
	int ret = -1;
	if (linenum < lines.size() + 1) {
		for (ret = linenum - 1; ret > -1; ret--) {
			if (lines.at(ret).type == ifLine && lines.at(ret).line1 == linenum) {
				break;

			}
		}
	}else {
		int non = 0;
	}
	//report error
	return ret;
}

int Process::findend(std::string text, int loc, int linenum)
{
	std::string pic;
	int bracnt = 0;
	
	for (int i = loc; i < text.length(); i++) {
		pic = text.substr(i, 1);
		if (pic == "{") {
			bracnt++;
		}else if (pic == "}") {
			bracnt--;
			if (bracnt == 0) return linenum;
		}else if (pic == "\n") {			
			linenum++;			
		}
	}
	return 0;
}
