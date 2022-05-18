#include "Token.h"
#include <stdlib.h>


Token::Token(std::string type, std::string name, int line, int pos) {
	this->type = type;
	this->name = name;
	this->line = line;
	this->pos = pos;
}

std::string Token::getType() {
	return this->type;
}

std::string Token::getName() {
	return this->name;
}

int Token::getPos() {
	return this->pos;
}

int Token::getLine() {
	return this->line;
}
