#include <stdio.h>
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

int evaluate(AST* node){
    if(node->type==NODE_NUM)
        return node->value;

    if(node->type==NODE_VAR)
        return getVar(node->name);

    if(node->type==NODE_BINOP){
        int l=evaluate(node->left);
        int r=evaluate(node->right);
        switch(node->op){

            case '+':
                return l+r;

            case '-':
                return l-r;

            case '*':
                return l*r;

            case '/':
                return l/r;
        }
    }
    if(node->type==NODE_ASSIGN){
        int value=evaluate(node->right);
        setVar(node->name,value);
        return value;
    }
    if(node->type==NODE_PRINT){
        int value=evaluate(node->left);
        printf("%d\n", value);
        return value;
    }
    return 0;
}