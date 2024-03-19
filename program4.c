#include <stdio.h>

int main() {
    char input[] = "This is a sample text.\nIt has multiple lines with\t\tspaces and tabs.";

    int whitespace_count = 0;
    int newline_count = 0;

    // Iterate through the input string
    for (int i = 0; input[i] != '\0'; i++) {
        // Check if the current character is whitespace (space or tab)
        if (input[i] == ' ' || input[i] == '\t') {
            whitespace_count++;
        }
        // Check if the current character is a newline character
        else if (input[i] == '\n') {
            newline_count++;
        }
    }

    printf("Number of whitespace characters: %d\n", whitespace_count);
    printf("Number of newline characters: %d\n", newline_count);

    return 0;
}

