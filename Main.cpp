#include <iostream>
#include <vector>
#include <string>
#include "Lexer.h"
#include "Token.h"

using namespace std;

int main2 (){
    string input = "apple = banana & !grape";
    // cout << "Enter logic expression (e.g. A = B & C)";
    // getline(cin, input);

    // Call the static function: ClassName::FunctionName
    vector<Token> tokens = Lexer::tokenize(input);

    // Let's print  the tokens to see if  it worked!
    cout << "\nTokens found:" << endl;
    for (const auto& t : tokens) {
        // Since TokenType is an enum class, we can't print it directly easily
        // so we just print the string value we captured.
        cout << "[" << t.value << "] ";
    }
    cout << std::endl;

    cout << "Hello from KC\n";
    return 0;
}
