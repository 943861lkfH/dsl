#include "Lexer.h"
#include "Token.h"
#include "TokenType.h"
#include <regex>
#include <fstream>
#include <iostream>

Lexer::Lexer(std::string filename) {
	this->filename = filename;
}

std::list<Token*> Lexer::lexemAnalys() {
	t->addListType();

	std::ifstream file(this->filename);
	if (!file.is_open()) {
		file.close();
		std::cout << "can't open file ";
	}
	for (int i = 0; getline(file, this->code); i++)
	{
		this->line++;
		this->pos = 0;
		this->nextToken();
	}
	return this->tokenList;
}

void Lexer::nextToken() {
	std::string strValue = "";
	std::string oper = "";

	for (int i = 0; i < code.size(); i++)
	{
		if (!oper.empty()) {
			std::string twoOper = oper;
			twoOper += code[i];
			if (checkToken(twoOper, line, pos)) {
				pos += 2;
				oper = "\0";
				continue;
			}
			checkToken(oper, line, pos);
			pos++;
			oper = "\0";
		}

		if (checkOneChar(code[i]))
		{
			if (!strValue.empty())
			{
				checkToken(strValue, line, pos);
				pos += strValue.size();
				strValue = "";
			}
			oper = code[i];
			if (i == code.size() - 1)
				checkToken(oper, line, pos);
			continue;
		}
		else if (std::regex_match(strValue, std::regex(R"("[^"]*)"))) {
			strValue += code[i];
			continue;
		}
		else if (checkWhitespace(code[i]))
		{
			if (!strValue.empty())
			{
				checkToken(strValue, this->line, this->pos);
				pos += strValue.size();
			}
			strValue = "";
			pos++;
			continue;
		}
		else {
			strValue += code[i];
			if (i == code.size() - 1)
				checkToken(strValue, this->line, this->pos);
		}
	}
}

bool Lexer::checkToken(std::string str, int line, int pos) {

	for (auto token : t->tokens)
	{
		if (std::regex_match(str, token->regex)) {
			tokenList.emplace_back(new Token(token->type, str, line, pos));
			return true;
		}
	}
	//std::cerr << "token is incorrect $this->pos"; // ÝÒÎ ÍÓÆÍÎ ÏÅÐÅÌÅÑÒÈÒÜ Â ÄÐÓÃÓÞ ×ÀÑÒÜ ÊÎÄÀ, È ÏÐÎÂÅÐßÒÜ TYPE = NONE
	//throw "token is incorrect $this->pos";
	//tokenList.emplace_back(new Token("NONE", str, line, pos));
	return false;
}

bool Lexer::checkOneChar(char str) {
	if ((str == ';')
		|| (str == '-') || (str == '+')
		|| (str == '*') || (str == '/')
		|| (str == '^') || (str == '=')
		|| (str == '(') || (str == ')')
		|| (str == '{') || (str == '}')
		|| (str == '>') || (str == '<')
		|| (str == '&') || (str == '|'))
		return true;
	return false;
}

bool Lexer::checkWhitespace(char str) {
	if ((str == '\n') || (str == '\t') || (str == ' '))
		return true;
	return false;
}