#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_NUM,
    TOKEN_ID,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_ASSIGN,
    TOKEN_EQ,      
    TOKEN_NEQ,     
    TOKEN_LT,      
    TOKEN_GT,      
    TOKEN_LE,      
    TOKEN_GE,      
    TOKEN_PRINT,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_SEMICOLON,
    TOKEN_EOF

} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
} Token;

#endif