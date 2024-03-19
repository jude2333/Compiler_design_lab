#include <stdio.h>
#include <string.h>

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char res[10];
} ThreeAddrCode;

ThreeAddrCode code[100];
int index = 0;

void generate(char op, char arg1[], char arg2[], char res[]) {
    strcpy(code[index].arg1, arg1);
    strcpy(code[index].arg2, arg2);
    strcpy(code[index].res, res);
    code[index].op = op;
    index++;
}

int main() {
    char expr[100];
    printf("Enter an expression: ");
    scanf("%s", expr);

    int i, j, k;
    char temp[10];

    for (i = 0; expr[i] != '\0'; i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            temp[0] = expr[i];
            temp[1] = '\0';
            generate('=', temp, "", temp);
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            sprintf(temp, "t%d", index);
            j = i - 1;
            k = i + 1;
            while (j >= 0 && expr[j] >= '0' && expr[j] <= '9') j--;
            while (k < strlen(expr) && expr[k] >= '0' && expr[k] <= '9') k++;

            // Check for common subexpressions
            int found = 0;
            for (int l = 0; l < index; l++) {
                if (code[l].op == expr[i] &&
                    !strcmp(code[l].arg1, expr + j + 1) &&
                    !strcmp(code[l].arg2, expr + i + 1)) {
                    strcpy(temp, code[l].res);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                generate(expr[i], expr + j + 1, expr + i + 1, temp);
            }

            i = k - 1;
        }
    }

    printf("Optimized Three Address Code:\n");
    for (i = 0; i < index; i++) {
        printf("%s = %s %c %s\n", code[i].res, code[i].arg1, code[i].op, code[i].arg2);
    }

    return 0;
}
