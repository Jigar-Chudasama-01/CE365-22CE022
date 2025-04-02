#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>
#include <cmath>
#include <cctype>

using namespace std;

// Function to determine if a character is an operator
bool isOp(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to return operator precedence
int getPrecedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Function to check if a string is a numeric value
bool isNumeric(const string& str) {
    istringstream iss(str);
    double num;
    return (iss >> num) && iss.eof();
}

// Function to evaluate an operation between two numbers
double evaluate(double left, double right, char op) {
    switch (op) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        case '^': return pow(left, right);
        default: return 0;
    }
}

// Function to split the expression into tokens
vector<string> tokenizeExpr(const string& expr) {
    vector<string> tokens;
    string token;
    
    for (size_t i = 0; i < expr.size(); ++i) {
        char ch = expr[i];
        
        if (isspace(ch)) continue;
        
        if (isOp(ch) || ch == '(' || ch == ')') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, ch));
        } else {
            token += ch;
        }
    }
    
    if (!token.empty()) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Function to optimize an arithmetic expression using constant folding
string optimizeExpression(const string& expr) {
    vector<string> tokens = tokenizeExpr(expr);
    vector<string> output;
    stack<string> ops;
    
    for (const auto& token : tokens) {
        if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else if (isOp(token[0])) {
            while (!ops.empty() && ops.top() != "(" && getPrecedence(ops.top()[0]) >= getPrecedence(token[0])) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        } else {
            output.push_back(token);
        }
    }
    
    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }
    
    // Perform constant folding
    stack<string> evalStack;
    for (const auto& token : output) {
        if (isOp(token[0])) {
            if (evalStack.size() < 2) continue;
            
            string b = evalStack.top(); evalStack.pop();
            string a = evalStack.top(); evalStack.pop();
            
            if (isNumeric(a) && isNumeric(b)) {
                double valA = stod(a);
                double valB = stod(b);
                double result = evaluate(valA, valB, token[0]);
                evalStack.push(to_string(result));
            } else {
                evalStack.push("(" + a + " " + token + " " + b + ")");
            }
        } else {
            evalStack.push(token);
        }
    }
    
    return evalStack.empty() ? expr : evalStack.top();
}

int main() {
    string inputExpr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, inputExpr);
    
    string optimizedExpr = optimizeExpression(inputExpr);
    cout << "Original: " << inputExpr << endl;
    cout << "Optimized: " << optimizedExpr << endl;
    
    return 0;
}