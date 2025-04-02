#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

using namespace std;

unordered_map<char, vector<string>> rules;
unordered_map<char, unordered_set<char>> firstSet, followSet;
unordered_map<char, unordered_map<char, string>> parsingTable;
unordered_set<char> nonTerminals;

void computeFirst(char symbol);
void computeFollow(char symbol);
void buildParsingTable();
bool checkLL1();
bool parseInput(const string &input);

int main() {
    rules['S'] = {"XY", "Z"};
    rules['X'] = {"p", ""};
    rules['Y'] = {"q", ""};
    rules['Z'] = {"(S)", "r"};

    for (auto &entry : rules) {
        nonTerminals.insert(entry.first);
    }

    for (char nt : nonTerminals) {
        computeFirst(nt);
    }

    followSet['S'].insert('$');
    for (char nt : nonTerminals) {
        computeFollow(nt);
    }

    buildParsingTable();

    cout << "First Sets:\n";
    for (const auto &item : firstSet) {
        cout << "First(" << item.first << ") = { ";
        for (char ch : item.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }

    cout << "\nFollow Sets:\n";
    for (const auto &item : followSet) {
        cout << "Follow(" << item.first << ") = { ";
        for (char ch : item.second) {
            cout << ch << " ";
        }
        cout << "}\n";
    }

    cout << "\nParsing Table:\n";
    for (const auto &row : parsingTable) {
        for (const auto &col : row.second) {
            cout << "M[" << row.first << ", " << col.first << "] = " << col.second << "\n";
        }
    }

    if (checkLL1()) {
        cout << "\nGrammar is LL(1)." << endl;
    } else {
        cout << "\nGrammar is NOT LL(1)." << endl;
        return 0;
    }

    vector<string> testCases = {"pq", "p", "(pq)", "r", "(p)", "qq", "()", "(qr)", "pqrr", "q"};
    for (const string &test : testCases) {
        cout << "\nTesting: " << test << " -> ";
        cout << (parseInput(test) ? "Valid" : "Invalid") << endl;
    }

    return 0;
}

void computeFirst(char symbol) {
    if (!firstSet[symbol].empty()) return;

    for (const string &prod : rules[symbol]) {
        if (prod.empty()) {
            firstSet[symbol].insert('ε');
            continue;
        }

        for (char ch : prod) {
            if (!nonTerminals.count(ch)) {
                firstSet[symbol].insert(ch);
                break;
            } else {
                computeFirst(ch);
                firstSet[symbol].insert(firstSet[ch].begin(), firstSet[ch].end());
                if (firstSet[ch].count('ε') == 0) break;
            }
        }
    }
}

void computeFollow(char symbol) {
    for (const auto &entry : rules) {
        char lhs = entry.first;
        for (const string &rhs : entry.second) {
            for (size_t i = 0; i < rhs.size(); ++i) {
                if (rhs[i] == symbol) {
                    size_t j = i + 1;
                    while (j < rhs.size()) {
                        char next = rhs[j];
                        if (!nonTerminals.count(next)) {
                            followSet[symbol].insert(next);
                            break;
                        } else {
                            followSet[symbol].insert(firstSet[next].begin(), firstSet[next].end());
                            if (firstSet[next].count('ε') == 0) break;
                        }
                        j++;
                    }
                    if (j == rhs.size() || firstSet[rhs[j - 1]].count('ε')) {
                        followSet[symbol].insert(followSet[lhs].begin(), followSet[lhs].end());
                    }
                }
            }
        }
    }
}

void buildParsingTable() {
    for (char nt : nonTerminals) {
        for (const string &prod : rules[nt]) {
            unordered_set<char> firstTerminals;
            if (!prod.empty()) {
                firstTerminals.insert(prod[0]);
            }
            for (char terminal : firstTerminals) {
                parsingTable[nt][terminal] = prod;
            }
            if (firstTerminals.count('ε')) {
                for (char terminal : followSet[nt]) {
                    parsingTable[nt][terminal] = "ε";
                }
            }
        }
    }
}

bool checkLL1() {
    for (const auto &entry : parsingTable) {
        unordered_set<char> seen;
        for (const auto &cell : entry.second) {
            if (seen.count(cell.first)) {
                return false;
            }
            seen.insert(cell.first);
        }
    }
    return true;
}

bool parseInput(const string &input) {
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('S');
    size_t index = 0;
    string str = input + "$";

    while (!parseStack.empty()) {
        char top = parseStack.top();
        char current = str[index];
        parseStack.pop();

        if (top == current) {
            index++;
        } else if (parsingTable[top].count(current)) {
            string rule = parsingTable[top][current];
            for (auto it = rule.rbegin(); it != rule.rend(); ++it) {
                if (*it != 'ε') parseStack.push(*it);
            }
        } else {
            return false;
        }
    }
    return index == str.size() - 1;
}