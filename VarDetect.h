#pragma once
#include "ascii.h"
#include "Operators.h"
#include "Globalize.h"
#include <cerrno>
#include <cfenv>

namespace AndyInt {
	enum valType {
		typeNone,
		typeNum,
		typeVar,
		typeNode,
		typeIntern,
		typeExtern,
		typeFunc
	};

	class VarDetect
	{
	public:
		bool isAccepted(std::string text, int pla);
		void clear();
		varinc getVal();
		double getNum();
		std::string varnam;
		bool neg = false;
		valType type = typeNone;
		valType type1 = typeNone;
		double val = 0;
		bool node = false;
		bool Uord = false;
		int funval = -1;
		int fstpla = 0;
		int sid = 0;
	private:
		void hantext(std::string aprt);
		void haniden();
		void changType();		
		bool hasiden = false;
		bool hasspa = false;
		bool decimal = false;
		bool numneg = false;
		bool expneg = false;
		bool hase = false;
		int dplas = 0;
		int exp = 0;
		
		strmeth meth;


	};
}

