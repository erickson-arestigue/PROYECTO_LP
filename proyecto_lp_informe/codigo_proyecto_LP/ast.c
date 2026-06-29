#include <stdlib.h>
#include <string.h>

#include "ast.h"

/* Inicializa todos los punteros del nodo */

static void initNode(AST *n){
    n->left = NULL;
    n->right = NULL;
    n->third = NULL;
    n->fourth = NULL;
    n->next = NULL;

    n->value = 0;
    n->name[0] = '\0';
    n->op[0] = '\0';
}

/******************** EXPRESIONES ********************/

AST* createNumber(int value){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_NUM;
    n->value = value;
    return n;
}

AST* createVariable(char *name){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_VAR;
    strcpy(n->name, name);
    return n;
}

AST* createBinary(char *op, AST *left, AST *right){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_BINOP;
    strcpy(n->op, op);
    n->left = left;
    n->right = right;
    return n;
}

AST* createCompare(char *op, AST *left, AST *right){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_COMPARE;
    strcpy(n->op, op);
    n->left = left;
    n->right = right;
    return n;
}

/******************** SENTENCIAS ********************/

AST* createAssign(char *name, AST *expr){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_ASSIGN;
    strcpy(n->name, name);
    n->right = expr;
    return n;
}

AST* createPrint(AST *expr){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_PRINT;
    n->left = expr;
    return n;
}

AST* createIf(AST *condition,AST *thenBranch,AST *elseBranch){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_IF;
    n->left = condition;
    n->right = thenBranch;
    n->third = elseBranch;
    return n;
}

AST* createWhile(AST *condition,AST *body){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_WHILE;
    n->left = condition;
    n->right = body;
    return n;
}

AST* createFor(AST *init,AST *condition,AST *update,AST *body){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_FOR;
    n->left = init;
    n->right = condition;
    n->third = update;
    n->fourth = body;
    return n;
}

AST* createBlock(AST *firstStatement){
    AST *n = malloc(sizeof(AST));
    initNode(n);
    n->type = NODE_BLOCK;
    n->left = firstStatement;
    return n;
}

/******************** LIBERACIÓN ********************/

void freeAST(AST *node){
    if (!node) return;
    AST *next;
    while (node)
    {
        freeAST(node->left);
        freeAST(node->right);
        freeAST(node->third);
        freeAST(node->fourth);
        next = node->next;
        free(node);
        node = next;
    }
}