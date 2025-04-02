#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Quad {
    string operation;
    string operand1;
    string operand2;
    string result;
};

bool isOperator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

int getPrecedence(char symbol) {
    if (symbol == '+' || symbol == '-') return 1;
    if (symbol == '*' || symbol == '/') return 2;
    if (symbol == '^') return 3;
    return 0;
}

string convertToPostfix(const string& expression) {
    stack<char> opStack;
    string postfix;

    for (size_t i = 0; i < expression.length(); i++) {
        char symbol = expression[i];

        if (isdigit(symbol) || symbol == '.') {
            string number;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                number += expression[i++];
            }
            --i;
            postfix += number + " ";
        }
        else if (symbol == '(') {
            opStack.push(symbol);
        }
        else if (symbol == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.pop();
        }
        else if (isOperator(symbol)) {
            while (!opStack.empty() && getPrecedence(opStack.top()) >= getPrecedence(symbol)) {
                postfix += opStack.top();
                postfix += " ";
                opStack.pop();
            }
            opStack.push(symbol);
        }
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        postfix += " ";
        opStack.pop();
    }

    return postfix;
}

vector<Quad> createQuadruples(const string& postfix) {
    stack<string> valueStack;
    vector<Quad> quads;
    int tempVarCount = 1;

    istringstream stream(postfix);
    string token;

    while (stream >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            valueStack.push(token);
        }
        else if (isOperator(token[0])) {
            string second = valueStack.top(); valueStack.pop();
            string first = valueStack.top(); valueStack.pop();
            string temp = "T" + to_string(tempVarCount++);
            
            quads.push_back({token, first, second, temp});
            valueStack.push(temp);
        }
    }

    return quads;
}

void showQuadruples(const vector<Quad>& quads) {
    cout << "\nQuadruple Representation:\n";
    cout << left << setw(12) << "Operation" << setw(12) << "Operand1" << setw(12) << "Operand2" << setw(12) << "Result" << endl;
    cout << "--------------------------------------------------" << endl;

    for (const auto& q : quads) {
        cout << left << setw(12) << q.operation
             << setw(12) << q.operand1
             << setw(12) << q.operand2
             << setw(12) << q.result << endl;
    }
}

int main() {
    string expr;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expr);
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    string postfixExpr = convertToPostfix(expr);
    cout << "\nPostfix Form: " << postfixExpr << endl;

    vector<Quad> quads = createQuadruples(postfixExpr);
    showQuadruples(quads);

    return 0;
}