#pragma once

#ifndef LEXER_H
#define LEXER_H
#include "Token.h"
#include <regex>

class Lexer final {

public:
	std::list<Token*> tokenList;
	Lexer(std::string filename);
	~Lexer() = default;
	std::list<Token*> lexemAnalys();
	void nextToken();
private:
	std::string code;
	std::string filename;
	int pos;
	int line = 0;
	bool checkToken(std::string str, int line, int pos);
	TokenType* t = new TokenType();
	bool checkOneChar(char str);
	bool checkWhitespace(char str);
};
#endif