#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eval.h"

typedef struct {
    char name[64];
    int value;
} Symbol;

static Symbol table[100];
static int count=0;
static void setVar(char* name,int value){
    for(int i=0;i<count;i++){
        if(strcmp(table[i].name,name)==0){
            table[i].value=value;
            return;
        }
    }
    strcpy(table[count].name,name);
    table[count].value=value;
    count++;
}

static int getVar(char* name){
    for(int i=0;i<count;i++){
        if(strcmp(table[i].name,name)==0)
            return table[i].value;
    }
    return 0;
}

int evaluate(AST *node){
    if(node == NULL)
        return 0;

    switch(node->type){
        case NODE_NUM:
            return node->value;

        case NODE_VAR:
            return getVar(node->name);

        case NODE_BINOP:
        {
            int l = evaluate(node->left);
            int r = evaluate(node->right);

            if(strcmp(node->op,"/")==0 || strcmp(node->op,"%")==0) {
                if(r == 0) {
                    printf("Error: division/modulo por cero\n");
                    exit(1);
                }
            }
            if(strcmp(node->op,"+")==0) return l+r;
            if(strcmp(node->op,"-")==0) return l-r;
            if(strcmp(node->op,"*")==0) return l*r;
            if(strcmp(node->op,"/")==0) return l/r;
            if(strcmp(node->op,"%")==0) return l%r;
            return 0;
        }

        case NODE_COMPARE:
        {
            int l = evaluate(node->left);
            int r = evaluate(node->right);
            if(strcmp(node->op,"<")==0)  return l<r;
            if(strcmp(node->op,">")==0)  return l>r;
            if(strcmp(node->op,"<=")==0) return l<=r;
            if(strcmp(node->op,">=")==0) return l>=r;
            if(strcmp(node->op,"==")==0) return l==r;
            if(strcmp(node->op,"!=")==0) return l!=r;
            return 0;
        }

        case NODE_ASSIGN:
        {
            int value = evaluate(node->right);
            setVar(node->name,value);
            return value;
        }

        case NODE_PRINT:
        {
            int value = evaluate(node->left);
            printf("%d\n",value);
            return value;
        }

        case NODE_BLOCK:
        {
            AST *current = node->left;
            while(current != NULL){
                evaluate(current);
                current = current->next;
            }
            return 0;
        }

        case NODE_IF:
        {
            if(evaluate(node->left)){
                evaluate(node->right);
            }else{
                if(node->third!=NULL)
                    evaluate(node->third);
            }
            return 0;
        }

        case NODE_WHILE:
        {
            while(evaluate(node->left)){
                evaluate(node->right);
            }
            return 0;
        }
        case NODE_FOR:
        {
            evaluate(node->left);
            while (evaluate(node->right)){
                evaluate(node->fourth);
                evaluate(node->third);
            }
            return 0;
        }
        default:
            return 0;
    }
}