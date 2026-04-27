#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include "Token.h"
#include "Node.h"

class Parser {
public:
    static std::shared_ptr<Node> buildAST(std::string expression);

    // Declare the helper function
    static void printAST(std::shared_ptr<Node> node, int depth);
};

#endif
