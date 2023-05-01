#include "Operators.h"

namespace AndyInt {
	OpNode::OpNode()
	{


	}

	OpNode::~OpNode()
	{

	}

	double OpNode::evaluate()
	{
		int fside = 0;
		int varcnt = 0;
		int nodcnt = 0;
		int numcnt = 0;
		double val1 = 0;
		double val2 = 0;
		double nval1 = 0;
		double nval2 = 0;

		for (int i = 0; i < Src.size(); i++) {
			switch (Src.at(i)) {
			case valNone:

				break;
			case valVar:
				if (fside == 0) {
					val1 = vars.Get(Var.at(varcnt).num, 0);
					if (Var.at(varcnt).neg) val1 *= -1;
				}
				else {
					val2 = vars.Get(Var.at(varcnt).num, 0);
					if (Var.at(varcnt).neg) val2 *= -1;
				}
				varcnt++;
				break;
			case valValue:
				if (fside == 0) {
					val1 = Val.at(numcnt);
				}
				else {
					val2 = Val.at(numcnt);
				}
				numcnt++;
				break;
			case valNode:
				if (fside == 0) {
					val1 = nodes.at(nodcnt).evaluate();
				}
				else {
					val2 = nodes.at(nodcnt).evaluate();
				}
				nodcnt++;
				break;
			case valIndexed:
				if (fside == 0) {
					nval1 = nodes.at(nodcnt).evaluate();
					val1 = vars.Get(Var.at(varcnt).num, nval1);
					if (Var.at(varcnt).neg) val1 *= -1;
				}
				else {
					nval2 = nodes.at(nodcnt).evaluate();
					val2 = vars.Get(Var.at(varcnt).num, nval2);
					if (Var.at(varcnt).neg) val2 *= -1;
				}
				nodcnt++;
				varcnt++;
				break;
			case valFixed:
				if (fside == 0) {
					nval1 = Val.at(varcnt);
					val1 = vars.Get(Var.at(varcnt).num, nval1);
					if (Var.at(varcnt).neg) val1 *= -1;
				}
				else {
					nval2 = Val.at(varcnt);
					val2 = vars.Get(Var.at(varcnt).num, nval2);
					if (Var.at(varcnt).neg) val2 *= -1;
				}
				numcnt++;
				varcnt++;
				break;
			case valInternal:
				if (fside == 0) {
					nval1 = nodes.at(nodcnt).evaluate();
					val1 = trans.calFun(Var.at(varcnt).num, nval1);
					if (Var.at(varcnt).neg) val1 *= -1;
				}
				else {
					nval1 = nodes.at(nodcnt).evaluate();
					val2 = trans.calFun(Var.at(varcnt).num, nval2);
					if (Var.at(varcnt).neg) val2 *= -1;
				}
				nodcnt++;
				varcnt++;
				break;
			case valExternal:
				std::vector<double> pargs;
				pargs.clear();
				if (fside == 0) {
					if (nodes.at(nodcnt).nodes.size() < 2) {

						nval1 = nodes.at(nodcnt).evaluate();
						pargs.push_back(nval1);
					}
					else {
						for (int i = 0; i < nodes.at(nodcnt).nodes.size(); i++) {
							nval1 = nodes.at(nodcnt).nodes.at(i).evaluate();
							pargs.push_back(nval1);
						}
					}
					val1 = trans.callext(Var.at(varcnt).num, pargs);
					if (Var.at(varcnt).neg) val1 *= -1;
					nodcnt++;
					varcnt++;
				}
				else {

					for (int i = 0; i < nodes.at(nodcnt).nodes.size(); i++) {
						nval1 = nodes.at(nodcnt).nodes.at(i).evaluate();
						pargs.push_back(nval1);
					}
					val2 = trans.callext(Var.at(varcnt).num, pargs);
					if (Var.at(varcnt).neg) val2 *= -1;
				}
				nodcnt++;
				varcnt++;
				break;
			}
			fside++;
		}
		if (fside == 1) {
			return val1;
		}
		else if (fside == 2) {
			return calc.Calculate(val1, val2, oper);
		}
		else {
			ahand.report(22);
			return 0;
		}
	}

	void OpNode::clear()
	{
		oper = opNone;


		Src.clear();
		Val.clear();
		Var.clear();

		nodes.clear();
	}

	bool OpNode::assign(tokenName tok, double ival)
	{
		if (Src.size() == 1) {
			aval prevVal;
			double par = 0;
			switch (Src.at(0)) {
			case valVar:
				prevVal = vars.SetGet(Var.at(0).num, 0);

				break;
			case valFixed:
				par = Val.at(0);
				prevVal = vars.SetGet(Var.at(0).num, int(par));

				break;
			case valIndexed:
				par = nodes.at(0).evaluate();
				prevVal = vars.SetGet(Var.at(0).num, int(par));

				break;
			default:
				ahand.report(20);
				return false;
				break;
			}
			bool avail = (tok == opAssignDirect || prevVal.defined);
			if (!avail) {
				ahand.report(19);
				return false;
			}
			double fval = 0;
			if (prevVal.defined) fval = prevVal.value;
			fval = calc.Calculate(fval, ival, tok);
			vars.Set(Var.at(0).num, fval, int(par));
			return true;
		}
		else if (Src.size() == 0) {
			ahand.report(21);
		}
		else {
			ahand.report(20);
		}
		return false;
	}
}


