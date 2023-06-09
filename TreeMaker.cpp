#include "TreeMaker.h"
namespace AndyInt {
	OpNode TreeMaker::createTree(std::string text)
	{
		VarDetect vdet[2];
		std::vector<OpNode> nodes;
		OpNode temp;
		OpNode temp1;
		if (text == "") {
			//ahand.report(3);
			return temp;
		}
		double num1;
		double num2;
		bool isnode1;
		bool isnode2;
		bool nfset;
		bool nfset1;
		int dplas1;
		int dplas2;
		int nodref;
		bool cntch;
		int cntprt;
		std::string pic;
		int ipic;
		int frm, frm1, frm2, to;
		frm = -1;
		frm2 = -1;
		int npl;
		bool incon;
		tokenName curtok;
		std::string temsym;
		int exprnum;
		int fundet;
		int nodepl1, nodepl2;
		valType vtype1, vtype2;
		int ufnd;
		int parcnt = 0;
		std::string pic1;
		for (int i = 0; i < text.length(); i++) {
			if (text.substr(i, 1) == "(") parcnt++;
			if (text.substr(i, 1) == ")") parcnt--;
		}
		if (parcnt != 0) {
			ahand.report(4);
			return temp;
		}
	resetlbl:
		while (hasPeren(text)) {
			fundet = -1;
			cntprt = 0;
			frm = -1;
			frm2 = -1;
			incon = false;
			vdet[0].clear();
			cntch = true;
			parcnt = 0;
			while (cntprt < text.length() && !(text.substr(cntprt, 1) == ")" && parcnt == 1)) {
				if (text.substr(cntprt, 1) == ")") parcnt--;
				if (text.substr(cntprt, 1) == "(") {
					parcnt++;
					if (frm2 < 0) frm2 = cntprt;
					cntch = false;
				}
				pic = text.substr(cntprt, 1);
				ipic = meth.asc(pic);
				if (pic == " ") {
					incon = true;
					if (cntch) {
						vdet[0].clear();
						fundet = -1;
						frm = -1;
					}
				}
				else if (cntch){
					if (vdet[0].isAccepted(text, cntprt)) {
						incon = false;
						if (frm < 0) frm = cntprt;
						
					}
				}
				cntprt++;
			}
			temp = createTree(text.substr(frm2 + 1, cntprt - frm2 - 1));
			
			switch (vdet[0].type) {
			case typeVar:
				switch (temp.nodes.size()) {
				case 0:
					ahand.report(32);
					break;
				case 1:
					temp = combvar(temp.nodes.at(0), vdet[0].getVal());					
					npl = countNodes(text, frm);
					nodes.insert(nodes.begin() + npl, temp);
					text = meth.emplace(text, frm, cntprt + 1);
				default:
					ahand.report(36);
					break;
				}
				break;
			case typeIntern:
				switch (temp.nodes.size()) {
				case 0:
					if (vdet[0].funval < 14) {
						ahand.report(32);
					}else{
						OpNode anul;
						temp = combfun(anul, vdet[0].funval, vdet[0].neg, true);
						
						npl = countNodes(text, frm);
						nodes.insert(nodes.begin() + npl, temp);
						text = meth.emplace(text, frm, cntprt + 1);
					}
					break;
				case 1:
					if (vdet[0].funval < 14) {
						if (temp.nodes.at(0).Src.at(0) == valValue) {
							double num = temp.nodes.at(0).Val.at(0);
							num = trans.calFun(fundet, num);
							std::string rep = fromNum(num);
							text = meth.RepText(text, rep, frm, cntprt);
						}else{
							temp = combfun(temp.nodes.at(0), vdet[0].funval, vdet[0].neg, true);
							
							npl = countNodes(text, frm);
							nodes.insert(nodes.begin() + npl, temp);
							text = meth.emplace(text, frm, cntprt + 1);
						}
						
					}else{
						ahand.report(30);
					}
					break;
				default:
					ahand.report(31);
					break;
				}
				break;
			case typeExtern:
				temp = combfun(temp, vdet[0].funval - 16, vdet[0].neg, false);				
				npl = countNodes(text, frm);
				nodes.insert(nodes.begin() + npl, temp);
				text = meth.emplace(text, frm, cntprt + 1);
				break;
			case typeNone:
				if (temp.nodes.size() > 0) {
					if (temp.nodes.at(0).Src.at(0) == valValue) {
						double num = temp.Val.at(0);
						std::string rep = fromNum(num);
						text = meth.RepText(text, rep, frm, cntprt);
					}else{
						if (temp.nodes.at(0).nodes.size() > 0) {							
							npl = countNodes(text, frm);
							nodes.insert(nodes.begin() + npl, temp.nodes.at(0).nodes.at(0));
							text = meth.emplace(text, frm, cntprt + 1);
						}else{

						}
					}
				}else{
					ahand.report(34);
				}
				break;
			default:
				if (temp.Src.size() == 0) ahand.report(34);
				ahand.report(35);
				break;
			}
			goto resetlbl;
		}
		bool accepted = true;
		bool subacc;
		for (int i = 0; i < text.length(); i++) {
			subacc = false;
			for (int j = 0; j < acChars.length(); j++) {
				if (text.substr(i, 1) == acChars.substr(j, 1)) subacc = true;
			}
			if (!subacc) accepted = false;
		}
		if (!accepted) {
			ahand.report(5);
		}
		for (int pri = 0; pri < 9; pri++) {
			for (int sid = 0; sid < 2; sid++) {
			resetlbl1:
				cntprt = 0;
				curtok = opNone;
				exprnum = 0;
				vdet[0].clear();
				vdet[1].clear();
				vdet[0].sid = sid;
				vdet[1].sid = sid;
				num1 = 0;
				num2 = 0;
				isnode1 = false;
				isnode2 = false;
				nodref = -1;
				nfset = true;
				nfset1 = false;
				dplas1 = 0;
				dplas2 = 0;
				nodref = 0;
				ufnd = -1;
				frm1 = -1;

				temp.clear();
				while (cntprt < text.length() + 1) {
					if (cntprt < text.length()) {
						pic = text.substr(cntprt, 1);
						if (cntprt < text.length() - 1) {
							pic1 = text.substr(cntprt + 1, 1);
						}else{
							pic1 = "";
						}
					}
					else {
						pic = "~";
					}
					ipic = meth.asc(pic);
					if (vdet[exprnum].isAccepted(text, cntprt)) {
						to = cntprt;
						if (nfset) {
							frm = cntprt;

							nfset = false;
						}
						if (nfset1) {
							frm1 = cntprt;

							nfset1 = false;
						}
						if (vdet[exprnum].node) {

							if (exprnum == 0) {                                          //////
								isnode1 = true;
								nodepl1 = countNodes(text, cntprt);
							}
							else {
								isnode2 = true;
								nodepl2 = countNodes(text, cntprt);
							}
							nodref = countNodes(text, cntprt);
						}
					}
					else if (pic == ",") {
						exprnum = 0;
						vdet[0].clear();
						vdet[1].clear();

						num1 = 0;
						num2 = 0;

						isnode1 = false;
						isnode2 = false;
						nodref = -1;
						nfset = true;
						nfset1 = false;
						dplas1 = 0;
						dplas2 = 0;
						nodref = 0;
					}
					else {
						if (curtok != opNone) {
							if (curtok == opInvert) {
								if (vdet[1].type == typeNum) {
									num2 = vdet[1].getNum();
									std::string rep;
									if (vdet[1].Uord) {
										rep = (num2 != 0) ? "-1" : "0";
									}
									else {
										rep = (num2 != 0) ? "1" : "0";
									}
									text = meth.RepText(text, rep, frm, to + 1);
									goto resetlbl1;
								}
								else if (sid == 1) {
									vtype2 = vdet[1].type1;
									OpNode nod;
									if (vtype2 == typeNode) {
										if ((nodes.at(nodepl2).Src.at(0) == valInternal && nodes.at(nodepl2).Src.size() < 2) || (nodes.at(nodepl2).Src.at(0) == valExternal && nodes.at(nodepl2).Src.size() < 2)) {
											vtype2 = typeFunc;
										}
										else {
											vtype2 = typeNode;
										}
										nodref = countNodes(text, cntprt);
										nod = nodes.at(nodref);
									}
									else {
										if (vtype2 == typeNone) ahand.report(6);
									}


									temp.clear();
									switch (vtype2) {
									case typeVar:
										temp.Src.push_back(valVar);
										temp.Var.push_back(vdet[1].getVal());
										temp.oper = opInvert;
										temp.Uord.push_back(vdet[1].Uord);
										nodes.insert(nodes.begin() + nodref, temp);
										text = meth.emplace(text, ufnd, to + 1);
										break;
									case typeFunc:
										temp.Uord.push_back(vdet[1].Uord);
										temp.Src.push_back(nod.Src.at(0));
										temp.Var.push_back(nod.Var.at(0));
										temp.nodes.push_back(nod.nodes.at(0));
										temp.oper = opInvert;
										nodes.at(nodref) = temp;
										text = meth.elimchar(text, ufnd);
										break;
									case typeNode:
										temp.Uord.push_back(vdet[1].Uord);
										temp.Src.push_back(valNode);
										temp.nodes.push_back(nod);
										temp.oper = opInvert;
										nodes.at(nodref) = temp;
										text = meth.elimchar(text, ufnd);
										break;
									}
									goto resetlbl1;
								}
							}
							else {
								if (vdet[0].type == typeNum && vdet[1].type == typeNum) {
									num1 = vdet[0].getNum();
									num2 = vdet[1].getNum();
									std::string rep = fromNum(calc.Calculate(num1, num2, curtok));
									text = meth.RepText(text, rep, frm, to + 1);
									goto resetlbl1;
								}
								else if (sid == 1) {
									vtype1 = vdet[0].type1;
									vtype2 = vdet[1].type1;
									if (vtype1 == typeNum) num1 = vdet[0].getNum();
									if (vtype2 == typeNum) num2 = vdet[1].getNum();
									if (vtype1 == typeNode) {
										if ((nodes.at(nodepl1).Src.at(0) == valInternal && nodes.at(nodepl1).Src.size() < 2) || (nodes.at(nodepl1).Src.at(0) == valExternal && nodes.at(nodepl1).Src.size() < 2)) {
											vtype1 = typeFunc;
										}
										else {
											vtype1 = typeNode;
										}
									}
									else {
										if (vtype1 == typeNone) ahand.report(6);
									}
									if (vtype2 == typeNode) {
										if ((nodes.at(nodepl2).Src.at(0) == valInternal && nodes.at(nodepl2).Src.size() < 2) || (nodes.at(nodepl2).Src.at(0) == valExternal && nodes.at(nodepl2).Src.size() < 2)) {
											vtype2 = typeFunc;
										}
										else {
											vtype2 = typeNode;
										}
									}
									else {
										if (vtype2 == typeNone) ahand.report(6);
									}
									if (vtype1 != typeNone && vtype2 != typeNone) {
										nodref = countNodes(text, cntprt);
										switch (vtype1) {
										case typeNum:
											switch (vtype2) {
											case typeVar:
												temp = numwithvar(num1, vdet[0].getVal(), curtok);
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
												temp = varwithnum(vdet[0].getVal(), num2, curtok);
												nodes.insert(nodes.begin() + nodref, temp);
												break;
											case typeVar:
												temp = varwithvar(vdet[0].getVal(), vdet[1].getVal(), curtok);
												nodes.insert(nodes.begin() + nodref, temp);
												break;
											case typeFunc:
												temp = varwithfunc(vdet[0].getVal(), nodes.at(nodref), curtok);
												nodes.at(nodref) = temp;
												break;
											case typeNode:
												temp = varwithnode(vdet[0].getVal(), nodes.at(nodref), curtok);
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
												temp = funcwithvar(nodes.at(nodref), vdet[1].getVal(), curtok);
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
												break;
											case typeVar:
												temp = nodewithvar(nodes.at(nodref), vdet[1].getVal(), curtok);
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
										text = meth.emplace(text, vdet[0].fstpla, to);
										goto resetlbl1;
									}
									else {
										ahand.report(14);
										return temp;
									}
								}
							}
						}
						else {
							for (int i = 0; i < int(smp.mathOps.length() / 2); i++) {
								if (smp.priority[i] == pri) {
									temsym = smp.mathOps.substr(i * 2, 2);
									if (temsym.substr(1, 1) == " ") temsym = temsym.substr(0, 1);
									if (temsym.length() == 1) {
										if (temsym == pic) {										
											
											if (pic1 == " ") {
												curtok = smp.convertedTokens[pic];
												if (curtok == opInvert) ufnd = cntprt;
											}
										}
									}
									else {
										if (cntprt > 0) {											
											
											if (pic + pic1 == temsym) {
												curtok = smp.convertedTokens[pic + pic1];
												
											}
										}
									}
								}
							}
							
							if (pic1 != " ") cntprt++;
							nfset1 = true;
							if (exprnum == 1) {
								frm = frm1;
								isnode1 = isnode2;
								isnode2 = false;
								vdet[0] = vdet[1];
								vdet[1].clear();

							}
							exprnum = 1;
						}
					}
					cntprt++;
				}

			}
		}
		vdet[0].clear();
		isnode1 = false;
		nodref = -1;
		dplas1 = 0;
		dplas2 = 0;
		nodref = 0;
		bool isnode = false;
		frm1 = -1;
		temp.clear();
		OpNode ret;

		accepted = true;
		for (int i = 0; i < text.length(); i++) {
			subacc = false;
			for (int j = 0; j < acChars.length(); j++) {
				if (text.substr(i, 1) == acChars.substr(j, 1)) subacc = true;
			}
			if (!subacc) accepted = false;
		}
		if (!accepted) {
			ahand.report(5);
		}

		if (detComma(text)) {
			OpNode tpart;
			for (int i = 0; i < text.length(); i++) {
				pic = text.substr(i, 1);
				ipic = meth.asc(pic);
				if (vdet[0].isAccepted(text, i)) {
					if (vdet[0].node) {
						int npl = countNodes(text, i);
						temp = nodes.at(npl);
						isnode = true;
					}
				}
				else if (pic == ",") {
					if (vdet[0].type == typeNum) {
						tpart.Src.push_back(valValue);
						tpart.Val.push_back(vdet[0].getNum());

					}
					else {
						if (vdet[0].type == typeVar) {
							tpart.Src.push_back(valVar);
							tpart.Var.push_back(vdet[0].getVal());
						}
						else {
							if (vdet[0].type == typeNode) {
								tpart.Src.push_back(valNode);
								tpart.nodes.push_back(temp);
								isnode = false;
							}
						}
					}
					ret.nodes.push_back(tpart);
					tpart.clear();
					vdet[0].clear();
					
				}


			}
			if (vdet[0].type == typeNum) {
				tpart.Src.push_back(valValue);
				tpart.Val.push_back(vdet[0].getNum());
				ret.nodes.push_back(tpart);
			}
			else {
				if (vdet[0].type == typeVar) {
					tpart.Src.push_back(valVar);
					tpart.Var.push_back(vdet[0].getVal());
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
		}
		else {
			ret.Src.push_back(valNode);
			for (int i = 0; i < text.length(); i++) {
				pic = text.substr(i, 1);
				ipic = meth.asc(pic);
				if (vdet[0].isAccepted(text, i)) {
					if (vdet[0].node) {
						temp = nodes.at(0);
						isnode = true;
					}
				}
			}
			if (vdet[0].type == typeNum) {
				temp.Src.push_back(valValue);
				temp.Val.push_back(vdet[0].getNum());
			}
			else if (vdet[0].type == typeVar) {
				temp.Src.push_back(valVar);
				temp.Var.push_back(vdet[0].getVal());
			}
			ret.nodes.push_back(temp);
			return ret;
		}
	}

	OpNode TreeMaker::combvar(OpNode inod, varinc var)
	{
		OpNode ret;
		ret.nodes.push_back(inod);
		ret.Src.push_back(valIndexed);
		ret.Var.push_back(var);
		return ret;
	}

	OpNode TreeMaker::combfun(OpNode inod, int fun, bool neg, bool internal)
	{
		OpNode ret;
		ret.nodes.push_back(inod);
		if (internal) {
			ret.Src.push_back(valInternal);
		}
		else {
			ret.Src.push_back(valExternal);
		}
		varinc inc;
		inc.num = fun;
		inc.neg = neg;
		ret.Var.push_back(inc);
		return ret;
	}


	int TreeMaker::countNodes(std::string text, int index)
	{
		int cnt = -1;

		for (int i = 0; i < index; i++) if (text.substr(i, 1) == "#") cnt++;
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

	OpNode TreeMaker::numwithvar(double num, varinc var, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(valValue);
		ret.Src.push_back(valVar);
		ret.Val.push_back(num);
		ret.Var.push_back(var);
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::varwithnum(varinc var, double num, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(valVar);
		ret.Src.push_back(valValue);
		ret.Val.push_back(num);
		ret.Var.push_back(var);
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::varwithvar(varinc var1, varinc var2, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(valVar);
		ret.Src.push_back(valVar);
		ret.Var.push_back(var1);
		ret.Var.push_back(var2);
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::varwithnode(varinc var, OpNode nod, tokenName token)
	{
		OpNode ret;
		if (nod.Src.size() < 2) {
			ret.Src.push_back(valVar);
			ret.Src.push_back(nod.Src.at(0));
			ret.Var.push_back(var);
			ret.Var.push_back(nod.Var.at(0));
			switch (nod.Src.at(0)) {
			case valIndexed:
				ret.nodes.push_back(nod.nodes.at(0));
				break;
			case valFixed:
				ret.Val.push_back(nod.Val.at(0));
				break;
			}
		}
		else {
			ret.Src.push_back(valVar);
			ret.Src.push_back(valNode);
			ret.Var.push_back(var);
			ret.nodes.push_back(nod);
		}
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::nodewithvar(OpNode nod, varinc var, tokenName token)
	{
		OpNode ret;
		if (nod.Src.size() < 2) {
			ret.Src.push_back(nod.Src.at(0));
			ret.Src.push_back(valVar);
			ret.Var.push_back(var);
			ret.Var.push_back(nod.Var.at(0));
			switch (nod.Src.at(0)) {
			case valIndexed:
				ret.nodes.push_back(nod.nodes.at(0));
				break;
			case valFixed:
				ret.Val.push_back(nod.Val.at(0));
				break;
			}
		}
		else {
			ret.Src.push_back(valNode);
			ret.Src.push_back(valVar);
			ret.Var.push_back(var);
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
		}
		else {
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
		}
		else {
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
		}
		else {
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
		}
		else {
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
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::funcwithval(OpNode nod, double num, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(nod.Src.at(0));
		ret.Src.push_back(valValue);
		ret.Val.push_back(num);
		ret.nodes.push_back(nod.nodes.at(0));
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::varwithfunc(varinc var, OpNode nod, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(valVar);
		ret.Src.push_back(nod.Src.at(0));
		ret.Var.push_back(var);
		ret.Var.push_back(nod.Var.at(0));
		ret.nodes.push_back(nod.nodes.at(0));
		ret.oper = token;
		return ret;
	}

	OpNode TreeMaker::funcwithvar(OpNode nod, varinc var, tokenName token)
	{
		OpNode ret;
		ret.Src.push_back(nod.Src.at(0));
		ret.Src.push_back(valVar);
		ret.Var.push_back(nod.Var.at(0));
		ret.Var.push_back(var);
		ret.nodes.push_back(nod.nodes.at(0));
		ret.oper = token;
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
		ret.oper = token;
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
		ret.oper = token;
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
		ret.oper = token;
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
		ret.oper = token;
		return ret;
	}
}

