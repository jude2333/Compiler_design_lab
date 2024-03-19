#include <stdio.h>
#include <string.h>
#include <ctype.h>


int is_valid_identifier(char *identifier) {
   
    if (strlen(identifier) == 0) {
        return 0; 
    }

   
    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return 0; 
    }


    for (int i = 1; i < strlen(identifier); i++) {

        if (!isalpha(identifier[i]) && !isdigit(identifier[i]) && identifier[i] != '_') {
            return 0;
        }
    }

    
    char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
    };
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return 0; 
        }
    }

    return 1; 
}

int main() {
  
    char *identifiers[] = {"variable123", "_var", "123variable", "for", "Identifier", ""};
    int num_identifiers = sizeof(identifiers) / sizeof(identifiers[0]);

    // Iterate through the identifiers and check if they are valid
    for (int i = 0; i < num_identifiers; i++) {
        if (is_valid_identifier(identifiers[i])) {
            printf("%s is a valid identifier.\n", identifiers[i]);
        } else {
            printf("%s is not a valid identifier.\n", identifiers[i]);
        }
    }

    return 0;
}

