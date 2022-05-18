#include "Node.h"

Node::Node(Expression* expression){
    this->expression = expression;
}

//Node::Node(Expression* expression, std::list<Node*>& children) {
//    this->expression = expression;
//    this->children = children;
//}

Node::~Node() {
    delete expression;
    for (auto child : children) {
        delete child;
    }
}

std::string Node::getType() {
    return expression->getType();
}

void Node::addChildFront(Node* child) {
    children.push_front(child);
}

void Node::addChildBack(Node* child) {
    children.push_back(child);
}

std::list<Node*> Node::getChildren(){
    return children;
}

Expression* Node::getExpression(){
    return expression;
}

void Node::printTree(int level) {
    std::cout << '\n';
    for (int i = 0; i < 4 * level; i++)
        std::cout << " ";
    std::cout << this->expression->getName();
    for (auto i : children)
    {
        if (i == *children.begin())
            level++;
        i->printTree(level);
    }
}

std::string Node::toString(int gen){
    std::string tab;
    for (int i = 0; i <= gen; i++) {
        tab += "    ";
    }

    std::string res = expression->toString();
    for (auto node : children) {
        res += "\n" + tab + node->toString(gen + 1);
    }

    return res;
}