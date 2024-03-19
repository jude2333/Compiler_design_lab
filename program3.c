#include <stdio.h>
#include <string.h>

// Function to check if a given string is an arithmetic operator
int is_arithmetic_operator(char *token) {
    // List of valid arithmetic operators
    char *operators[] = {"+", "-", "*", "/"};
    int num_operators = sizeof(operators) / sizeof(operators[0]);

    // Loop through the list of operators and compare with the given token
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return 1; // Token is an arithmetic operator
        }
    }

    return 0; // Token is not an arithmetic operator
}

int main() {
    // Test the function with sample tokens
    char *tokens[] = {"+", "-", "*", "/", "(", ")", "="};
    int num_tokens = sizeof(tokens) / sizeof(tokens[0]);

    // Iterate through the tokens and check if they are arithmetic operators
    for (int i = 0; i < num_tokens; i++) {
        if (is_arithmetic_operator(tokens[i])) {
            printf("%s is an arithmetic operator.\n", tokens[i]);
        } else {
            printf("%s is not an arithmetic operator.\n", tokens[i]);
        }
    }

    return 0;
}

