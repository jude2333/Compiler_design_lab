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


int find_common_prefix_length(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int prefix_length = 0;
    for (int i = 0; i < len1 && i < len2; i++) {
        if (str1[i] == str2[i]) {
            prefix_length++;
        } else {
            break;
        }
    }
    return prefix_length;
}
void eliminate_left_factoring(Production *prod) {
    // Find the common prefix length of all symbols
    int common_prefix_length = prod->num_symbols;
    for (int i = 1; i < prod->num_symbols; i++) {
        int prefix_length = find_common_prefix_length(prod->symbols, prod->symbols + i);
        if (prefix_length < common_prefix_length) {
            common_prefix_length = prefix_length;
        }
    }


    if (common_prefix_length > 0) {
        // Create a new non-terminal for the common prefix
        char new_non_terminal = prod->non_terminal + '\'';

        // Update the original production to remove the common prefix
        prod->num_symbols -= common_prefix_length;
        for (int i = 0; i < prod->num_symbols; i++) {
            prod->symbols[i] = prod->symbols[i + common_prefix_length];
        }

        // Create new productions for each alternative
        prod++;
        prod->non_terminal = new_non_terminal;
        prod->num_symbols = common_prefix_length;
        for (int i = 0; i < common_prefix_length; i++) {
            prod->symbols[i] = prod[-1].symbols[i];
        }
        prod++;
        prod->non_terminal = new_non_terminal;
        prod->num_symbols = 1;
        prod->symbols[0] = '|';
        for (int i = 0; i < prod[-1].num_symbols - common_prefix_length; i++) {
            prod->symbols[i + 1] = prod[-1].symbols[i + common_prefix_length];
        }
        prod++;
        prod->non_terminal = '\0'; // End marker
    }
}

// Function to print the productions
void print_productions(Production *productions) {
    printf("Productions after left factoring:\n");
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
        {'A', {'a', 'a', 'b', '|', 'a', 'a', 'c'}, 7},
        {'B', {'b', 'c', '|', 'b', 'd', '|', 'b', 'e'}, 8},
        {'\0', {}, 0} // End marker
    };

    // Apply left factoring for each production
    Production productions[MAX_PRODUCTIONS * 4]; // Max possible new productions = original_productions * 4
    Production *prod_ptr = productions;
    for (int i = 0; original_productions[i].non_terminal != '\0'; i++) {
        Production original_prod = original_productions[i];
        if (is_non_terminal(original_prod.symbols[0])) {
            eliminate_left_factoring(&original_prod);
        }
        *prod_ptr++ = original_prod;
    }
    prod_ptr->non_terminal = '\0'; // End marker for new productions

    // Print the productions after left factoring
    print_productions(productions);

    return 0;
}

