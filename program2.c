#include <stdio.h>
#include <string.h>


int check_comment(const char *line) {
   
    while (*line == ' ' || *line == '\t') {
        line++;
    }

    if (strncmp(line, "//", 2) == 0) {
        return 1; 
    }

    if (strncmp(line, "/*", 2) == 0) {

        const char *end_comment = strstr(line, "*/");
        if (end_comment != NULL) {
            return 2; 
        } else {
            return 3; 
        }
    }


    return 0;
}

int main() {

    const char *lines[] = {
        "int x = 5; // This is a single-line comment",
        "/* This is a multi-line comment */",
        "/* This is a multi-line comment that is not closed",
        "// This is a single-line comment inside a multi-line comment */",
        "This is not a comment"
    };

    for (int i = 0; i < 5; i++) {
        int result = check_comment(lines[i]);
        if (result == 1) {
            printf("Line %d: Single-line comment\n", i + 1);
        } else if (result == 2) {
            printf("Line %d: Multi-line comment\n", i + 1);
        } else if (result == 3) {
            printf("Line %d: Multi-line comment not closed\n", i + 1);
        } else {
            printf("Line %d: Not a comment\n", i + 1);
        }
    }

    return 0;
}

