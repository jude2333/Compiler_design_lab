#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50
#define MAX_CONSTANT_LENGTH 10

bool isOperator(char ch) {
    char operators[] = "+-*/=";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return true;
        }
    }
    return false;
}

bool isWhitespace(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n');
}


void analyzeInput(char input[]) {
    int len = strlen(input);
    int i = 0;
    while (i < len) {
        if (isWhitespace(input[i])) {
            i++;
            continue;
        }
        if (input[i] == '/' && input[i+1] == '/') {
            break;
        }

        if (isalpha(input[i])) {
            char identifier[MAX_IDENTIFIER_LENGTH];
            int j = 0;
            while (isalpha(input[i]) || isdigit(input[i]) || input[i] == '_') {
                identifier[j++] = input[i++];
            }
            identifier[j] = '\0';
            printf("Identifier: %s\n", identifier);
        }
        else if (isdigit(input[i])) {
            char constant[MAX_CONSTANT_LENGTH];
            int j = 0;
            while (isdigit(input[i])) {
                constant[j++] = input[i++];
            }
            constant[j] = '\0';
            printf("Constant: %s\n", constant);
        }

        else if (isOperator(input[i])) {
            printf("Operator: %c\n", input[i++]);
        }
        else {
            
            i++;
        }
    }
}

int main() {
    char input[1000];
    printf("Enter input:\n");
    fgets(input, sizeof(input), stdin);
    analyzeInput(input);
    return 0;
}

