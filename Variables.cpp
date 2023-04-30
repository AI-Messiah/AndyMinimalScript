#include "Variables.h"

ErrorHandler ahand;

int Variables::getRef(std::string name)
{
	if (refs.contains(name)) {
		int idx = refs[name];
		if (!vplas.at(idx).active) {
			ahand.report(8);
		}
		return idx;
	}else {
		ahand.report(7);
		return 0;
	}
	
}

void Variables::Create(std::string name, long double val, bool hasval, int pars)
{
	if (!refs.contains(name)) {
		refs.insert(std::pair<std::string, int>(name, curidx));
		varref nref;

		nref.active = true;
		nref.scope = cscope;
		aval vref;
		for (int i = 0; i < pars; i++) {
			vref.defined = false;
			vref.value = 0;
			if (hasval && pars == 1) {
				vref.defined = true;
				vref.value = val;
			}
			nref.vals.push_back(vref);
		}
		vplas.push_back(nref);
		curidx++;
	}else{
		int anidx = refs[name];
		if (vplas.at(anidx).active) {
			ahand.report(9);
		}else{
			varref nref;
			nref.active = true;
			nref.scope = cscope;
			aval vref;
			for (int i = 0; i < pars; i++) {
				vref.defined = false;
				vref.value = 0;
				if (hasval && pars == 1) {
					vref.defined = true;
					vref.value = val;
				}
				nref.vals.push_back(vref);
			}
			vplas.at(anidx) = nref;
		}
	}
}

void Variables::IncScope()
{
	cscope++;
}

void Variables::DecScope()
{
	if (cscope > 0) cscope--;
	int clen = vplas.size();
	for (int i = 0; i < clen; i++) if (vplas.at(i).scope > cscope) {
		vplas.at(i).active = false;
		vplas.at(i).vals.clear();			
	}
}

void Variables::ResetScope()
{
	int clen = vplas.size();
	for (int i = 0; i < clen; i++) if (vplas.at(i).scope == cscope) {
		vplas[i].active = false;
		vplas[i].vals.clear();
	}
}

void Variables::Set(int num, long double val, int par)
{
	if (num < vplas.size()) {
		
		if (vplas.at(num).active) {
			if (par < vplas.at(num).vals.size() && par >= 0) {
				aval vref;
				vref.defined = true;
				vref.value = val;
				vplas.at(num).vals[par] = vref;
			}
			else {
				ahand.report(10);
			}
		}
		else {
			ahand.report(8);
		}
	}
	else {
		ahand.report(11);
	}
}


double Variables::Get(int num, int par)
{
	if (num < vplas.size()) {
		if (vplas.at(num).active) {
			if (par < vplas.at(num).vals.size() && par >= 0) {
				if (vplas.at(num).vals.at(par).defined) {
					return vplas.at(num).vals.at(par).value;
				}
				else {
					ahand.report(23);
				}
			}
			else {
				if (par < 0) {
					ahand.report(13);
				}else{
					ahand.report(10);
				}						
			}
		}
		else {
			ahand.report(8);
		}

	}
	
	return 0.0;
}

aval Variables::SetGet(int num, int par)
{
	aval ret;
	ret.value = 0;
	ret.defined = false;
	if (par < 0) {
		ahand.report(13);
		return ret;
	}
	if (num < vplas.size()) {
		
		if (vplas.at(num).active) {
			if (par < vplas.at(num).vals.size() && par >= 0) {
				ret = vplas.at(num).vals.at(par);
				return ret;
			}else{
				ahand.report(10);
			}
		}else{
			ahand.report(8);
		}
	}else{
		ahand.report(11);
	}
	return ret;
}



void Variables::clear()
{
	vplas.clear();
	refs.clear();
}
