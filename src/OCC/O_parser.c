#include "O_parser.h"
#include "O_debug_help.h"
#include "O_parse_tree.h"
#include "O_symbol_table.h"
#include "O_token_types.h"
#include "univ_defs.h"

#pragma GCC diagnostic ignored "-Wswitch-enum"
/* match: Verifies that the current token matches the expected type.
   Advances the token pointer if successful; otherwise, exits with an error.
*/
Token* match(Token** currentToken, TokenType expectedType)
{
    if ((*currentToken)->type == expectedType) {
        Token* matchedToken = *currentToken;
        (*currentToken)++;
        return matchedToken;
    } else {
        printf("Syntax error: Expected token type %s but found %s at line %zu\n",
            StrTokenType[expectedType], StrTokenType[(*currentToken)->type], (*currentToken)->lineNum);
        exit(1);
    }
}

/* Expression Parsing */

// parsePrimaryExpr: Handles "(" Expression ")" | Identifier | INT_L | FLOAT_L | CHAR_L | STR_L
ParseTreeNode* parsePrimaryExpr(Token** currentToken, SymbolTable* symTable)
{
    if ((*currentToken)->type == LPAREN) {
        match(currentToken, LPAREN);
        ParseTreeNode* exprNode = parseExpression(currentToken, symTable);
        match(currentToken, RPAREN);
        return exprNode;
    } else if ((*currentToken)->type == IDENTIFIER) {
        if (!lookupSymbol(symTable, (*currentToken)->value)) {
            printf("Semantic error: Undeclared variable '%s' at line %zu\n", (*currentToken)->value, (*currentToken)->lineNum);
            exit(1);
        }
        return createParseTreeNode(match(currentToken, IDENTIFIER), NULL);
    } else if ((*currentToken)->type == INT_L || (*currentToken)->type == FLOAT_L || (*currentToken)->type == CHAR_L || (*currentToken)->type == STR_L) {
        return createParseTreeNode(match(currentToken, (*currentToken)->type), NULL);
    } else {
        printf("Syntax error: Unexpected token '%s' in primary expression at line %zu\n", (*currentToken)->value, (*currentToken)->lineNum);
        exit(1);
    }
}

// parseMultiplicativeExpr: Handles "*", "/" and "%" operators.
ParseTreeNode* parseMultiplicativeExpr(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* left = parsePrimaryExpr(currentToken, symTable);
    while ((*currentToken)->type == STAR || (*currentToken)->type == SLASH || (*currentToken)->type == MOD) {
        TokenType opType = (*currentToken)->type;
        ParseTreeNode* opNode = createParseTreeNode(match(currentToken, opType), NULL);
        addChild(opNode, left);
        addChild(opNode, parsePrimaryExpr(currentToken, symTable));
        left = opNode;
    }
    return left;
}

// parseAdditiveExpr: Handles "+" and "-" operators.
ParseTreeNode* parseAdditiveExpr(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* left = parseMultiplicativeExpr(currentToken, symTable);
    while ((*currentToken)->type == PLUS || (*currentToken)->type == MINUS) {
        TokenType opType = (*currentToken)->type;
        ParseTreeNode* opNode = createParseTreeNode(match(currentToken, opType), NULL);
        addChild(opNode, left);
        addChild(opNode, parseMultiplicativeExpr(currentToken, symTable));
        left = opNode;
    }
    return left;
}

// parseRelationalExpr: Handles relational operators: "==", "!=", "<", "<=", ">" and ">=".
ParseTreeNode* parseExpression(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* left = parseAdditiveExpr(currentToken, symTable);
    while ((*currentToken)->type == EQ || (*currentToken)->type == NEQ || (*currentToken)->type == LT || (*currentToken)->type == LE || (*currentToken)->type == GT || (*currentToken)->type == GE) {
        TokenType opType = (*currentToken)->type;
        Token* opToken = match(currentToken, opType);
        ParseTreeNode* opNode = createParseTreeNode(opToken, NULL);
        addChild(opNode, left);
        ParseTreeNode* right = parseAdditiveExpr(currentToken, symTable);
        addChild(opNode, right);
        left = opNode;
    }
    return left;
}

/* Statement Parsing */

// parseDeclaration: Handles "DATATYPE Identifier [ "=" Expression ] ";".
ParseTreeNode* parseDeclaration(Token** currentToken, SymbolTable* symTable, int flag)
{
    ParseTreeNode* declNode = createParseTreeNode(&(Token) { .value = "DECLARATION", .type = BEGINNING }, NULL);
    Token* typeToken = match(currentToken, (*currentToken)->type);     // Accept int, float, char, string
    addChild(declNode, createParseTreeNode(typeToken, NULL));

    Token* idToken = match(currentToken, IDENTIFIER);
    if (lookupSymbol(symTable, idToken->value)) {
        printf("Semantic error: Redeclaration of variable '%s' at line %zu\n", idToken->value, idToken->lineNum);
        exit(1);
    }
    addChild(declNode, createParseTreeNode(idToken, NULL));

    ParseTreeNode* exprNode = NULL;
    if ((*currentToken)->type == EQUAL) {
        Token* eqToken = match(currentToken, EQUAL);
        addChild(declNode, createParseTreeNode(eqToken, NULL));
        exprNode = parseExpression(currentToken, symTable);
        addChild(declNode, exprNode);
    }

    if (flag == 0) {
        Token* semicolonToken = match(currentToken, SEMICOLON);
        addChild(declNode, createParseTreeNode(semicolonToken, NULL));
    }
    insertSymbol(symTable, idToken->value, typeToken->type, NULL);
    return declNode;
}

// parseAssignment: Handles "Identifier "=" Expression ";".
ParseTreeNode* parseAssignment(Token** currentToken, SymbolTable* symTable, int flag)
{
    ParseTreeNode* assignNode = createParseTreeNode(&(Token) { .value = "ASSIGNMENT", .type = BEGINNING }, NULL);
    Token* idToken = match(currentToken, IDENTIFIER);
    if (!lookupSymbol(symTable, idToken->value)) {
        printf("Semantic error: Assignment to undeclared variable '%s' at line %zu\n",
            idToken->value, idToken->lineNum);
        exit(1);
    }
    addChild(assignNode, createParseTreeNode(idToken, NULL));
    Token* eqToken = match(currentToken, EQUAL);
    addChild(assignNode, createParseTreeNode(eqToken, NULL));
    ParseTreeNode* exprNode = parseExpression(currentToken, symTable);
    addChild(assignNode, exprNode);
    if (flag == 0) {
        Token* semicolonToken = match(currentToken, SEMICOLON);
        addChild(assignNode, createParseTreeNode(semicolonToken, NULL));
    }
    // if (exprNode && exprNode->type == INT_L) {
    //     updateSymbol(symTable, idToken->value, NULL);
    // }
    return assignNode;
}

// parseExitStatement: Handles "exit" "(" Expression ")" ";".
ParseTreeNode* parseExitStatement(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* exitNode = createParseTreeNode(&(Token) { .value = "EXIT_STATEMENT", .type = BEGINNING }, NULL);
    Token* exitToken = match(currentToken, EXIT);
    addChild(exitNode, createParseTreeNode(exitToken, NULL));
    Token* lpToken = match(currentToken, LPAREN);
    addChild(exitNode, createParseTreeNode(lpToken, NULL));
    ParseTreeNode* exprNode = parseExpression(currentToken, symTable);
    addChild(exitNode, exprNode);
    Token* rpToken = match(currentToken, RPAREN);
    addChild(exitNode, createParseTreeNode(rpToken, NULL));
    Token* semicolonToken = match(currentToken, SEMICOLON);
    addChild(exitNode, createParseTreeNode(semicolonToken, NULL));
    return exitNode;
}

// parsePrintStatement: Handles "print" "(" Expression ")" ";".
ParseTreeNode* parsePrintStatement(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* printNode = createParseTreeNode(&(Token) { .value = "PRINT_STATEMENT", .type = BEGINNING }, NULL);
    Token* printToken = match(currentToken, PRINT);
    addChild(printNode, createParseTreeNode(printToken, NULL));
    match(currentToken, LPAREN);
    ParseTreeNode* exprNode = parseExpression(currentToken, symTable);
    addChild(printNode, exprNode);
    match(currentToken, RPAREN);
    Token* semicolonToken = match(currentToken, SEMICOLON);
    addChild(printNode, createParseTreeNode(semicolonToken, NULL));
    return printNode;
}

// parseScanStatement: Handles "scan" "(" Identifier ")" ";".
ParseTreeNode* parseScanStatement(Token** currentToken, SymbolTable* symTable)
{
    ParseTreeNode* scanNode = createParseTreeNode(&(Token) { .value = "SCAN_STATEMENT", .type = BEGINNING }, NULL);
    Token* scanToken = match(currentToken, SCAN);
    addChild(scanNode, createParseTreeNode(scanToken, NULL));
    match(currentToken, LPAREN);
    Token* idToken = match(currentToken, IDENTIFIER);
    if (!lookupSymbol(symTable, idToken->value)) {
        printf("Semantic error: Scanned variable '%s' is not declared at line %zu\n",
            idToken->value, idToken->lineNum);
        exit(1);
    }
    addChild(scanNode, createParseTreeNode(idToken, NULL));
    match(currentToken, RPAREN);
    Token* semicolonToken = match(currentToken, SEMICOLON);
    addChild(scanNode, createParseTreeNode(semicolonToken, NULL));
    return scanNode;
}

// parseIfStatement: Handles "if" "(" Expression ")" Statement [ "else" Statement ].
ParseTreeNode* parseIfStatement(Token** currentToken, SymbolTable* symTable)
{
    SymbolTable* ifScope = createSymbolTable(symTable);
    ParseTreeNode* ifNode = createParseTreeNode(&(Token) { .value = "IF_STATEMENT", .type = BEGINNING }, ifScope);
    Token* ifToken = match(currentToken, IF);
    addChild(ifNode, createParseTreeNode(ifToken, NULL));
    match(currentToken, LPAREN);
    ParseTreeNode* condExpr = parseExpression(currentToken, symTable);
    addChild(ifNode, condExpr);
    match(currentToken, RPAREN);
    ParseTreeNode* thenStmt = parseStatement(currentToken, ifScope);
    addChild(ifNode, thenStmt);
    if ((*currentToken)->type == ELSE) {
        SymbolTable* elseScope = createSymbolTable(symTable);
        Token* elseToken = match(currentToken, ELSE);
        addChild(ifNode, createParseTreeNode(elseToken, elseScope));
        ParseTreeNode* elseStmt = parseStatement(currentToken, elseScope);
        addChild(ifNode, elseStmt);
    }
    return ifNode;
}

// parseWhileStatement: Handles "while" "(" Expression ")" Statement.
ParseTreeNode* parseWhileStatement(Token** currentToken, SymbolTable* symTable)
{
    SymbolTable* whileScope = createSymbolTable(symTable);
    ParseTreeNode* whileNode = createParseTreeNode(&(Token) { .value = "WHILE_STATEMENT", .type = BEGINNING }, whileScope);
    Token* whileToken = match(currentToken, WHILE);
    addChild(whileNode, createParseTreeNode(whileToken, NULL));
    match(currentToken, LPAREN);
    ParseTreeNode* condExpr = parseExpression(currentToken, symTable);
    addChild(whileNode, condExpr);
    match(currentToken, RPAREN);
    ParseTreeNode* loopStmt = parseStatement(currentToken, whileScope);
    addChild(whileNode, loopStmt);
    return whileNode;
}

/* For-loop Parsing Helpers */

// parseForInit: Parses the initializer part of a for-loop.
ParseTreeNode* parseForInit(Token** currentToken, SymbolTable* symTable)
{
    if ((*currentToken)->type == INT)
        return parseDeclaration(currentToken, symTable, 1);
    else if ((*currentToken)->type == IDENTIFIER && (((*currentToken) + 1)->type == EQUAL))
        return parseAssignment(currentToken, symTable, 1);
    else
        return NULL;
}

// parseForUpdate: Parses the update part of a for-loop.
ParseTreeNode* parseForUpdate(Token** currentToken, SymbolTable* symTable)
{
    if ((*currentToken)->type != RPAREN) {
        if ((*currentToken)->type == IDENTIFIER && (((*currentToken) + 1)->type == EQUAL))
            return parseAssignment(currentToken, symTable, 1);
        else
            return parseExpression(currentToken, symTable);
    } else {
        return NULL;
    }
}

// parseForStatement: Handles "for" "(" [ForInit] ";" Expression ";" [ForUpdate] ")" Statement.
// A new scope is created for the for-loop.
ParseTreeNode* parseForStatement(Token** currentToken, SymbolTable* symTable)
{
    SymbolTable* forScope = createSymbolTable(symTable);
    ParseTreeNode* forNode = createParseTreeNode(&(Token) { .value = "FOR_STATEMENT", .type = BEGINNING }, forScope);
    Token* forToken = match(currentToken, FOR);
    addChild(forNode, createParseTreeNode(forToken, NULL));
    match(currentToken, LPAREN);
    ParseTreeNode* initNode = parseForInit(currentToken, forScope);
    if (initNode)
        addChild(forNode, initNode);
    match(currentToken, SEMICOLON);
    ParseTreeNode* condNode = parseExpression(currentToken, forScope);
    addChild(forNode, condNode);
    match(currentToken, SEMICOLON);
    ParseTreeNode* updateNode = parseForUpdate(currentToken, forScope);
    if (updateNode)
        addChild(forNode, updateNode);
    match(currentToken, RPAREN);
    ParseTreeNode* bodyNode = parseStatement(currentToken, forScope);
    addChild(forNode, bodyNode);
    return forNode;
}

/* Block and Statement Parsing */

// parseBlock: Handles "{" StatementList "}" and creates a new scope.
ParseTreeNode* parseBlock(Token** currentToken, SymbolTable* symTable)
{
    SymbolTable* localScope = createSymbolTable(symTable);
    ParseTreeNode* blockNode = createParseTreeNode(&(Token) { .value = "BLOCK", .type = BEGINNING }, localScope);
    match(currentToken, LBRACE);
    while ((*currentToken)->type != RBRACE) {
        addChild(blockNode, parseStatement(currentToken, localScope));
    }
    match(currentToken, RBRACE);
    return blockNode;
}

// parseStatement: Determines which kind of statement to parse.
ParseTreeNode* parseStatement(Token** currentToken, SymbolTable* symTable)
{
    switch ((*currentToken)->type) {
    case INT:
    case FLOAT:
    case CHAR:
    case STRING:
        return parseDeclaration(currentToken, symTable, 0);
    case IDENTIFIER:
        if (((*currentToken) + 1)->type == EQUAL)
            return parseAssignment(currentToken, symTable, 0);
        else {
            printf("Syntax error: Unexpected identifier usage '%s' at line %zu\n",
                (*currentToken)->value, (*currentToken)->lineNum);
            exit(1);
        }
    case EXIT:
        return parseExitStatement(currentToken, symTable);
    case IF:
        return parseIfStatement(currentToken, symTable);
    case WHILE:
        return parseWhileStatement(currentToken, symTable);
    case FOR:
        return parseForStatement(currentToken, symTable);
    case LBRACE:
        return parseBlock(currentToken, symTable);
    case PRINT:
        return parsePrintStatement(currentToken, symTable);
    case SCAN:
        return parseScanStatement(currentToken, symTable);
    default:
        printf("Syntax error: Unexpected token '%s' at line %zu\n",
            (*currentToken)->value, (*currentToken)->lineNum);
        exit(1);
    }
}

// Top-level parser: Processes the token stream, builds the parse tree, and manages scope.
ParseTreeNode* parser(Token* tokens)
{
    Token* currentToken = tokens;
    SymbolTable* globalScope = createSymbolTable(NULL);
    ParseTreeNode* root = createParseTreeNode(&(Token) { .value = "PROGRAM", .type = BEGINNING }, globalScope);
    while (currentToken->type != END_OF_TOKENS) {
        addChild(root, parseStatement(&currentToken, globalScope));
    }
    printParseTree(root, NULL, 0);
    // destroySymbolTable(globalScope);
    return root;
}