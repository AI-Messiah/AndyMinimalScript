#pragma once
#include "Operators.h"

#include <string>
#include <map>


enum tokenType {
	Operator,
	Assignment
};
struct tokenProperty {
	tokenType type;
	bool internal;
	bool ambiguous;
};

class Maps
{
public:
	Maps();
	~Maps();
	std::string asdOps = "*=/=\\=+=-== ";
	std::map<std::string, tokenName> convertedTokens;
	std::map<tokenName, tokenProperty> convertedProperties;
	std::string mathOps = "^ * / \\ + - & | > < ==!=>=<=! &&||*=/=\\=+=-== ";
	int priority[22];
};

