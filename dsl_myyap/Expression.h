#pragma once
#include <string>
#include "InterpretatorArgs.h"

#ifndef EXPRESSION_H
#define EXPRESSION_H
class Expression
{
public:
	Expression(std::string type, int line);
	Expression(std::string type, std::string name, int line);
	~Expression() = default;
	std::string getType();
	std::string getName();
	virtual void action(const InterpretatorArgs& args) = 0;
	virtual std::string toString() const = 0;
private:
	std::string type;
	std::string name;
	int line;
};
#endif


