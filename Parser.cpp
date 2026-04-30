#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cctype>
#include <memory>
#include "Node.h"
#include "Token.h"
#include "Parser.h"

using namespace std;

// 1. Define operator precedence
// Higher number = Higher precedence
map<TokenType, int> precedence = {
    {TokenType::NOT, 4}, // NOT
    {TokenType::AND, 3}, // AND
    {TokenType::XOR, 2}, // XOR
    {TokenType::OR, 1}  // OR
};

map<TokenType, string> symbolMap = {
    {TokenType::NOT, "~"}, // NOT
    {TokenType::AND, "&"}, // AND
    {TokenType::XOR, "^"}, // XOR
    {TokenType::OR, "|"}  // OR
};

void buildSubTree(stack<shared_ptr<Node>>& nodes, TokenType token) {
    // Safety check: ensure we have enough operands
    if (nodes.empty()) return;

    auto newNode = make_shared<Node>();
    newNode->type = token; // <--- FIX: Must set the type!

    // NOT is unary (1 child)
    if (token == TokenType::NOT) {
        newNode->right = nodes.top();
        nodes.pop();
    }
    // Binary operators (2 children)
    else {
        if (nodes.size() < 2) return; // Basic validation
        newNode->right = nodes.top(); nodes.pop();
        newNode->left = nodes.top(); nodes.pop();
    }
    nodes.push(newNode);
}

shared_ptr<Node> Parser::buildAST(const std::vector<Token> expression) {
    stack<shared_ptr<Node>> nodeStack;
    stack<TokenType> opStack;

    for (const Token& t : expression) {
        if (t.type == TokenType::VARIABLE || t.type == TokenType::LITERAL) {
            auto leaf = make_shared<Node>();
            leaf->type = t.type;
            leaf->varName = t.value; 
            nodeStack.push(leaf);
        }
        else if (t.type == TokenType::LPAREN) {
            opStack.push(t.type);
        }
        else if (t.type == TokenType::RPAREN) {
            while (!opStack.empty() && opStack.top() != TokenType::LPAREN) {
                buildSubTree(nodeStack, opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop(); // Pop the LPAREN
        }
        else if (precedence.count(t.type)) {
            while (!opStack.empty() && opStack.top() != TokenType::LPAREN && 
                   precedence[opStack.top()] >= precedence[t.type]) {
                buildSubTree(nodeStack, opStack.top());
                opStack.pop();
            }
            opStack.push(t.type); 
        }
    }

    // FIX: Process any remaining operators after the loop
    while (!opStack.empty()) {
        if (opStack.top() == TokenType::LPAREN) {
            // Optional: throw error for mismatched parens
            opStack.pop();
            continue;
        }
        buildSubTree(nodeStack, opStack.top());
        opStack.pop();
    }

    if (nodeStack.empty()) return nullptr;
    return nodeStack.top();
}
// shared_ptr<Node> Parser::buildAST (string expression){
//     stack<shared_ptr<Node>> nodeStack;
//     stack<char> opStack;

//     for (char c : expression) {
//         if (isspace(c)) continue;
        
//         if (isalnum(c)){
//             nodeStack.push(make_shared<Node>(string(1, c)));
//         }
//         else if (c == '('){
//             opStack.push(c);
//         }
//         else if (c == ')') {
//             while (!opStack.empty() && opStack.top() != '('){
//                 buildSubTree(nodeStack, opStack.top());
//                 opStack.pop();
//             }
//             opStack.pop();
//         }
//         else if (precedence.count(c)){
//             while (!opStack.empty() && opStack.top() != '(' && 
//                 precedence[opStack.top()] >= precedence[c]) {
//                 buildSubTree(nodeStack, opStack.top());
//                 opStack.pop();
//             }
//             opStack.push(c);
//         }
//     }
//     while (!opStack.empty()){
//         buildSubTree(nodeStack, opStack.top());
//         opStack.pop();
//     }

//     return nodeStack.top();
// }

// Simple recursive function to print the tree (for verification)
// void Parser::printAST(shared_ptr<Node> node, int depth = 0){
//     if (!node) return;
//     for (int i = 0; i < depth; i++) cout << " ";
//     cout << symbolMap.find(node->type)->second << endl;
//     printAST(node->left, depth + 1);
//     printAST(node->right, depth + 1);
// }

void Parser::printAST(shared_ptr<Node> node, int depth) {
    if (!node) return;

    // 1. Print indentation for tree structure
    for (int i = 0; i < depth; i++) cout << "  ";

    // 2. Determine what to print based on node type
    if (node->type == TokenType::VARIABLE || node->type == TokenType::LITERAL) {
        // For leaf nodes, print the actual value (e.g., "A", "B", "1")
        cout << node->varName << endl;
    } 
    else {
        // For operator nodes, look up the symbol (~, &, |, ^)
        auto it = symbolMap.find(node->type);
        if (it != symbolMap.end()) {
            cout << it->second << endl;
        } else {
            cout << "?" << endl; // Fallback for unknown types
        }
    }

    // 3. Recurse to children
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
}

// int mainParser(){
//     string expr = "~(A | B) & C";
//     // string expr = "A & (B | C)";
//     auto root = Parser::buildAST(expr);
//     cout << "AST Structure:" << endl;
//     Parser::printAST(root);
//     return 0;
// }
