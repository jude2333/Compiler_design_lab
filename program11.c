#include <stdio.h>
#include <string.h>
#include <math.h>

double evaluate(char expr[], int len) {
    double stack[100];
    int top = -1;
    int i, op1, op2;
    char op;

    for (i = 0; i < len; i++) {
        if (expr[i] >= '0' && expr[i] <= '9') {
            stack[++top] = expr[i] - '0';
        } else {
            op2 = stack[top--];
            op1 = stack[top--];
            op = expr[i];

            switch (op) {
                case '+':
                    stack[++top] = op1 + op2;
                    break;
                case '-':
                    stack[++top] = op1 - op2;
                    break;
                case '*':
                    stack[++top] = op1 * op2;
                    break;
                case '/':
                    stack[++top] = op1 / op2;
                    break;
                case '^':
                    stack[++top] = pow(op1, op2);
                    break;
            }
        }
    }

    return stack[top];
}

int main() {
    char expr[100];
    printf("Enter an expression: ");
    scanf("%s", expr);
    printf("Result: %.2lf\n", evaluate(expr, strlen(expr)));
    return 0;
}
