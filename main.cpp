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

int main(){
	ifstream in("source1.txt");
	string text;
	string line;
	while (getline(in, line)) {
		text += line + "\n";
	}
	Interface inter;
	inter.setErrorHandler(&errhand);
	inter.setFunction("print", &printm);
	inter.handleScript(text);
	in.close();
	return 0;
}