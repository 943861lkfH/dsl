#include "ExpBody.h"

ExpBody::ExpBody(std::string name, int line) :Expression("body", name, line) {
    this->name = name;
}

std::string ExpBody::toString() const {
    return name;
}