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
#include "LogicEngine.h"

using namespace std;



int main(){
    auto& varMap = (*VariableMap::instance);

    string input = "banana ^ grape";
    // cout << "Enter logic expression (e.g. A = B & C)";
    // TODO: use FileManager to read the file to get equation

    // Use Lexer to break down equation code into tokens
    vector<Token> tokens = Lexer::tokenize(input);
    cout << "Lexer passed" << endl;
    
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

    cout << "Start Parser" << endl;
    shared_ptr<Node> ast = Parser::buildAST(tokens);
    cout << "Parser passed" << endl;
    Parser::printAST(ast, 0);
    // try {
    //     bool result = LogicEngine::evaluate(ast, varMap);;
    //     cout << "LogicEngine passed" << endl;
    //     cout << "Expression: " << input << endl;
    //     cout << "Result: " << (result ? "True" : "False") << endl;
    // } catch (const exception& e) {
    //     cerr << "Error: " << e.what() << endl;
    // }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            varMap["banana"] = i != 0;
            varMap["grape"] = j != 0;
            cout << "banana: " << varMap["banana"] << ", grape: " << varMap["grape"] << endl;
            try {
                bool result = LogicEngine::evaluate(ast, varMap);
                cout << "LogicEngine passed" << endl;
                cout << "Expression: " << input << endl;
                cout << "Result: " << (result ? "True" : "False") << endl;
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }
    
    return EXIT_SUCCESS;
}


// int mainLogicEngine(){
//     string expr = "!(~A | ~B)";
//     auto root  = Parser::buildAST(expr);

//     // Define values for our variables
//     map<char, bool> myValues = {
//         {'A', false},
//         {'B', false}
//     };

//     for (int i = 0; i < 2; i++) {
//         for (int j = 0; j < 2; j++) {
//             myValues['A'] = i == 0;
//             myValues['B'] = j == 0;
//             // cout << "A: " << myValues['A'] << ", B: " << myValues['B'] << endl;
//             try {
//                 bool result = evaluate(root, myValues);
//                 cout << "Expression: " << expr << endl;
//                 cout << "Result: " << (result ? "True" : "False") << endl;
//             } catch (const exception& e) {
//                 cerr << "Error: " << e.what() << endl;
//             }
//         }
//     }
    
//     return 0;
// }



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