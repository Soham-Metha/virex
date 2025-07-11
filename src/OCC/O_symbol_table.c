#include "O_symbol_table.h"
#include "univ_defs.h"

// Create a new symbol table, linking it to a parent scope (or NULL if global)
SymbolTable* createSymbolTable(SymbolTable* parent)
{
    SymbolTable* symTable = malloc(sizeof(SymbolTable));
    symTable->table = createHashTable(100, stringHashFunc, stringKeyCompare, stringKeyDestroy, free);
    symTable->parent = parent;
    return symTable;
}

// Destroy a symbol table (but does NOT free parent scope)
void destroySymbolTable(SymbolTable* symTable)
{
    destroyHashTable(symTable->table);
    free(symTable);
}

// Insert a symbol into the **current scope only**
void insertSymbol(SymbolTable* currentScope, const char* name, TokenType type, void* memAddress)
{
    if (!currentScope) {
        printf("Error: No active scope for insertion\n");
        exit(1);
    }

    // Check if symbol already exists in the current scope
    if (retrieve(currentScope->table, name)) {
        printf("Semantic error: Redeclaration of '%s' in the same scope\n", name);
        exit(1);
    }

    // Create symbol entry
    SymbolEntry* entry = malloc(sizeof(SymbolEntry));
    entry->identifier = strdup(name);
    entry->type = type;
    entry->memAddress = memAddress;

    insert(currentScope->table, entry->identifier, entry);
}

// Lookup a symbol in the current scope or any parent scope (recursive search)
SymbolEntry* lookupSymbol(SymbolTable* currentScope, const char* name)
{
    SymbolTable* scope = currentScope;
    while (scope) {
        SymbolEntry* entry = retrieve(scope->table, name);
        if (entry) {
            return entry;
        }
        scope = scope->parent;     // Move to parent scope
    }
    return NULL;     // Not found
}

// Update a symbol in the closest scope where it is declared
void updateSymbol(SymbolTable* currentScope, const char* name, void* memAddress)
{
    SymbolTable* scope = currentScope;
    while (scope) {
        SymbolEntry* entry = retrieve(scope->table, name);
        if (entry) {
            entry->memAddress = memAddress;
            return;
        }
        scope = scope->parent;     // Move to parent scope
    }
    printf("Semantic error: '%s' is not declared\n", name);
    exit(1);
}