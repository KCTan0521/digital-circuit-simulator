#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cstdlib>
#include "Lexer.h"
#include "Token.h"
#include "VariableMap.h"
#include "Node.h"
#include "Parser.h"

using namespace std;



int main(){
    auto& varMap = (*VariableMap::instance);

    string input = "banana & !grape";
    // cout << "Enter logic expression (e.g. A = B & C)";
    // TODO: use FileManager to read the file to get equation

    // Use Lexer to break down equation code into tokens
    vector<Token> tokens = Lexer::tokenize(input);
    
    if (tokens.empty()) {
        cout << "Unable to detect tokens in the equation" << endl;
        return EXIT_FAILURE;
    }
    for (const auto& t : tokens) {
        if (t.type == TokenType::VARIABLE){
            // initialize variables in VariableMap
            varMap[t.value] = true;
        }
        // cout << "[" << t.value << "] ";
    }

    VariableMap::printVariableMap(varMap);

    // Parser::buildAST(tokens);

    // cout << "Hello from KC\n";
    return EXIT_SUCCESS;
}

// int mainAsm() {
//     int src = 100;
//     int dst;

//     asm ("movl %1, %%eax;"  // Move input to eax
//          "addl $5, %%eax;"  // Add 5
//          "movl %%eax, %0;"  // Move eax to output
//          : "=r" (dst)       // Output: %0
//          : "r" (src)        // Input: %1
//          : "%eax"           // Clobbered register
//     );

//     std::cout << "Result: " << dst << std::endl; // 15
// }