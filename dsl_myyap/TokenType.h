#pragma once

#include <list>
#include <regex>

class TokenType
{
public:
	std::string type;
	std::regex regex;
	std::list<TokenType*> tokens;
	TokenType(std::string type, std::regex regex);
	void addListType();
	TokenType() {};
};

