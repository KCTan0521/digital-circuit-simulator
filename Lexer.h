#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>

class Lexer {
public:
    // This is the main function you will call
    static std::vector<Token> tokenize(std::string input);
};

#endif