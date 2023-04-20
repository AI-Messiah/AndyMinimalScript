#include "Variables.h"

ErrorHandler ahand;


int Variables::getRef(std::string name)
{
	if (refs.contains(name)) {
		int idx = refs[name];
		if (!vplas.at(idx).active) {
			//report error
		}
		return idx;
	}else {
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
			//report error(5);
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

bool Variables::exists(std::string name)
{
	return refs.contains(name);
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
				//report error(6);
			}
		}
		else {
			//report error(7);
		}
	}
	else {
		//report error(8);
	}
}

bool Variables::isActive(int num)
{
	if (num < vplas.max_size()) {
		
		if (vplas.at(num).active) {
			return true;
		}
	}else{
		//report error(8);
	}
	return false;
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
					//report error(9);
				}
			}
			else {
				//report error(6);				
			}
		}
		else {
			//report error(7);			
		}

	}
	
	return 0.0;
}

aval Variables::SetGet(int num, int par)
{
	aval ret;
	ret.value = 0;
	ret.defined = false;
	if (num < vplas.size()) {
		
		if (vplas.at(num).active) {
			if (par < vplas.at(num).vals.size() && par >= 0) {
				ret = vplas.at(num).vals.at(par);
				return ret;
			}
			else {
				//report error(6);
			}
		}
		else {
			//report error(7);
		}
	}
	else {
		//report error(8);
	}
	return ret;
}


bool Variables::isArray(int num)
{
	if (num < vplas.size()) {
		
		if (vplas.at(num).active) {
			return (vplas.at(num).vals.size() > 1);
		}
	}else{
		//report error(8);
	}
	return false;
}

int Variables::getNum(std::string name)
{
	if (refs.contains(name)) {
		return refs[name];
	}
	//report error
	return -1;
}

void Variables::clear()
{
	for (int i = 0; i < vplas.size(); i++) vplas.at(i).active = false;
	
}
