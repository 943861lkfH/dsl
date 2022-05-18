#include "ExpFunc.h"

ExpFunc::ExpFunc(std::string name, std::list<Node*> arguments, int line) :Expression("func", line) {
	this->name = name;
	this->arguments = arguments;
}