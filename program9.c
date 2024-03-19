#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


bool isValidGrammar(char* input) {

    int len = strlen(input);
    if (len < 2 || input[len - 1] != '.') {
        return false;
    }
    for (int i = 0; i < len - 1; i++) {
        if (!islower(input[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    // Test the function with sample input strings
    char input1[] = "abc."; // Valid input string
    char input2[] = "Abc."; // Invalid input string (uppercase letter)
    char input3[] = "abc";  // Invalid input string (missing period)

    // Check each input string against the grammar
    printf("%s is %s\n", input1, isValidGrammar(input1) ? "valid" : "invalid");
    printf("%s is %s\n", input2, isValidGrammar(input2) ? "valid" : "invalid");
    printf("%s is %s\n", input3, isValidGrammar(input3) ? "valid" : "invalid");

    return 0;
}

