#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Define C keywords
unordered_set<string> keywords = {"int", "char", "return", "if", "else", "while", "for", "break", "continue"};

// Define operators and punctuation
unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!'};
unordered_set<char> punctuation = {';', ',', '{', '}', '(', ')'};
unordered_map<string, int> symbolTable;

// Function to check if a word is a keyword
bool isKeyword(const string &word) {
    return keywords.count(word) > 0;
}

// Function to check if the token is a valid identifier
bool isIdentifier(const string &token) {
    if (isdigit(token[0])) return false;
    for (char ch : token) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

// Function to validate and categorize the token
void processToken(const string &token, int lineNum, vector<string> &tokens, vector<string> &errors) {
    if (token.empty()) return;

    // Identifying the token type
    if (isKeyword(token)) {
        tokens.push_back("Keyword: " + token);
    } else if (isdigit(token[0])) {
        bool validConstant = true;
        for (char c : token) {
            if (!isdigit(c)) {
                validConstant = false;
                break;
            }
        }
        validConstant ? tokens.push_back("Constant: " + token) :
                        errors.push_back("Line " + to_string(lineNum) + ": " + token + " invalid lexeme");
    } else if (isIdentifier(token)) {
        tokens.push_back("Identifier: " + token);
        symbolTable[token]++;
    } else {
        errors.push_back("Line " + to_string(lineNum) + ": " + token + " invalid identifier");
    }
}

// Main lexical analyzer function
void lexicalAnalyzer(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open file." << endl;
        return;
    }

    vector<string> tokens;
    vector<string> errors;
    string currentToken = "";
    char currentChar;
    int lineNum = 1;
    bool inComment = false;

    while (file.get(currentChar)) {
        // Handle newlines
        if (currentChar == '\n') {
            lineNum++;
            continue;
        }

        // Comment processing
        if (inComment) {
            if (currentChar == '*' && file.peek() == '/') {
                file.get(currentChar);
                inComment = false;
            }
            continue;
        }
        if (currentChar == '/' && file.peek() == '*') {
            file.get(currentChar);
            inComment = true;
            continue;
        }
        if (currentChar == '/' && file.peek() == '/') {
            while (file.get(currentChar) && currentChar != '\n');
            lineNum++;
            continue;
        }

        // Token processing
        if (isalnum(currentChar) || currentChar == '_') {
            currentToken += currentChar;
        } else {
            processToken(currentToken, lineNum, tokens, errors);
            currentToken = "";

            if (operators.count(currentChar)) {
                tokens.push_back("Operator: " + string(1, currentChar));
            } else if (punctuation.count(currentChar)) {
                tokens.push_back("Punctuation: " + string(1, currentChar));
            } else if (!isspace(currentChar)) {
                errors.push_back("Line " + to_string(lineNum) + ": " + string(1, currentChar) + " invalid character");
            }
        }
    }

    // Process last token if present
    processToken(currentToken, lineNum, tokens, errors);

    file.close();

    // Output tokens
    cout << "TOKENS\n";
    for (const auto &token : tokens) {
        cout << token << endl;
    }

    // Output errors if any
    if (!errors.empty()) {
        cout << "\nLEXICAL ERRORS\n";
        for (const auto &error : errors) {
            cout << error << endl;
        }
    }

    // Output symbol table
    cout << "\nSYMBOL TABLE ENTRIES\n";
    int idx = 1;
    for (const auto &entry : symbolTable) {
        cout << idx++ << ") " << entry.first << endl;
    }
}

int main() {
    string filename = "1.c"; // Provide your C file name here
    lexicalAnalyzer(filename);
    return 0;
}
