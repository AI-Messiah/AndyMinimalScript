#include "Transit.h"

Transit::Transit()
{
	std::string funnames[] = { "abs", "acos" , "asin" , "atan", "ceil", "cos", "cosh", "exp", "floor", "log", "sin", "sinh", "tan", "tanh", "distrand", "secrand"};
	for (int i = 0; i < 16; i++) oFunNames[i] = funnames[i];
}

Transit::~Transit()
{
}

int Transit::intlookup(std::string name)
{
	for (int i = 0; i < 16; i++) {
		if (name == oFunNames[i]) return i;
	}
	return -1;
}

int Transit::extlookup(std::string name)
{
	for (int i = 0; i < funNames.size(); i++) {
		if (name == funNames[i]) return i;
	}
	return -1;
}

double Transit::calFun(int funval, double pasval){

	double result;
	try {
		switch (funval) {
		case 0:
			result = fabs(pasval);
			break;
		case 1:
			result = acos(pasval);
			break;
		case 2:
			result = asin(pasval);
			break;
		case 3:
			result = atan(pasval);
			break;
		case 4:
			result = ceil(pasval);
			break;
		case 5:
			result = cos(pasval);
			break;
		case 6:
			result = cosh(pasval);
			break;
		case 7:
			result = exp(pasval);
			break;
		case 8:
			result = floor(pasval);
			break;
		case 9:
			result = log(pasval);
			break;
		case 10:
			result = sin(pasval);
			break;
		case 11:
			result = sinh(pasval);
			break;
		case 12:
			result = tan(pasval);
			break;
		case 13:
			result = tanh(pasval);
			break;
		case 14:
			result = distRand();
			break;
		case 15:
			result = myRand();
			break;
		}
		return result;
	}
	catch (_exception e) {
		ahand.report(0);
	}
	return 0;
}

double Transit::callext(int num, std::vector<double> args)
{
	return ops.at(num)(args);	
}

void Transit::setFunction(std::string name, std::function<double(std::vector<double>)> address)
{
	for (int i = 0; i < funNames.size(); i++) if (funNames.at(i) == name) {

	}
	std::string excludes[] = { "while", "if", "else", "end", "def", "e" };
	for (int i = 0; i < 5; i++) if (name == excludes[i]) {

	}
	for (int i = 0; i < 16; i++) if (name == oFunNames[i]) {

	}
	funNames.push_back(name);
	ops.push_back(address);
	
}

double Transit::distRand()
{
	static bool firs = true;
	static std::default_random_engine gen;
	static std::uniform_real_distribution<long double> dist(0.0, 1.0);
	if (firs) {
		gen.seed(static_cast<unsigned int>(time(NULL)));
		firs = false;
	}
	return dist(gen);
}

uint64_t Transit::rdrand64()
{
	unsigned long long ret;   // not uint64_t, GCC/clang wouldn't compile.
	do {} while (!_rdrand64_step(&ret));  // retry until success.
	return ret;
}

double Transit::myRand()
{
	long double retv = 0;
	unsigned long long vlon = rdrand64();
	for (int i = 0; i < 48; i++) if ((unsigned long long)floor(vlon / pow(2, 63 - i)) % 2 > 0) retv += pow(2, -(i + 1));
	return retv;
}
