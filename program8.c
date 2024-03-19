#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 100

typedef struct SymbolEntry {
    char name[50];
    int value;
    struct SymbolEntry* next;
} SymbolEntry;

SymbolEntry* symbolTable[TABLE_SIZE];


int hash(char* name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % TABLE_SIZE;
}


void insert(char* name, int value) {
    int index = hash(name);
    
    SymbolEntry* newEntry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    strcpy(newEntry->name, name);
    newEntry->value = value;
    newEntry->next = NULL;
    
    if (symbolTable[index] == NULL) {
        symbolTable[index] = newEntry;
    } else {
        SymbolEntry* current = symbolTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }
}


SymbolEntry* search(char* name) {
    int index = hash(name);
    
    SymbolEntry* current = symbolTable[index];
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteSymbol(char* name) {
    int index = hash(name);
    
    SymbolEntry* current = symbolTable[index];
    SymbolEntry* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                symbolTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Function to print the symbol table
void printTable() {
    printf("Symbol Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        SymbolEntry* current = symbolTable[i];
        while (current != NULL) {
            printf("%s -> %d\n", current->name, current->value);
            current = current->next;
        }
    }
}

int main() {
    // Initialize symbol table
    for (int i = 0; i < TABLE_SIZE; i++) {
        symbolTable[i] = NULL;
    }
    
    // Perform symbol table operations
    insert("x", 10);
    insert("y", 20);
    insert("z", 30);
    
    printf("After insertion:\n");
    printTable();
    
    SymbolEntry* result = search("y");
    if (result != NULL) {
        printf("Value of y: %d\n", result->value);
    } else {
        printf("Symbol y not found.\n");
    }
    
    deleteSymbol("y");
    
    printf("After deletion:\n");
    printTable();
    
    return 0;
}

