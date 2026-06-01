#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "lexer.h"

static Token current;

static void eat(TokenType type){
    if(current.type==type) current=getNextToken();
}

static AST* factor(){
    if(current.type==TOKEN_NUM){
        int v=atoi(current.lexeme);
        eat(TOKEN_NUM);
        return createNumber(v);
    }
    if(current.type==TOKEN_ID){
        char name[64];
        strcpy(name,current.lexeme);
        eat(TOKEN_ID);
        return createVariable(name);
    }
    return NULL;
}

static AST* term(){
    AST* node=factor();
    while(current.type==TOKEN_MUL ||current.type==TOKEN_DIV){
        char op=current.lexeme[0];
        if(current.type==TOKEN_MUL) eat(TOKEN_MUL);
        else eat(TOKEN_DIV);
        node=createBinary(op,node,factor());
    }
    return node;
}

static AST* expr(){
    AST* node=term();
    while(current.type==TOKEN_PLUS ||current.type==TOKEN_MINUS){
        char op=current.lexeme[0];
        if(current.type==TOKEN_PLUS) eat(TOKEN_PLUS);
        else eat(TOKEN_MINUS);
        node=createBinary(op,node,term());
    }
    return node;
}
//
AST* parse(char* source){
    initLexer(source);
    current = getNextToken();
    // print(expr) 
    if(current.type == TOKEN_PRINT){
        eat(TOKEN_PRINT);
        eat(TOKEN_LPAREN);
        AST* expression = expr();
        eat(TOKEN_RPAREN);
        return createPrint(expression);
    }
    // variable=expr 
    char name[64];
    strcpy(name,current.lexeme);
    eat(TOKEN_ID);
    eat(TOKEN_ASSIGN);
    AST* expression = expr();
    return createAssign(name, expression);
}