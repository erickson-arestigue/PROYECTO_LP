#ifndef AST_H
#define AST_H

/*
 * Tipos de nodos del AST
 */
typedef enum {
    NODE_NUM,
    NODE_VAR,
    NODE_BINOP,
    NODE_COMPARE,
    NODE_ASSIGN,
    NODE_PRINT,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_BLOCK

} NodeType;

/*
 * Nodo del AST
 */

typedef struct AST{
    NodeType type;
    int value;
    char name[64];
    char op[3];
    struct AST *left;
    struct AST *right;
    struct AST *third;
    struct AST *fourth;
    struct AST *next;
}AST;


/*************** EXPRESIONES ****************/

AST* createNumber(int value);

AST* createVariable(char *name);

AST* createBinary(char *op,AST *left,AST *right);

AST* createCompare(char *op,AST *left,AST *right);


/*************** SENTENCIAS ****************/

AST* createAssign(char *name,AST *expr);

AST* createPrint(AST *expr);

AST* createIf(AST *condition,AST *thenBranch,AST *elseBranch);

AST* createWhile(AST *condition, AST *body);

AST* createFor(AST *init,AST *condition,AST *update,AST *body);

AST* createBlock(AST *firstStatement);

/******************** LIBERACIÓN ********************/

void freeAST(AST *node);

#endif