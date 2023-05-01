#pragma once
#include <string>
#include <vector>
#include <random>
#include <immintrin.h>
#include <stdint.h>
#include <cmath>
#include <functional>
#include "Variables.h"
namespace AndyInt {
	class Transit
	{
	public:
		Transit();
		~Transit();
		std::string oFunNames[16];
		int intlookup(std::string name);
		int extlookup(std::string name);
		double calFun(int funval, double pasval);
		double callext(int num, std::vector<double> args);
		void setFunction(std::string name, std::function<double(std::vector<double>)> address);
		std::vector<std::string> funNames;
	private:
		std::vector<std::function<double(std::vector<double>)>> ops;

		double distRand();
		uint64_t rdrand64();
		double myRand();
	};
}

	

