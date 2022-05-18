#pragma once

#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>

class Token {
private:
    std::string type;
    std::string name;
    int line;
    int pos;

public:
    Token(std::string type, std::string name, int line, int pos);
    std::string getType();
    std::string getName();
    int getPos();
    int getLine();
};
#endif