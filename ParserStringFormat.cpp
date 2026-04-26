#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cctype>

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

// The Shunting Yard algorithm is a method for parsing mathematical expressions written in infix notation
// and converting them into postfix notation (also known as Reverse Polish Notation or RPN)
vector<string> shuntingYard(string expression) {
    vector<string> output;
    stack<char> opStack;

    for (int i = 0; i < expression.length(); i++){
        char c = expression[i];

        // Skip whitespace
        if (isspace(c)) continue;

        // If it's an operand (Variable/Letter), add to output
        if (isalnum(c)) {
            string operand(1, c);
            output.push_back(operand);
        }
        // Left parenthesis
        else if (c == '(') {
            opStack.push(c);       
        }
        // Right parenthesis
        else if (c == ')') {
            while(!opStack.empty() && opStack.top() != '('){
                output.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.pop(); // Remove '('
        }
        // Operator
        else if (isOperator(c)){
            while (!opStack.empty() && opStack.top() != '(' && precedence[opStack.top()] >= precedence[c]) {
                output.push_back(string(1, opStack.top()));
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    
    // Pop remaining operators
    while(!opStack.empty()){
        output.push_back(string(1, opStack.top()));
        opStack.pop();
    }

    return output;
}

int mainParserStringFormat(){
    string input = "~(A | B) & C";
    vector<string> postfix = shuntingYard(input);

    cout << "Infix: " << input << endl;
    cout << "Postfix: ";
    for (const string& s : postfix) {
        cout << s << " ";
    }
    cout << endl;


    return 0;
}
