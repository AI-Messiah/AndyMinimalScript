#include "Recieve.h"


double printmeth(std::vector<double> inp) {
	std::stringstream stream;
	std::cout << inp.at(0) << "\n";	
	return 0;
}

void Recieve::converted(const char* inp)
{
	std::string str(inp);
	inter.setFunction("print", &printmeth);
	inter.handleScript(str);
}
