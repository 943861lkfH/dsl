#include "TokenType.h"

TokenType::TokenType(std::string type, std::regex regex) {
	this->type = type;
	this->regex = regex;
}

void TokenType::addListType() {
	this->tokens.emplace_back(new TokenType("FUNC_NAME", std::regex(R"(#function#)")));
	this->tokens.emplace_back(new TokenType("DIGIT", std::regex(R"(0|([1-9][0-9]*\.?[0-9]*))")));
	this->tokens.emplace_back(new TokenType("STRING", std::regex(R"(\"[0-9a-zA-Z\*\\/&\s]*\")")));
	this->tokens.emplace_back(new TokenType("IF_KW", std::regex(R"(if)")));
	this->tokens.emplace_back(new TokenType("ELSE_KW", std::regex(R"(else)")));
	this->tokens.emplace_back(new TokenType("WHILE_KW", std::regex(R"(while)")));
	this->tokens.emplace_back(new TokenType("L_BRACKET", std::regex(R"(\()")));
	this->tokens.emplace_back(new TokenType("R_BRACKET", std::regex(R"(\))")));
	this->tokens.emplace_back(new TokenType("L_BRACE", std::regex(R"(\{)")));
	this->tokens.emplace_back(new TokenType("R_BRACE", std::regex(R"(\})")));
	this->tokens.emplace_back(new TokenType("MORE_OP", std::regex(R"(>)")));
	this->tokens.emplace_back(new TokenType("LESS_OP", std::regex(R"(<)")));
	this->tokens.emplace_back(new TokenType("MINUS_OP", std::regex(R"(\-)")));
	this->tokens.emplace_back(new TokenType("EQUALS_OP", std::regex(R"(=)")));
	this->tokens.emplace_back(new TokenType("PLUS_OP", std::regex(R"(\+)")));
	this->tokens.emplace_back(new TokenType("MULTIPLY_OP", std::regex(R"(\*)")));
	this->tokens.emplace_back(new TokenType("DIVIDE_OP", std::regex(R"(\/)")));
	this->tokens.emplace_back(new TokenType("MULTIPLY_OP", std::regex(R"(\^)")));
	this->tokens.emplace_back(new TokenType("SEMICOLON_OP", std::regex(R"(;)")));
	this->tokens.emplace_back(new TokenType("INT_VAR", std::regex(R"(int)")));
	this->tokens.emplace_back(new TokenType("DOUBLE_VAR", std::regex(R"(double)")));
	this->tokens.emplace_back(new TokenType("STRING_VAR", std::regex(R"(string)")));
	this->tokens.emplace_back(new TokenType("VAR", std::regex(R"([a-z]+[a-zA-Z0-9_]*)")));
	this->tokens.emplace_back(new TokenType("OP_IF", std::regex(R"((&&)|(\|\|)|(==)|(>=)|(<=)|(<>))")));
	this->tokens.emplace_back(new TokenType("NONE", std::regex(R"(^$)")));
}