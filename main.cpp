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

int main(){
	ifstream in("source.txt");
	string text;
	string line;
	while (getline(in, line)) {
		text += line + "\n";
	}
	Interface inter;
	inter.setFunction("print", &printm);
	//inter.debugfunc("print(12)");
	inter.handleScript(text);
	in.close();
	return 0;
}