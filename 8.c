#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define NO_RULE -1
#define EPSILON 'e'

char nonTerminals[MAX];
char terminals[MAX];
char parsingTable[MAX][MAX][MAX] = {""};
char rules[MAX][MAX];
int numNonTerminals, numTerminals, numRules;

// Function to get LL(1) Grammar from user
void getGrammar() {
    printf("Enter number of non-terminals: ");
    scanf("%d", &numNonTerminals);
    printf("Enter non-terminals: ");
    for (int i = 0; i < numNonTerminals; i++) {
        scanf(" %c", &nonTerminals[i]);
    }
    
    printf("Enter number of terminals: ");
    scanf("%d", &numTerminals);
    printf("Enter terminals (including '$' for end): ");
    for (int i = 0; i < numTerminals; i++) {
        scanf(" %c", &terminals[i]);
    }
    
    printf("Enter number of grammar rules: ");
    scanf("%d", &numRules);
    printf("Enter grammar rules in format (e.g., S->aAB):\n");
    for (int i = 0; i < numRules; i++) {
        scanf("%s", rules[i]);
    }
}

// Function to generate the predictive parsing table
void generateParsingTable() {
    memset(parsingTable, '-', sizeof(parsingTable));
    for (int i = 0; i < numRules; i++) {
        char nonTerminal = rules[i][0];
        char *production = strchr(rules[i], '>') + 1;

        for (int j = 0; j < numTerminals; j++) {
            if (production[0] == terminals[j] || production[0] == EPSILON) {
                for (int k = 0; k < numNonTerminals; k++) {
                    if (nonTerminals[k] == nonTerminal) {
                        strcpy(parsingTable[k][j], rules[i]);
                        break;
                    }
                }
            }
        }
    }
}

void displayGrammar() {
    printf("\nLL(1) Grammar:\n");
    for (int i = 0; i < numRules; i++) {
        printf("%s\n", rules[i]);
    }
}

void displayParsingTable() {
    printf("\nPredictive Parsing Table:\n");
    printf("\t");
    for (int i = 0; i < numTerminals; i++) printf("%c\t", terminals[i]);
    printf("\n");
    
    for (int i = 0; i < numNonTerminals; i++) {
        printf("%c\t", nonTerminals[i]);
        for (int j = 0; j < numTerminals; j++) {
            if (strcmp(parsingTable[i][j], "-") != 0)
                printf("%s\t", parsingTable[i][j]);
            else
                printf("-\t");
        }
        printf("\n");
    }
}

int isLL1Grammar() {
    for (int i = 0; i < numNonTerminals; i++) {
        for (int j = 0; j < numTerminals; j++) {
            if (strchr(parsingTable[i][j], '|')) {
                return 0; // Conflict found, grammar is not LL(1)
            }
        }
    }
    return 1; // Grammar is LL(1)
}

int validateString(char *input) {
    char stack[MAX] = "S$";
    int top = 1, i = 0;

    while (stack[top] != '$') {
        char X = stack[top--]; // Pop stack
        char a = input[i]; // Read input

        if (X == a) {
            i++; // Match and advance input
        } else {
            int row = -1, col = -1;
            for (int j = 0; j < numNonTerminals; j++) if (nonTerminals[j] == X) row = j;
            for (int j = 0; j < numTerminals; j++) if (terminals[j] == a) col = j;

            if (row == -1 || col == -1 || strcmp(parsingTable[row][col], "-") == 0)
                return 0; // No valid production

            char *production = strchr(parsingTable[row][col], '>') + 1;
            for (int j = strlen(production) - 1; j >= 0; j--) {
                if (production[j] != EPSILON)
                    stack[++top] = production[j];
            }
        }
    }
    return (input[i] == '\0');
}

int main() {
    getGrammar();
    generateParsingTable();
    displayGrammar();
    displayParsingTable();
    if (isLL1Grammar()) {
        printf("\nGrammar is LL(1)\n");
        char input[MAX];
        printf("Enter input string: ");
        scanf("%s", input);
        printf(validateString(input) ? "Valid string\n" : "Invalid string\n");
    } else {
        printf("\nGrammar is not LL(1)\n");
    }
    return 0;
}