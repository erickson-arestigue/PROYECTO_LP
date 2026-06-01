#include <stdlib.h>
#include <string.h>

#include "ast.h"

AST* createNumber(int value){
    AST* n = malloc(sizeof(AST));
    n->type = NODE_NUM;
    n->value = value;
    return n;
}

AST* createVariable(char* name){
    AST* n = malloc(sizeof(AST));
    n->type = NODE_VAR;
    strcpy(n->name,name);
    return n;
}

AST* createBinary(char op,AST* left,AST* right){
    AST* n = malloc(sizeof(AST));
    n->type = NODE_BINOP;
    n->op = op;
    n->left = left;
    n->right = right;
    return n;
}

AST* createAssign(char* name,AST* expr){
    AST* n = malloc(sizeof(AST));
    n->type = NODE_ASSIGN;
    strcpy(n->name,name);
    n->right = expr;
    return n;
}

AST* createPrint(AST* expr){
    AST* n = malloc(sizeof(AST));
    n->type = NODE_PRINT;
    n->left = expr;
    return n;
}