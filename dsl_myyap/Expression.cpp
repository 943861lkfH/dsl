#include "Expression.h"


Expression::Expression(std::string type, int line) {
	this->type = type;
	this->line = line;
}

Expression::Expression(std::string type, std::string name, int line) {
	this->type = type;
	this->name = name;
	this->line = line;
}

std::string Expression::getType() {
	return type;
}

std::string Expression::getName() {
	return name;
}
