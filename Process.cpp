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
			nfirst = false;
			nlast = true;
		}else{
			if (nfirst && nlast) result += pic;
			retcnt = 0;
		}
	}
	int pcnt = 0;
	bool hasret = false;
	bool closdet = false;
	while (pcnt < result.length()) {
		pic = result.substr(pcnt, 1);
		if (pic == "{" && !hasret) {
			result = meth.insertRet(result, pcnt);
			pcnt++;
		}
		hasret = (pic == "\n");
		if (closdet && !hasret) {
			result = meth.insertRet(result, pcnt);
			
		}
		closdet = (pic == "}");
		pcnt++;
	}
	
	resetlbl:
	charType past = noChar;
	charType pres = noChar;
	bool spa = false;
	bool pspa = false;
	
	int ipic;

	int iaft;
	int ibef;
	std::string aft;
	std::string bef;
	pcnt = 0;
	while (pcnt < result.length()) {
		pic = result.substr(pcnt, 1);
		ipic = meth.asc(pic);
		aft = "";
		if (pcnt < result.length() - 1) aft = result.substr(pcnt+ 1, 1);
		iaft = meth.asc(aft);
		bef = "";
		if (pcnt > 0) bef = result.substr(pcnt - 1, 1);
		ibef = meth.asc(bef);
		spa = (pic == " ");
		if (pic == "." || (ipic > 47 && ipic < 58)) {
			pres = numChar;
		}
		else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
			if (pic == "e") {
				if ((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (ibef > 64 && ibef < 91) || (ibef > 96 && ibef < 123)) {
					pres = textChar;
				}
				else {
					if ((iaft > 47 && iaft < 58) || aft == "-") {
						pres = numChar;
					}
					else {
						pres = operChar;
					}
				}
			}
			else {
				pres = textChar;
			}
		}else if (pic == "-") {
			if ((iaft > 64 && iaft < 91) || (iaft > 96 && iaft < 123) || (iaft > 47 && iaft < 58) || aft == ".") {
				if (iaft > 60) {
					pres = textChar;
				}else{
					pres = numChar;
				}
			}else{
				pres = operChar;			
			}
		}else {
			pres = noChar;
			for (int i = 0; i < opers.length(); i++) if (pic == opers.substr(i, 1)) pres = operChar;
		}
		if (past != noChar && pres != noChar && past != pres && !pspa) {
			result = meth.insertSpa(result, pcnt);
			goto resetlbl;
		}
		pspa = spa;
		past = pres;
		pcnt++;
	}
	std::ofstream out("CScript.txt");
	out << result;
	out.close();

	convert(result);
	
	
}

void Process::convert(std::string text)
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
	std::string linetext = "";
	int pcnt = 0;
	bool cont = true;
	int lastpos = 0;
	std::string lastwhole = "";
	while (pcnt < text.length()) {
		cont = true;
		linetext = "";
		while ((text.substr(pcnt, 1) != "\n") && pcnt < text.length()) {
			linetext += text.substr(pcnt, 1);
			pcnt++;
			
		}
		pcnt++;
		AndyInt::ahand.line = linetext;
		AndyInt::ahand.curline = linenum + 1;
		textlines.push_back(linetext);
		for (int i = 0; i < linetext.length(); i++) {
			pic = linetext.substr(i, 1);
			
			whole += pic;
			whocnt++;
			if (parcnt != 0) insparen += pic;			
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
			else if (pic == "." || pic == "-" || (ipic > 47 && ipic < 58)) {
				if (ldef) {
					if (paropen && ipic > 47 && ipic < 58) {
						size *= 10;
						size += ipic - 48;
					}
					else {
						if (pic == ".") {
							decimal = true;
						}
						else if (pic == "-") {
							canneg = true;
						}
						else {
							if (decimal) {
								dplas++;
								asig += pow(10, -dplas) * (ipic - 48);
							}
							else {
								asig *= 10;
								asig += ipic - 48;
							}
						}
					}
				}
				else {

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
							aline.line1 = findend(text, lastpos, linenum) + 1;
							break;
						case elseLine:
							thisend = findend(text, lastpos, linenum) + 1;
							befend = findline(linenum);
							lines.at(befend).line2 = thisend;
							break;
						case whileLine:
							aline.line1 = findend(text, lastpos, linenum) + 1;
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
				AndyInt::vars.IncScope();
			}
			else if (pic == "}") {
				AndyInt::vars.DecScope();
			}
			else if (pic == "\n") {
				
			}
			else {
				
				if (holdWord == defLine && pic == "=") setval = true;				
				if (holdWord == funLine) {
					for (int j = 0; j < amap.asdOps.length() / 2; j++) {
						std::string cmp = amap.asdOps.substr(j * 2, 2);
							
						std::string pic1 = "";
						if (i < linetext.length() - 1) pic1 = linetext.substr(i + 1,1);						
						if (cmp == pic + pic1 && holdWord != defLine) {
							holdWord = varLine;
							aline.op1 = maker.createTree(whole.substr(0, whocnt - 2));
							res.Check(whole.substr(0, whocnt - 2));
							lastwhole = whole;
							whole = "";
							aline.equtype = amap.convertedTokens[cmp];
						}						
					}
				}
				
			}
		}
		linenum++;
		
		switch (holdWord) {
		case funLine:
			res.Check(whole);
			aline.op1 = maker.createTree(whole.substr(0, whole.length()));
			break;
		case varLine:
			//aline.op1 = maker.createTree(lastwhole.substr(0, lastwhole.length() - 1));
			res.Check(whole);
			aline.op2 = maker.createTree(whole.substr(0, whole.length()));
			break;
		case defLine:
			if (size == 0) size = 1;
			AndyInt::vars.Create(expvar, asig, setval, size);
			if (setval) size = -1;
			aline.line1 = size;
			aline.val = asig;
			aline.labname = expvar;
			res.Check(expvar);
			break;
		case ifLine:
			res.Check(insparen);
			insparen = insparen.substr(0, insparen.length() - 1);
			aline.op1 = maker.createTree(insparen);

			break;
		case elseLine:

			break;
		case whileLine:
			res.Check(insparen);
			insparen = insparen.substr(0, insparen.length() - 1);
			aline.op1 = maker.createTree(insparen);
			break;
		case gotoLine:
			aline.labname = expdef;
			break;
		case labelLine:
			res.Check(expdef);
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
		lastpos = pcnt;
	}
	int labcnt = 0;
	for (int i = 0; i < lines.size(); i++) {
		Line curlin = lines.at(i);
		if (curlin.type == labelLine) {
			for (int j = 0; j < lines.size(); j++) {
				Line seclin = lines.at(j);
				if (i != j && curlin.labname == seclin.labname) {
					if (seclin.type == labelLine) {
						AndyInt::ahand.report(15);
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
	AndyInt::vars.clear();
	AndyInt::ahand.sendErrors();
	AndyInt::ahand.reponce = true;
	Run();
}

void Process::shutDown()
{
	std::mutex mut;
	mut.lock();
	contrun = false;
	mut.unlock();
}

void Process::Run()
{	
	int linenum = 0;
	Line current;
	double val;
	AndyInt::tokenName tok;
	bool hasval;
	bool skip = false;
	while (linenum < lines.size() && contrun) {
		if (AndyInt::ahand.beenReported) return;
		AndyInt::ahand.line = textlines.at(linenum);
		AndyInt::ahand.curline = linenum + 1;
		current = lines.at(linenum);
		if (current.ifend || current.whilend) {
			linenum = current.whret;
		}
		else {
			switch (current.type)
			{
			case defLine:
				hasval = current.line1 < 0;
				if (current.line1 < 1) current.line1 = 1;
				AndyInt::vars.Create(current.labname, current.val, hasval, current.line1);
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
				skip = (val == 0);
				break;

			case gotoLine:
				linenum = current.line1;
				break;
			case exitLine:
				return;
			}
		}
		if (current.type != gotoLine && !(current.type == whileLine && skip) && !(current.ifend || current.whilend)) linenum++;
	}
	
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
		for (ret = linenum - 1; ret > 0; ret--) {
			if (lines.at(ret).type == ifLine && lines.at(ret).line1 == linenum) {
				break;

			}
		}
	}
	if (ret < 0) {
		ret = 0;
		AndyInt::ahand.report(2);
	}
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
	AndyInt::ahand.report(1);
	return 0;
}
