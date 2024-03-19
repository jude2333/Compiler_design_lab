#include <stdio.h>
#include <string.h>

typedef enum {
    PUSH, POP, ADD, SUB, MUL, DIV
} OpCode;

int generate_code(char *expr, int *code) {
    int i, j = 0;
    char op, arg1[10], arg2[10];

    for (i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            code[j++] = PUSH;
            code[j++] = expr[i] - '0';
        } else {
            op = expr[i];
            switch (op) {
                case '+':
                    code[j++] = POP;
                    strcpy(arg2, "");
                    code[j++] = POP;
                    strcpy(arg1, "");
                    code[j++] = ADD;
                    code[j++] = PUSH;
                    break;
                case '-':
                    code[j++] = POP;
                    strcpy(arg2, "");
                    code[j++] = POP;
                    strcpy(arg1, "");
                    code[j++] = SUB;
                    code[j++] = PUSH;
                    break;
                case '*':
                    code[j++] = POP;
                    strcpy(arg2, "");
                    code[j++] = POP;
                    strcpy(arg1, "");
                    code[j++] = MUL;
                    code[j++] = PUSH;
                    break;
                case '/':
                    code[j++] = POP;
                    strcpy(arg2, "");
                    code[j++] = POP;
                    strcpy(arg1, "");
                    code[j++] = DIV;
                    code[j++] = PUSH;
                    break;
            }
        }
    }

    code[j] = -1;
    return j;
}

int main() {
    char expr[100];
    int code[100], i, len;

    printf("Enter an expression: ");
    scanf("%s", expr);

    len = generate_code(expr, code);

    printf("Generated machine code:\n");
    for (i = 0; i < len; i++) {
        if (code[i] == PUSH)
            printf("PUSH %d\n", code[i + 1]);
        else if (code[i] == POP)
            printf("POP\n");
        else if (code[i] == ADD)
            printf("ADD\n");
        else if (code[i] == SUB)
            printf("SUB\n");
        else if (code[i] == MUL)
            printf("MUL\n");
        else if (code[i] == DIV)
            printf("DIV\n");
    }

    return 0;
}
