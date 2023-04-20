#include "TreeMaker.h"

OpNode TreeMaker::createTree(std::string text)
{
    std::vector<OpNode> nodes;
	OpNode temp;
	if (text == "") {
		//report error
		return temp;
	}
	double num1;
	double num2;
	bool hasnum1;
	bool hasnum2;
	bool canneg;
	bool neg1;
	bool neg2;
	bool decimal1;
	bool decimal2;
	bool isnode1;
	bool isnode2;
	bool nfset;
	bool nfset1;
	int dplas1;
	int dplas2;
	int nodref;
	bool cntch;
	std::string var1;
	std::string var2;
	int cntprt;
	std::string pic;
	int ipic;
	int frm, frm1, to;
	int npl;
	bool incon;
	tokenName curtok;
	std::string temsym;
	bool fexpr;
	int fundet;
	int nodepl1, nodepl2;
	valType vtype1, vtype2;	
	while (hasPeren(text)) {
	resetlbl:
		fundet = -1;
		cntprt = 0;
		frm = 0;
		incon = false;
		var1 = "";
		cntch = true;
		while (cntprt < text.length() && text.substr(cntprt, 1) != ")") {
			if (text.substr(cntprt, 1) == "(") {
				frm = cntprt;
				cntch = false;
			}
			pic = text.substr(cntprt, 1);
			ipic = meth.asc(pic);
			if (pic == " ") {
				incon = true;
				if (cntch) {
					var1 = "";
					fundet = -1;
				}
			}
			else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
				incon = false;
				if (cntch) {
					var1 += pic;
					for (int i = 0; i < 16; i++) if (var1 == trans.oFunNames[i]){
						fundet = i;
						break;						
					}
					for (int i = 0; i < trans.funNames.size(); i++) if (var1 == trans.funNames.at(i)) {
						fundet = i + 16;
						break;
					}
				}
			}
			cntprt++;
		}                                                                    
		temp = createTree(text.substr(frm + 1, cntprt - frm - 1));
		if (fundet > 15) {			
			temp = combfun(temp, fundet - 16, false);
			text = meth.emplace(text, frm, cntprt);
			npl = countNodes(text, frm);
			nodes.insert(nodes.begin() + npl, temp);
		}
		else {
			
			if (temp.Src.size() < 2 && temp.Src.at(0) == valValue) {
				if (var1 != "") {
					//if (fundet > -1) 
					if (fundet > -1) {
						if (fundet < 14) {
							double num = temp.Val.at(0);
							num = trans.calFun(fundet, num);
							std::string rep = fromNum(num);
							text = meth.RepText(text, rep, frm, cntprt);
						}
						
						else {
							//report error
						}
					}
					else {
						temp.Src.at(0) = valFixed;
						text = meth.emplace(text, frm, cntprt);
						npl = countNodes(text, frm);
						nodes.insert(nodes.begin() + npl, temp);
					}
				}
				else {
					double num = temp.Val.at(0);

					std::string rep = fromNum(num);
					text = meth.RepText(text, rep, frm, cntprt);
				}
			}
			else {
				if (var1 != "") {

					temp = combvar(temp, var1);
					if (fundet > -1) {
						temp.Src.at(0) = valInternal;
					}
					else {
						temp.Src.at(0) = valIndexed;
					}
					text = meth.emplace(text, frm, cntprt);
					npl = countNodes(text, frm);
					nodes.insert(nodes.begin() + npl, temp);
				}
				else {
					text = meth.emplace(text, frm, cntprt);
					npl = countNodes(text, frm);
					nodes.insert(nodes.begin() + npl, temp);
				}
			}
		}
	}
	for (int pri = 0;pri < 9; pri++) {
		for (int sid = 0; sid < 2; sid++) {
		resetlbl1:
			cntprt = 0;
			curtok = opNone;
			fexpr = true;
			var1 = "";
			var2 = "";
			neg1 = false;
			neg2 = false;
			canneg = false;
			num1 = 0;
			num2 = 0;
			decimal1 = false;
			decimal2 = false;
			isnode1 = false;
			isnode2 = false;
			nodref = -1;
			nfset = true;
			nfset1 = false;
			dplas1 = 0;
			dplas2 = 0;
			nodref = 0;
			hasnum1 = false;
			hasnum2 = false;
			frm1 = -1;

			temp.clear();

			while (cntprt < text.length()) {
				pic = text.substr(cntprt, 1);
				ipic = meth.asc(pic);

				if (pic == " ") {
					canneg = false;
				}
				else if (pic == "." || pic == "-" || (ipic > 47 && ipic < 58)) {

					if (pic == "-") {
						canneg = true;
					}
					else if (pic == ".") {
						to = cntprt;
						if (nfset) {
							frm = cntprt;
							if (canneg) frm--;
							nfset = false;
						}
						if (nfset1) {
							frm1 = cntprt;
							if (canneg) frm1--;
							nfset1 = false;
						}
						if (fexpr) {
							if (canneg) neg1 = true;
							if (decimal1) {
								//report error
							}
							decimal1 = true;
							hasnum1 = true;
						}
						else {
							if (canneg) neg2 = true;
							if (decimal2) {
								//report error
							}
							decimal2 = true;
							hasnum2 = true;
						}
					}
					else {
						to = cntprt;
						if (nfset) {
							frm = cntprt;
							if (canneg) frm--;
							nfset = false;
						}
						if (nfset1) {
							frm1 = cntprt;
							if (canneg) frm1--;
							nfset1 = false;
						}
						if (fexpr) {
							if (canneg) neg1 = true;
							hasnum1 = true;
							if (decimal1) {
								dplas1++;
								num1 += pow(10, -dplas1) * (ipic - 48);
							}
							else {
								num1 *= 10;
								num1 += ipic - 48;
							}
						}
						else {
							if (canneg) neg2 = true;
							hasnum2 = true;
							if (decimal2) {
								dplas2++;
								num2 += pow(10, -dplas2) * (ipic - 48);
							}
							else {
								num2 *= 10;
								num2 += ipic - 48;
							}
						}
					}

				}
				else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
					to = cntprt;
					if (nfset) {
						frm = cntprt;
						nfset = false;
					}
					if (nfset1) {
						frm1 = cntprt;
						nfset1 = false;
					}
					if (fexpr) {
						var1 += pic;
					}
					else {
						var2 += pic;
					}
				}
				else if (pic == "#") {
					to = cntprt;
					if (nfset) {
						frm = cntprt;
						nfset = false;
					}
					if (nfset1) {
						frm1 = cntprt;
						nfset1 = false;
					}
					if (fexpr) {
						isnode1 = true;
						nodepl1 = countNodes(text, cntprt);
					}
					else {
						isnode2 = true;
						nodepl2 = countNodes(text, cntprt);
					}
					nodref = countNodes(text, cntprt);
				}
				else if (pic == ",") {
					fexpr = true;
					var1 = "";
					var2 = "";
					neg1 = false;
					neg2 = false;
					canneg = false;
					num1 = 0;
					num2 = 0;
					decimal1 = false;
					decimal2 = false;
					isnode1 = false;
					isnode2 = false;
					nodref = -1;
					nfset = true;
					nfset1 = false;
					dplas1 = 0;
					dplas2 = 0;
					nodref = 0;
					hasnum1 = false;
					hasnum2 = false;
				}
				else {
					if (curtok != opNone) {
						if (neg1) num1 *= -1;
						if (neg2) num2 *= -1;
						if (hasnum1 && hasnum2) {
							std::string rep = fromNum(calc.Calculate(num1, num2, curtok));
							text = meth.RepText(text, rep, frm, to + 1);
							goto resetlbl1;
						}
						else if (sid == 1){
							if (hasnum1) {
								vtype1 = typeNum;
							}
							else if (var1 != "") {
								vtype1 = typeVar;
							}
							else if (isnode1) {
								if ((nodes.at(nodepl1).Src.at(0) == valInternal && nodes.at(nodepl1).Src.size() < 2) || (nodes.at(nodepl1).Src.at(0) == valExternal && nodes.at(nodepl1).Src.size() < 2)) {
									vtype1 = typeFunc;
								}
								else {
									vtype1 = typeNode;
								}
							}
							else {
								//report error
							}

							if (hasnum2) {
								vtype2 = typeNum;
							}
							else if (var2 != "") {
								vtype2 = typeVar;
							}
							else if (isnode2) {
								if ((nodes.at(nodepl2).Src.at(0) == valInternal && nodes.at(nodepl2).Src.size() < 2) || (nodes.at(nodepl2).Src.at(0) == valExternal && nodes.at(nodepl2).Src.size() < 2)) {
									vtype2 = typeFunc;
								}
								else {
									vtype2 = typeNode;
								}
							}
							else {
								//report error
							}

							nodref = countNodes(text, cntprt);
							switch (vtype1) {
							case typeNum:
								switch (vtype2) {
								case typeVar:
									temp = numwithvar(num1, var2, curtok);
									nodes.insert(nodes.begin() + nodref, temp);
									break;
								case typeFunc:
									temp = numwithfunc(num1, nodes.at(nodref), curtok);
									nodes.at(nodref) = temp;
									break;
								case typeNode:
									temp = numwithnode(num1, nodes.at(nodref), curtok);
									nodes.at(nodref) = temp;
									break;
								}
								break;
							case typeVar:
								switch (vtype2) {
								case typeNum:
									temp = varwithnum(var1, num2, curtok);
									nodes.insert(nodes.begin() + nodref, temp);
									break;
								case typeVar:
									temp = varwithvar(var1, var2, curtok);
									nodes.insert(nodes.begin() + nodref, temp);
									break;
								case typeFunc:
									temp = varwithfunc(var1, nodes.at(nodref), curtok);
									nodes.at(nodref) = temp;
									break;
								case typeNode:
									temp = varwithnode(var1, nodes.at(nodref), curtok);
									nodes.at(nodref) = temp;
									break;
								}
								break;
							case typeFunc:
								switch (vtype2) {
								case typeNum:
									temp = funcwithval(nodes.at(nodref), num2, curtok);
									nodes.at(nodref) = temp;
									break;
								case typeVar:
									temp = funcwithvar(nodes.at(nodref), var2, curtok);
									nodes.at(nodref) = temp;
									break;
								case typeFunc:
									temp = funcwithfunc(nodes.at(nodref - 1), nodes.at(nodref), curtok);
									nodes.at(nodref - 1) = temp;
									nodes.erase(nodes.begin() + nodref);
									break;
								case typeNode:
									temp = funcwithnode(nodes.at(nodref - 1), nodes.at(nodref), curtok);
									nodes.at(nodref - 1) = temp;
									nodes.erase(nodes.begin() + nodref);
									break;
								}
								break;
							case typeNode:
								switch (vtype2) {
								case typeNum:
									temp = nodewithnum(nodes.at(nodref), num2, curtok);
									nodes.at(nodref) = temp;
									//to = cntprt + 2;
									break;
								case typeVar:
									temp = nodewithvar(nodes.at(nodref), var2, curtok);
									nodes.at(nodref) = temp;
									break;
								case typeFunc:
									temp = nodewithfunc(nodes.at(nodref - 1), nodes.at(nodref), curtok);
									nodes.at(nodref - 1) = temp;
									nodes.erase(nodes.begin() + nodref);
									break;
								case typeNode:
									temp = nodewithnode(nodes.at(nodref - 1), nodes.at(nodref), curtok);
									nodes.at(nodref - 1) = temp;
									nodes.erase(nodes.begin() + nodref);
									break;
								}
								break;
							}
							text = meth.emplace(text, frm, to + 1);
							goto resetlbl1;
						}
					}
					else {
						for (int i = 0; i < int(smp.mathOps.length() / 2); i++) {
							if (smp.priority[i] == pri) {
								temsym = smp.mathOps.substr(i * 2, 2);
								if (temsym.substr(1, 1) == " ") temsym = temsym.substr(0, 1);
								if (temsym.length() == 1) {
									if (temsym == pic) {
										curtok = smp.convertedTokens[pic];
									}
								}
								else {
									if (cntprt > 0) {
										std::string pic1 = "";
										if (cntprt < text.length() - 1) pic1 = text.substr(cntprt + 1, 1);
										if (pic1 + pic == temsym) {
											curtok = smp.convertedTokens[pic + pic1];
											cntprt++;
										}
									}
								}
							}
						}


						nfset1 = true;
						if (!fexpr && curtok == opNone) {
							frm = frm1;
							isnode1 = isnode2;
							isnode2 = false;
							var1 = var2;
							var2 = "";
							num1 = num2;
							num2 = 0;
							hasnum1 = hasnum2;
							hasnum2 = false;
						}
						decimal1 = false;
						decimal2 = false;
						dplas1 = 0;
						dplas2 = 0;
						fexpr = false;

					}
				}

				cntprt++;
			}
			if (curtok != opNone) {
				if (neg1) num1 *= -1;
				if (neg2) num2 *= -1;
				if (hasnum1 && hasnum2) {
					std::string rep = fromNum(calc.Calculate(num1, num2, curtok));
					text = meth.RepText(text, rep, frm, cntprt - 1);
					goto resetlbl1;
				}
				else if (sid == 1){
					if (hasnum1) {
						vtype1 = typeNum;
					}
					else if (var1 != "") {
						vtype1 = typeVar;
					}
					else if (isnode1) {
						if ((nodes.at(nodepl1).Src.at(0) == valInternal && nodes.at(nodepl1).Src.size() < 2) || (nodes.at(nodepl1).Src.at(0) == valExternal && nodes.at(nodepl1).Src.size() < 2)) {
							vtype1 = typeFunc;
						}
						else {
							vtype1 = typeNode;
						}
					}
					else {
						//report error
					}

					if (hasnum2) {
						vtype2 = typeNum;
					}
					else if (var2 != "") {
						vtype2 = typeVar;
					}
					else if (isnode2) {
						if ((nodes.at(nodepl2).Src.at(0) == valInternal && nodes.at(nodepl2).Src.size() < 2) || (nodes.at(nodepl2).Src.at(0) == valExternal && nodes.at(nodepl2).Src.size() < 2)) {
							vtype2 = typeFunc;
						}
						else {
							vtype2 = typeNode;
						}
					}
					else {
						//report error
					}

					nodref = countNodes(text, cntprt);
					switch (vtype1) {
					case typeNum:
						switch (vtype2) {
						case typeVar:
							temp = numwithvar(num1, var2, curtok);
							nodes.insert(nodes.begin() + nodref, temp);
							break;
						case typeFunc:
							temp = numwithfunc(num1, nodes.at(nodref), curtok);
							nodes.at(nodref) = temp;
							break;
						case typeNode:
							temp = numwithnode(num1, nodes.at(nodref), curtok);
							nodes.at(nodref) = temp;
							break;
						}
						break;
					case typeVar:
						switch (vtype2) {
						case typeNum:
							temp = varwithnum(var1, num2, curtok);
							nodes.insert(nodes.begin() + nodref, temp);
							break;
						case typeVar:
							temp = varwithvar(var1, var2, curtok);
							nodes.insert(nodes.begin() + nodref, temp);
							break;
						case typeFunc:
							temp = varwithfunc(var1, nodes.at(nodref), curtok);
							nodes.at(nodref) = temp;
							break;
						case typeNode:
							temp = varwithnode(var1, nodes.at(nodref), curtok);
							nodes.at(nodref) = temp;
							break;
						}
						break;
					case typeFunc:
						switch (vtype2) {
						case typeNum:
							temp = funcwithval(nodes.at(nodref), num2, curtok);
							nodes.at(nodref) = temp;
							break;
						case typeVar:
							temp = funcwithvar(nodes.at(nodref), var2, curtok);
							nodes.at(nodref) = temp;
							break;
						case typeFunc:
							temp = funcwithfunc(nodes.at(nodref - 1), nodes.at(nodref), curtok);
							nodes.at(nodref - 1) = temp;
							nodes.erase(nodes.begin() + nodref);
							break;
						case typeNode:
							temp = funcwithnode(nodes.at(nodref - 1), nodes.at(nodref), curtok);
							nodes.at(nodref - 1) = temp;
							nodes.erase(nodes.begin() + nodref);
							break;
						}
						break;
					case typeNode:
						switch (vtype2) {
						case typeNum:
							temp = nodewithnum(nodes.at(nodref), num2, curtok);
							nodes.at(nodref) = temp;
							//to = cntprt + 2;
							break;
						case typeVar:
							temp = nodewithvar(nodes.at(nodref), var2, curtok);
							nodes.at(nodref) = temp;
							break;
						case typeFunc:
							temp = nodewithfunc(nodes.at(nodref - 1), nodes.at(nodref), curtok);
							nodes.at(nodref - 1) = temp;
							nodes.erase(nodes.begin() + nodref);
							break;
						case typeNode:
							temp = nodewithnode(nodes.at(nodref - 1), nodes.at(nodref), curtok);
							nodes.at(nodref - 1) = temp;
							nodes.erase(nodes.begin() + nodref);
							break;
						}
						break;
					}
					
					text = meth.emplace(text, frm, to);
					goto resetlbl1;
				}
			}
		}
	}
	
	
	var1 = "";
	
	neg1 = false;
	
	canneg = false;
	num1 = 0;
	
	decimal1 = false;
	
	isnode1 = false;
	
	nodref = -1;
	
	dplas1 = 0;
	dplas2 = 0;
	nodref = 0;
	hasnum1 = false;
	bool isnode = false;
	frm1 = -1;
	temp.clear();
	OpNode ret;
	if (detComma(text)) {
		OpNode tpart;
		
		
		for (int i = 0; i < text.length(); i++) {
			pic = text.substr(i, 1);
			ipic = meth.asc(pic);
			if (pic == " ") {
				canneg = false;
			}
			else if (pic == "." || pic == "-" || (ipic > 47 && ipic < 58)) {
				if (pic == "-") {
					canneg = true;
				}
				else if (pic == ".") {
					if (canneg) neg1 = true;
					if (decimal1) {
						//report error
					}
					decimal1 = true;
					hasnum1 = true;
				}
				else {
					if (canneg) neg1 = true;
					hasnum1 = true;
					if (decimal1) {
						dplas1++;
						num1 += pow(10, -dplas1) * (ipic - 48);
					}
					else {
						num1 *= 10;
						num1 += ipic - 48;
					}
				}
			}
			else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
				var1 += pic;
			}
			else if (pic == "#") {
				int npl = countNodes(text, i);
				temp = nodes.at(npl);
				isnode = true;
			}
			else if (pic == ",") {
				if (hasnum1) {
					tpart.Src.push_back(valValue);
					tpart.Val.push_back(num1);
					
				}else{
					if (var1 != "") {
						tpart.Src.push_back(valVar);
						tpart.Var.push_back(vars.getRef(var1));
					}else{
						if (isnode) {
							tpart.Src.push_back(valNode);
							tpart.nodes.push_back(temp);
							isnode = false;
						}
					}
				}
				ret.nodes.push_back(tpart);
				tpart.clear();
				var1 = "";
				num1 = 0;
				hasnum1 = false;
				decimal1 = false;
				dplas1 = 0;
				neg1 = false;
				canneg = false;
			}
		}
		if (hasnum1) {
			tpart.Src.push_back(valValue);
			tpart.Val.push_back(num1);
			ret.nodes.push_back(tpart);
		}
		else {
			if (var1 != "") {
				tpart.Src.push_back(valVar);
				tpart.Var.push_back(vars.getRef(var1));
				ret.nodes.push_back(tpart);
			}
			else {
				if (isnode) {
					tpart.Src.push_back(valNode);
					tpart.nodes.push_back(temp);
					isnode = false;
					ret.nodes.push_back(tpart);
				}
			}
		}
		return ret;
	}else{
		for (int i = 0; i < text.length(); i++) {
			pic = text.substr(i, 1);
			ipic = meth.asc(pic);
			if (pic == " ") {
				canneg = false;
			}
			else if (pic == "." || pic == "-" || (ipic > 47 && ipic < 58)) {
				if (pic == "-") {
					canneg = true;
				}
				else if (pic == ".") {
					if (canneg) neg1 = true;
					if (decimal1) {
						//report error
					}
					decimal1 = true;
					hasnum1 = true;
				}
				else {
					if (canneg) neg1 = true;
					hasnum1 = true;
					if (decimal1) {
						dplas1++;
						num1 += pow(10, -dplas1) * (ipic - 48);
					}
					else {
						num1 *= 10;
						num1 += ipic - 48;
					}
				}
			}
			else if ((ipic > 64 && ipic < 91) || (ipic > 96 && ipic < 123)) {
				var1 += pic;
			}
			else if (pic == "#") {
				temp = nodes.at(0);
				isnode = true;
			}
		}
		if (hasnum1) {
			temp.Src.push_back(valValue);
			temp.Val.push_back(num1);
		}
		else if (!isnode) {
			temp.Src.push_back(valVar);
			temp.Var.push_back(vars.getRef(var1));
		}
		ret.nodes.push_back(temp);
		return temp;
	}
}

OpNode TreeMaker::combvar(OpNode inod, std::string var)
{
	OpNode ret;
	ret.nodes.push_back(inod);
	ret.Src.push_back(valIndexed);
	ret.Var.push_back(vars.getRef(var));
	return ret;
}

OpNode TreeMaker::combfun(OpNode inod, int fun, bool internal)
{
	OpNode ret;
	ret.nodes.push_back(inod);
	if (internal) {
		ret.Src.push_back(valInternal);
	}else{
		ret.Src.push_back(valExternal);
	}
	ret.Var.push_back(fun);
	return ret;
}


int TreeMaker::countNodes(std::string text, int index)
{
    int cnt = -1;
    for (int i = 0; i < index - 1; i++) if (text.substr(i, 1) == "#") cnt++;
	if (cnt < 0) cnt = 0;
    return cnt;
}


bool TreeMaker::hasPeren(std::string text)
{
	std::string pic;
	int ipic;
	int parcnt = 0;
	bool incon = true;
	for (int i = 0; i < text.length(); i++) {
		if (text.substr(i, 1) == "(") return true;
		
	}
	return false;
}

std::string TreeMaker::fromNum(double val)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(15) << val;
	return stream.str();
}

bool TreeMaker::detComma(std::string text)
{
	for (int i = 0; i < text.length(); i++) if (text.substr(i, 1) == ",") return true;
	return false;
}

OpNode TreeMaker::numwithvar(double num, std::string var, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valValue);
	ret.Src.push_back(valVar);
	ret.Val.push_back(num);
	ret.Var.push_back(vars.getRef(var));
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::varwithnum(std::string var, double num, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valVar);
	ret.Src.push_back(valValue);	
	ret.Val.push_back(num);
	ret.Var.push_back(vars.getRef(var));
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::varwithvar(std::string var1, std::string var2, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valVar);
	ret.Src.push_back(valVar);
	ret.Var.push_back(vars.getRef(var1));
	ret.Var.push_back(vars.getRef(var2));
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::varwithnode(std::string var, OpNode nod, tokenName token)
{
	OpNode ret;
	if (nod.Src.size() < 2) {
		ret.Src.push_back(valVar);
		ret.Src.push_back(nod.Src.at(0));
		ret.Var.push_back(vars.getRef(var));
		ret.Var.push_back(nod.Var.at(0));
		switch (nod.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod.Val.at(0));
			break;
		}
	}else{
		ret.Src.push_back(valVar);
		ret.Src.push_back(valNode);
		ret.Var.push_back(vars.getRef(var));
		ret.nodes.push_back(nod);
	}	
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::nodewithvar(OpNode nod, std::string var, tokenName token)
{
	OpNode ret;
	if (nod.Src.size() < 2) {
		ret.Src.push_back(nod.Src.at(0));
		ret.Src.push_back(valVar);		
		ret.Var.push_back(vars.getRef(var));
		ret.Var.push_back(nod.Var.at(0));
		switch (nod.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod.Val.at(0));
			break;
		}
	}else{
		ret.Src.push_back(valNode);
		ret.Src.push_back(valVar);
		ret.Var.push_back(vars.getRef(var));
		ret.nodes.push_back(nod);
	}
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::numwithnode(double num, OpNode nod, tokenName token)
{
	OpNode ret;
	if (nod.Src.size() < 2) {		
		ret.Src.push_back(valValue);
		ret.Src.push_back(nod.Src.at(0));
		ret.Val.push_back(num);
		ret.Var.push_back(nod.Var.at(0));
		switch (nod.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod.Val.at(0));
			break;
		}
	}else{		
		ret.Src.push_back(valValue);
		ret.Src.push_back(valNode);
		ret.Val.push_back(num);
		ret.nodes.push_back(nod);
	}
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::nodewithnum(OpNode nod, double num, tokenName token)
{
	OpNode ret;
	if (nod.Src.size() < 2) {		
		ret.Src.push_back(nod.Src.at(0));
		ret.Src.push_back(valValue);
		ret.Val.push_back(num);
		ret.Var.push_back(nod.Var.at(0));
		switch (nod.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod.Val.at(0));
			break;
		}
	}else{
		ret.Src.push_back(valNode);
		ret.Src.push_back(valValue);		
		ret.Val.push_back(num);
		ret.nodes.push_back(nod);
	}
	ret.oper = token;
	return ret;
}

OpNode TreeMaker::nodewithnode(OpNode nod1, OpNode nod2, tokenName token)
{
	OpNode ret;
	ret.oper = token;
	if (nod1.Src.size() < 2) {
		ret.Src.push_back(nod1.Src.at(0));
		ret.Var.push_back(nod1.Var.at(0));
		switch (nod1.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod1.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod1.Val.at(0));
			break;
		}
	}else{
		ret.Src.push_back(valNode);
		ret.nodes.push_back(nod1);
	}
	if (nod2.Src.size() < 2) {
		ret.Src.push_back(nod2.Src.at(0));
		ret.Var.push_back(nod1.Var.at(0));
		switch (nod1.Src.at(0)) {
		case valIndexed:
			ret.nodes.push_back(nod1.nodes.at(0));
			break;
		case valFixed:
			ret.Val.push_back(nod1.Val.at(0));
			break;
		}
	}else{
		ret.Src.push_back(valNode);
		ret.nodes.push_back(nod2);
	}
	
	return ret;
}

OpNode TreeMaker::valwithfunc(double num, OpNode nod, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valValue);
	ret.Src.push_back(nod.Src.at(0));
	ret.Val.push_back(num);
	ret.nodes.push_back(nod.nodes.at(0));
	return ret;
}

OpNode TreeMaker::funcwithval(OpNode nod, double num, tokenName token)
{
	OpNode ret;	
	ret.Src.push_back(nod.Src.at(0));
	ret.Src.push_back(valValue);
	ret.Val.push_back(num);
	ret.nodes.push_back(nod.nodes.at(0));
	return ret;
}

OpNode TreeMaker::varwithfunc(std::string var, OpNode nod, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valVar);
	ret.Src.push_back(nod.Src.at(0));
	ret.Var.push_back(vars.getRef(var));
	ret.Var.push_back(nod.Var.at(0));	
	ret.nodes.push_back(nod.nodes.at(0));
	return ret;
}

OpNode TreeMaker::funcwithvar(OpNode nod, std::string var, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(nod.Src.at(0));
	ret.Src.push_back(valVar);
	ret.Var.push_back(nod.Var.at(0));
	ret.Var.push_back(vars.getRef(var));
	ret.nodes.push_back(nod.nodes.at(0));
	return ret;
}

OpNode TreeMaker::funcwithnode(OpNode nod1, OpNode nod2, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(nod1.Src.at(0));
	ret.Src.push_back(valNode);
	ret.Var.push_back(nod1.Var.at(0));
	ret.nodes.push_back(nod1.nodes.at(0));
	ret.nodes.push_back(nod2);
	return ret;
}

OpNode TreeMaker::nodewithfunc(OpNode nod1, OpNode nod2, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valNode);
	ret.Src.push_back(nod2.Src.at(0));	
	ret.Var.push_back(nod2.Var.at(0));
	ret.nodes.push_back(nod1);
	ret.nodes.push_back(nod2.nodes.at(0));
	return ret;
}

OpNode TreeMaker::funcwithfunc(OpNode nod1, OpNode nod2, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(nod1.Src.at(0));
	ret.Src.push_back(nod2.Src.at(0));
	ret.Var.push_back(nod1.Var.at(0));
	ret.Var.push_back(nod2.Var.at(0));
	ret.nodes.push_back(nod1.nodes.at(0));
	ret.nodes.push_back(nod2.nodes.at(0));
	return ret;
}

OpNode TreeMaker::numwithfunc(double num, OpNode nod, tokenName token)
{
	OpNode ret;
	ret.Src.push_back(valValue);
	ret.Src.push_back(nod.Src.at(0));
	ret.Var.push_back(nod.Var.at(0));
	ret.Val.push_back(num);
	ret.nodes.push_back(nod.nodes.at(0));
	return ret;
}


