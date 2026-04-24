#include "Lexer.h"
#include <cctype> // for isspace, isalnum

std::vector<Token> Lexer::tokenize(std::string input) {
    std::vector<Token> tokens;
    int i = 0;
    int n = input.length();

    while (i < n) {
        char current = input[i];

        // 1. Skip whitespace
        if (std::isspace(current)) {
            i++;
            continue;
        }

        // 2. Handle Single-Character Operators
        if (current == '&') {
            tokens.push_back({TokenType::AND, "&"});
            i++;
        } else if (current == '|') {
            tokens.push_back({TokenType::OR, "|"});
            i++;
        } else if (current == '~') {
            tokens.push_back({TokenType::NOT, "~"});
            i++;
        } else if (current == '^') {
            tokens.push_back({TokenType::XOR, "^"});
            i++;
        } else if (current == '=') {
            tokens.push_back({TokenType::ASSIGN, "="});
            i++;
        } else if (current == '(') {
            tokens.push_back({TokenType::LPAREN, "("});
            i++;
        } else if (current == ')') {
            tokens.push_back({TokenType::RPAREN, ")"});
            i++;
        }
        
        // 3. Handle Multi-Character Variables (e.g., "Var1", "A", "B")
        else if (std::isalpha(current)) {
            std::string varName;
            // Keep reading as long as it's alphanumeric (A-Z or 0-9)
            while (i < n && std::isalnum(input[i])) {
                varName += input[i];
                i++;
            }
            tokens.push_back({TokenType::VARIABLE, varName});
        } 
        
        // 4. Handle Errors (Unknown characters)
        else {
            // For now, just skip or throw an error
            i++; 
        }
    }
    return tokens;
}