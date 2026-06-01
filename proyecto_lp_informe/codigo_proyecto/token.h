#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    //varaibles y numeros
    TOKEN_NUM,
    TOKEN_ID,
    //operadores aritmeticos
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    //asignacion(=)
    TOKEN_ASSIGN,
    //imprimir
    TOKEN_PRINT,
    //parentesis
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    //salto de linea
    TOKEN_EOF

} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
} Token;

#endif