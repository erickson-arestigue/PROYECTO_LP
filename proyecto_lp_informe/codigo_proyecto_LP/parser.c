#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "parser.h"
#include "lexer.h"

static Token current;
static AST* comparison();
static AST* statement();
static AST* program();
static AST* block();
static AST* ifStatement();
static AST* whileStatement();
static AST* forStatement();

static void eat(TokenType type){
    if(current.type != type){
        printf("Error de sintaxis\n");
        exit(1);
    }
    current = getNextToken();
}

static AST* factor()
{
    AST *node;
    if(current.type == TOKEN_MINUS){
        eat(TOKEN_MINUS);
        return createBinary("-",createNumber(0),factor());
    }

    if(current.type == TOKEN_NUM){
        int value = atoi(current.lexeme);
        eat(TOKEN_NUM);
        return createNumber(value);
    }

    if(current.type == TOKEN_ID){
        char name[64];
        strcpy(name,current.lexeme);
        eat(TOKEN_ID);
        return createVariable(name);
    }

    if(current.type == TOKEN_LPAREN){
        eat(TOKEN_LPAREN);
        node = comparison();
        eat(TOKEN_RPAREN);
        return node;
    }

    printf("Factor inesperado\n");
    exit(1);
}

static AST* term(){
    AST *node = factor();
    while(current.type==TOKEN_MUL ||current.type==TOKEN_DIV ||current.type==TOKEN_MOD){
        char op[3];
        strcpy(op, current.lexeme);

        if(current.type==TOKEN_MUL)
            eat(TOKEN_MUL);
        else if(current.type==TOKEN_DIV)
            eat(TOKEN_DIV);
        else
            eat(TOKEN_MOD);

        node = createBinary(op, node, factor());
    }
    return node;
}

static AST* expr(){
    AST *node = term();
    while(current.type==TOKEN_PLUS ||current.type==TOKEN_MINUS){
        char op[2];
        op[0]=current.lexeme[0];
        op[1]='\0';
        if(current.type==TOKEN_PLUS)
            eat(TOKEN_PLUS);
        else
            eat(TOKEN_MINUS);

        node = createBinary(op,node,term());
    }
    return node;
}

static AST* comparison(){
    AST *node = expr();
    while(
        current.type==TOKEN_LT ||
        current.type==TOKEN_GT ||
        current.type==TOKEN_LE ||
        current.type==TOKEN_GE ||
        current.type==TOKEN_EQ ||
        current.type==TOKEN_NEQ){
        char op[3];
        strcpy(op,current.lexeme);
        TokenType t=current.type;
        eat(t);
        node = createCompare(op,node,expr());
    }
    return node;
}

static AST* assignment(){
    char name[64];
    strcpy(name, current.lexeme);
    eat(TOKEN_ID);
    eat(TOKEN_ASSIGN);
    AST *value = comparison();
    return createAssign(name, value);
}

static AST* printStatement(){
    eat(TOKEN_PRINT);
    eat(TOKEN_LPAREN);
    AST *expr = comparison();
    eat(TOKEN_RPAREN);
    return createPrint(expr);
}

static AST* statement(){
    AST *node=NULL;
    switch(current.type){
        case TOKEN_PRINT:
            node = printStatement();
            break;
        case TOKEN_ID:
            node = assignment();
            break;
        case TOKEN_IF:
            node = ifStatement();
            break;
        case TOKEN_WHILE:
            node = whileStatement();
            break; 
        case TOKEN_FOR:
            node = forStatement();
            break;
        case TOKEN_LBRACE:
            node = block();
            break;
        default:
            printf("Sentencia invalida\n");
            exit(1);
    }
    return node;
}

static AST* block(){
    eat(TOKEN_LBRACE);
    AST *first = NULL;
    AST *last = NULL;
    while(current.type != TOKEN_RBRACE &&
          current.type != TOKEN_EOF){
        AST *stmt = statement();
        if(current.type == TOKEN_SEMICOLON)
            eat(TOKEN_SEMICOLON);

        if(first == NULL){
            first = stmt;
            last = stmt;
        }else{
            last->next = stmt;
            last = stmt;
        }
    }
    eat(TOKEN_RBRACE);
    return createBlock(first);
}

static AST* ifStatement(){
    eat(TOKEN_IF);
    eat(TOKEN_LPAREN);
    AST *condition = comparison();
    eat(TOKEN_RPAREN);
    AST *thenBranch = statement();
    AST *elseBranch = NULL;
    if(current.type == TOKEN_ELSE){
        eat(TOKEN_ELSE);
        elseBranch = statement();
    }

    return createIf(condition,thenBranch,elseBranch);
}

static AST* whileStatement(){
    eat(TOKEN_WHILE);
    eat(TOKEN_LPAREN);
    AST *condition = comparison();
    eat(TOKEN_RPAREN);
    AST *body = statement();
    return createWhile(condition, body);
}

static AST* forStatement(){
    eat(TOKEN_FOR);
    eat(TOKEN_LPAREN);
    AST *init = NULL;
    if(current.type != TOKEN_SEMICOLON){
        init = statement();
    }
    eat(TOKEN_SEMICOLON);
    AST *condition = NULL;
    if(current.type != TOKEN_SEMICOLON){
        condition = comparison();
    }
    eat(TOKEN_SEMICOLON);
    AST *update = NULL;
    if(current.type != TOKEN_RPAREN){
        update = statement();
    }
    eat(TOKEN_RPAREN);
    AST *body = statement();
    return createFor(init, condition, update, body);
}

static AST* program(){
    AST *first = NULL;
    AST *last = NULL;
    while(current.type != TOKEN_EOF){
        AST *stmt = statement();
        if(current.type == TOKEN_SEMICOLON)
            eat(TOKEN_SEMICOLON);

        if(first == NULL){
            first = stmt;
            last = stmt;
        }else{
            last->next = stmt;
            last = stmt;
        }
    }
    return createBlock(first);
}

AST* parse(char *source){
    initLexer(source);
    current = getNextToken();
    return program();
}