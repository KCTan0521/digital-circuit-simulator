#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cctype>
#include <memory>
#include "Node.h"
#include "Parser.h"

using namespace std;

// 1. Define operator precedence
// Higher number = Higher precedence
map<char, int> precedence = {
    {'~', 4}, // NOT
    {'!', 4}, // NOT
    {'&', 3}, // AND
    {'^', 2}, // XOR
    {'|', 1}  // OR
};

bool isOperator(char c){
    return precedence.count(c);
}

void buildSubTree(stack<shared_ptr<Node>>& nodes, char op){
    auto newNode = make_shared<Node>(string(1, op));

    // NOT is unary (1 child)
    if (op == '~'){
        newNode->right = nodes.top();
        nodes.pop();
    }
    // AND, OR, XOR are binary (2 children)
    else{
        newNode->right = nodes.top(); nodes.pop();
        newNode->left = nodes.top(); nodes.pop();
    }
    nodes.push(newNode);
}

shared_ptr<Node> Parser::buildAST (string expression){
    stack<shared_ptr<Node>> nodeStack;
    stack<char> opStack;

    for (char c : expression) {
        if (isspace(c)) continue;
        
        if (isalnum(c)){
            nodeStack.push(make_shared<Node>(string(1, c)));
        }
        else if (c == '('){
            opStack.push(c);
        }
        else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '('){
                buildSubTree(nodeStack, opStack.top());
                opStack.pop();
            }
            opStack.pop();
        }
        else if (precedence.count(c)){
            while (!opStack.empty() && opStack.top() != '(' && 
                precedence[opStack.top()] >= precedence[c]) {
                buildSubTree(nodeStack, opStack.top());
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()){
        buildSubTree(nodeStack, opStack.top());
        opStack.pop();
    }

    return nodeStack.top();
}

// Simple recursive function to print the tree (for verification)
void Parser::printAST(shared_ptr<Node> node, int depth = 0){
    if (!node) return;
    for (int i = 0; i < depth; i++) cout << " ";
    cout << node->value << endl;
    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
}


int mainParser(){
    string expr = "~(A | B) & C";
    // string expr = "A & (B | C)";
    auto root = Parser::buildAST(expr);
    cout << "AST Structure:" << endl;
    Parser::printAST(root);
    return 0;
}
