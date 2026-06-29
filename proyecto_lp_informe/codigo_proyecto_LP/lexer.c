#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

static char *src;
static int pos;

void initLexer(char *source){
    src = source;
    pos = 0;
}

static char currentChar(){
    return src[pos];
}

static void advance(){
    pos++;
}

Token getNextToken(){
    Token t;
    while (isspace(currentChar()))
        advance();

    if (currentChar() == '\0'){
        t.type = TOKEN_EOF;
        strcpy(t.lexeme, "EOF");
        return t;
    }

    if (isdigit(currentChar()))
    {
        int i = 0;

        while (isdigit(currentChar()))
        {
            t.lexeme[i++] = currentChar();
            advance();
        }

        t.lexeme[i] = '\0';
        t.type = TOKEN_NUM;
        return t;
    }

    if (isalpha(currentChar()) || currentChar() == '_'){
        int i = 0;
        while (isalnum(currentChar()) || currentChar() == '_'){
            t.lexeme[i++] = currentChar();
            advance();
        }
        t.lexeme[i] = '\0';
        if (strcmp(t.lexeme, "print") == 0)
            t.type = TOKEN_PRINT;

        else if (strcmp(t.lexeme, "if") == 0)
            t.type = TOKEN_IF;

        else if (strcmp(t.lexeme, "else") == 0)
            t.type = TOKEN_ELSE;

        else if (strcmp(t.lexeme, "while") == 0)
            t.type = TOKEN_WHILE;

        else if (strcmp(t.lexeme, "for") == 0)
            t.type = TOKEN_FOR;

        else
            t.type = TOKEN_ID;

        return t;
    }

    if (currentChar() == '=' && src[pos + 1] == '='){
        t.type = TOKEN_EQ;
        strcpy(t.lexeme, "==");
        advance();
        advance();
        return t;
    }

    if (currentChar() == '!' && src[pos + 1] == '='){
        t.type = TOKEN_NEQ;
        strcpy(t.lexeme, "!=");
        advance();
        advance();
        return t;
    }

    if (currentChar() == '<' && src[pos + 1] == '='){
        t.type = TOKEN_LE;
        strcpy(t.lexeme, "<=");
        advance();
        advance();
        return t;
    }

    if (currentChar() == '>' && src[pos + 1] == '='){
        t.type = TOKEN_GE;
        strcpy(t.lexeme, ">=");
        advance();
        advance();
        return t;
    }

    switch (currentChar())
    {

    case '+':
        t.type = TOKEN_PLUS;
        strcpy(t.lexeme, "+");
        break;

    case '-':
        t.type = TOKEN_MINUS;
        strcpy(t.lexeme, "-");
        break;

    case '*':
        t.type = TOKEN_MUL;
        strcpy(t.lexeme, "*");
        break;

    case '/':
        t.type = TOKEN_DIV;
        strcpy(t.lexeme, "/");
        break;
    case '%':
        t.type = TOKEN_MOD;
        strcpy(t.lexeme, "%");
        break;
    case '=':
        t.type = TOKEN_ASSIGN;
        strcpy(t.lexeme, "=");
        break;

    case '<':
        t.type = TOKEN_LT;
        strcpy(t.lexeme, "<");
        break;

    case '>':
        t.type = TOKEN_GT;
        strcpy(t.lexeme, ">");
        break;

    case '(':
        t.type = TOKEN_LPAREN;
        strcpy(t.lexeme, "(");
        break;

    case ')':
        t.type = TOKEN_RPAREN;
        strcpy(t.lexeme, ")");
        break;

    case '{':
        t.type = TOKEN_LBRACE;
        strcpy(t.lexeme, "{");
        break;

    case '}':
        t.type = TOKEN_RBRACE;
        strcpy(t.lexeme, "}");
        break;

    case ';':
        t.type = TOKEN_SEMICOLON;
        strcpy(t.lexeme, ";");
        break;

    default:
        printf("Error lexico: caracter '%c' no reconocido\n", currentChar());
        advance();
        return getNextToken();
    }

    advance();
    return t;
}