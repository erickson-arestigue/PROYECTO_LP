#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

static char* src;
static int pos;
//
void initLexer(char* source){
    src = source;
    pos = 0;
}

static char currentChar(){
    return src[pos];
}

static void advance(){
    pos++;
}
//
Token getNextToken(){
    Token t;
    while(isspace(currentChar()))
        advance();

    if(currentChar()=='\0'){
        t.type = TOKEN_EOF;
        strcpy(t.lexeme,"EOF");
        return t;
    }

    if(isdigit(currentChar())){
        int i=0;
        while(isdigit(currentChar())){
            t.lexeme[i++]=currentChar();
            advance();
        }
        t.lexeme[i]='\0';
        t.type = TOKEN_NUM;
        return t;
    }

    if(isalpha(currentChar())){
        int i=0;
        while(isalnum(currentChar())){
            t.lexeme[i++]=currentChar();
            advance();
        }
        t.lexeme[i]='\0';
        if(strcmp(t.lexeme,"print")==0) t.type = TOKEN_PRINT;
        else t.type = TOKEN_ID;
        return t;
    }

    switch(currentChar()){
        case '+':
            t.type=TOKEN_PLUS;
            strcpy(t.lexeme,"+");
            break;

        case '-':
            t.type=TOKEN_MINUS;
            strcpy(t.lexeme,"-");
            break;

        case '*':
            t.type=TOKEN_MUL;
            strcpy(t.lexeme,"*");
            break;

        case '/':
            t.type=TOKEN_DIV;
            strcpy(t.lexeme,"/");
            break;

        case '=':
            t.type=TOKEN_ASSIGN;
            strcpy(t.lexeme,"=");
            break;

        case '(':
            t.type=TOKEN_LPAREN;
            strcpy(t.lexeme,"(");
            break;

        case ')':
            t.type=TOKEN_RPAREN;
            strcpy(t.lexeme,")");
            break;
    }
    advance();
    return t;
}