#include <fstream>
#include <iostream>
#include "Interface.h"

using namespace std;

string fromdub(double val) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(15) << val;
	return stream.str();
}

double printm(vector<double> inp) {
	
	for (int i = 0; i < inp.size(); i++) {
		cout << fromdub(inp.at(i)) << " ";		
	}
	cout << "\n";
	return 0;
}

void errhand(std::vector<errInfo> errors) {
	for (int i = 0; i < errors.size(); i++) {
		cout << errors.at(i).lineText << " " << errors.at(i).errType << " " << errors.at(i).errMes << "\n";
	}
}

double testfun(vector<double> inp) {
	double ret = 1;
	double chg;
	for (int i = 0; i < inp.size(); i++) {
		chg = inp.at(i) + 1.0 / ((double)i + 2.0);
		ret *= chg;
	}
	return ret;
}

int main(){
	ifstream in("source5.txt");
	string text;
	string line;
	while (getline(in, line)) {
		text += line + "\n";
	}
	Interface inter;
	inter.setErrorHandler(&errhand);
	inter.setFunction("print", &printm);
	inter.setFunction("testfun", &testfun);	
	inter.handleScript(text);
	in.close();
	return 0;
}