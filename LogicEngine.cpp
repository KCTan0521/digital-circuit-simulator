#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>

#include "Lexer.h"
#include "Token.h"
#include "Node.h"
#include "Parser.h"


using namespace std;

bool evaluate(shared_ptr<Node> node, map<char, bool>& values) {
    if (!node) return false;

    // Leaf Node: It's an operand (A, B, 1, 0, etc.)
    if (!node->left && !node->right) {
        char val = node->value[0];
        if (val == '1') return true;
        if (val == '0') return false;

        // Look up variable in our map
        if (values.count(val)) {
            return values[val];
        }
        throw runtime_error("Variable value not provided: " + node->value);
    }

    // Operator Node: Evaluate children first
    char op = node->value[0];

    if (op == '~') { // Unary NOT
        return !evaluate(node->right, values);
    }

    // Binary operators
    bool leftVal = evaluate(node->left, values);
    bool rightVal = evaluate(node->right, values);

    switch (op) {
        case '&': return leftVal && rightVal;
        case '|': return leftVal || rightVal;
        case '^': return leftVal ^ rightVal;
        default: throw runtime_error("Unknown operator: " + node->value);
    }

}

int main(){
    string expr = "~(~A | ~B)";
    auto root  = Parser::buildAST(expr);

    // Define values for our variables
    map<char, bool> myValues = {
        {'A', false},
        {'B', false}
    };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            myValues['A'] = i == 0;
            myValues['B'] = j == 0;
            // cout << "A: " << myValues['A'] << ", B: " << myValues['B'] << endl;
            try {
                bool result = evaluate(root, myValues);
                cout << "Expression: " << expr << endl;
                cout << "Result: " << (result ? "True" : "False") << endl;
            } catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
        }
    }
    
    return 0;
}

int mainLogicEngine(){
    string expr = "~(A | B) & C";
    // string expr = "A & (B | C)";
    auto root = Parser::buildAST(expr);
    cout << "AST Structure:" << endl;
    Parser::printAST(root, 0);

    return 0;
    
}