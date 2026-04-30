#ifndef NODE_H
#define NODE_H

#include "Token.h"
#include <string>
#include <memory>

using namespace std;

struct Node {
    TokenType type;
    string varName; // Only applicable to TokenType::VARIABLE
    shared_ptr<Node> left, right;
    Node() : type(TokenType::UNKNOWN), varName(""), left(nullptr), right(nullptr) {}
};

#endif