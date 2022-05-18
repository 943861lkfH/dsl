#pragma once

#include <list>
#include "Expression.h"
#include <iostream>

class Node
{
private:
    Expression* expression;
    std::list<Node*> children;

public:
    void printTree(int level);
    Node(Expression*);
    //Node(Expression*, std::list<Node*>&);
    ~Node();

    std::string getType();
    Expression* getExpression();

    void addChildFront(Node* child);
    void addChildBack(Node* child);

    std::list<Node*> getChildren();

    std::string toString(int gen = 0);
};

