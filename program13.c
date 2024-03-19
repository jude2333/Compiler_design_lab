#include <stdio.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char c;
    int char_count = 0, word_count = 0, line_count = 1;
    int inword = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        char_count++;

        if (isspace(c)) {
            inword = 0;
        } else if (!inword) {
            inword = 1;
            word_count++;
        }

        if (c == '\n') {
            line_count++;
        }
    }

    fclose(fp);

    printf("Characters: %d\n", char_count);
    printf("Words: %d\n", word_count);
    printf("Lines: %d\n", line_count);

    return 0;
}
