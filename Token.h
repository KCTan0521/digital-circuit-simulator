#ifndef TOKEN_H
#define TOKEN_H

#include <string>

/*
TokenType categoizes the pieces of text the Lexer finds.
We use "enum class" because it's safe and prevents naming conflicts.
*/
enum class TokenType{
    VARIABLE, // Any name (e.g. A, B, C, Input1)
    AND,      // &
    OR,       // |
    NOT,      // ~
    XOR,      // ^
    ASSIGN,   // =
    LPAREN,   // (
    RPAREN,   // )
    LITERAL,  // 1 or 0, but this not fully supported
    UNKNOWN   // For erros or characters we don't recognize
};

/*
The Token struct is the "package" that holds the
category and the actual text found.
*/
struct Token {
    TokenType type;
    std::string value;

    // A handy constructor to make creating tokens easier in Lexer.cpp
    Token(TokenType t, std::string v) : type(t), value(v) {}
};

#endif
