#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "eval.h"

int main() {
    char linea[256];
    printf("MINIPYTHON\n");
    while (1) {
        printf(">>> ");
        fgets(linea, sizeof(linea), stdin);
        if(strcmp(linea, "exit\n") == 0)break;
        AST* tree = parse(linea);
        evaluate(tree);
    }
    return 0;
}