#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10


typedef struct {
    char non_terminal;
    char symbols[MAX_SYMBOLS];
    int num_symbols;
} Production;


int is_non_terminal(char symbol) {
    return isupper(symbol);
}


void eliminate_left_recursion(Production *prod) {
    char new_non_terminal = prod->non_terminal + '\'';
    int num_original_symbols = prod->num_symbols;

    
    int num_left_recursive_symbols = 0;
    char left_recursive_symbols[MAX_SYMBOLS];
    char non_left_recursive_symbols[MAX_SYMBOLS];
    for (int i = 0; i < num_original_symbols; i++) {
        char symbol = prod->symbols[i];
        if (symbol == prod->non_terminal) {
            left_recursive_symbols[num_left_recursive_symbols++] = symbol;
        } else {
            non_left_recursive_symbols[i - num_left_recursive_symbols] = symbol;
        }
    }

    prod->num_symbols = num_left_recursive_symbols;
    for (int i = 0; i < num_left_recursive_symbols; i++) {
        prod->symbols[i] = left_recursive_symbols[i];
    }
    prod++;

    prod->non_terminal = new_non_terminal;
    prod->num_symbols = 2;
    prod->symbols[0] = '$'; // Epsilon symbol
    for (int i = 0; i < num_left_recursive_symbols; i++) {
        prod->symbols[i + 1] = left_recursive_symbols[i];
    }
    prod++;

    prod->non_terminal = new_non_terminal;
    prod->num_symbols = num_original_symbols + 1 - num_left_recursive_symbols;
    for (int i = 0; i < prod->num_symbols; i++) {
        prod->symbols[i] = non_left_recursive_symbols[i];
    }
    prod++;

    prod->non_terminal = '\0'; // End of productions marker
}

// Function to print the productions
void print_productions(Production *productions) {
    printf("Productions after left recursion elimination:\n");
    for (int i = 0; productions[i].non_terminal != '\0'; i++) {
        printf("%c -> ", productions[i].non_terminal);
        for (int j = 0; j < productions[i].num_symbols; j++) {
            printf("%c", productions[i].symbols[j]);
        }
        printf("\n");
    }
}

int main() {
    // Define the original productions (example grammar)
    Production original_productions[] = {
        {'A', {'A', 'B', '|', 'C'}, 4},
        {'B', {'B', 'a', '|', 'b'}, 4},
        {'C', {'c', '|', 'd'}, 3},
        {'\0', {}, 0} // End marker
    };

    
    Production productions[MAX_PRODUCTIONS * 4]; 
    Production *prod_ptr = productions;
    for (int i = 0; original_productions[i].non_terminal != '\0'; i++) {
        Production original_prod = original_productions[i];
        if (is_non_terminal(original_prod.symbols[0])) {
            eliminate_left_recursion(&original_prod);
        }
        *prod_ptr++ = original_prod;
    }
    prod_ptr->non_terminal = '\0'; 

    print_productions(productions);

    return 0;
}

