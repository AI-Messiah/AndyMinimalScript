#pragma once
#ifndef VARIABLES
#define VARIABLES
#include <functional>
#include <vector>
#include <string>

#include <map>
//#include "ProcessScript.h"
//#include <iterator>

#include "ErrorHandler.h"
namespace AndyInt {

	extern ErrorHandler ahand;

	struct aval {
		double value;
		bool defined;
	};

	struct varref {
		bool active;
		int scope;
		std::vector<aval> vals;
	};

	class Variables
	{
	public:
		int getRef(std::string name);
		void Create(std::string name, long double val, bool hasval, int pars);

		void IncScope();
		void DecScope();
		void ResetScope();
		void Set(int num, long double val, int par);

		double Get(int num, int par);
		aval SetGet(int num, int par);


		void clear();
	private:
		int cscope = 0;
		int curidx = 0;
		std::map<std::string, int> refs;
		std::vector<varref> vplas;

	};
}
#endif // !VARIABLES