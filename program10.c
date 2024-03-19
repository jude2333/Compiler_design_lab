#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function prototypes
int expression(char*);
int term(char*);
int factor(char*);


void skipWhitespace(char** input) {
    while (isspace(**input)) {
        (*input)++;
    }
}


int expression(char* input) {
    int result = term(input);

    while (*input == '+' || *input == '-') {
        char op = *input;
        input++;
        skipWhitespace(&input);

        if (op == '+') {
            result += term(input);
        } else {
            result -= term(input);
        }
    }

    return result;
}


int term(char* input) {
    int result = factor(input);

    while (*input == '*' || *input == '/') {
        char op = *input;
        input++;
        skipWhitespace(&input);

        if (op == '*') {
            result *= factor(input);
        } else {
            int divisor = factor(input);
            if (divisor != 0) {
                result /= divisor;
            } else {
                fprintf(stderr, "Error: Division by zero.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return result;
}


int factor(char* input) {
    int result;

    if (*input == '(') {
        input++;
        skipWhitespace(&input);
        result = expression(input);
        if (*input == ')') {
            input++;
            skipWhitespace(&input);
            return result;
        } else {
            fprintf(stderr, "Error: Missing closing parenthesis.\n");
            exit(EXIT_FAILURE);
        }
    } else if (isdigit(*input)) {
        result = 0;
        while (isdigit(*input)) {
            result = result * 10 + (*input - '0');
            input++;
        }
        skipWhitespace(&input);
        return result;
    } else {
        fprintf(stderr, "Error: Invalid input.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char input[100];

    // Input an arithmetic expression
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);

    // Parse and evaluate the expression
    int result = expression(input);
    printf("Result: %d\n", result);

    return 0;
}

