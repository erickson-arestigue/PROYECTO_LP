#ifndef AST_H
#define AST_H
/*
 * Tipos de nodos que pueden existir
 * dentro del Árbol de Sintaxis Abstracta (AST).
 */
typedef enum {
    NODE_NUM,
    NODE_VAR,
    NODE_BINOP,
    NODE_ASSIGN,
    NODE_PRINT
} NodeType;
/*
 * Estructura que representa un nodo del AST.
 * Dependiendo del tipo de nodo, algunos campos
 * serán utilizados y otros no.
 */
typedef struct AST{
    NodeType type;
    int value;
    char name[64];
    char op;
    struct AST* left;
    struct AST* right;
} AST;
//nodo numerico
AST* createNumber(int value);
//nodo variable
AST* createVariable(char* name);
//nodo de operacion binaria
AST* createBinary(char op,AST* left,AST* right);
//nodo de asignacion
AST* createAssign(char* name,AST* expr);
//imprime un valor
AST* createPrint(AST* expr);

#endif