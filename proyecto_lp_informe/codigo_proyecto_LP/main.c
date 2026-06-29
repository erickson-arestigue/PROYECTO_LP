#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "eval.h"

int main() {
    printf("MINIPYTHON\n");
    char linea[256];
    char buffer[8192] = "";
    while (1) {
        printf(">>> ");
        if (fgets(linea, sizeof(linea), stdin) == NULL)break;
        if (strcmp(linea, "exit\n") == 0)break;
        if (strcmp(linea, "\n") == 0) {
            AST* tree = parse(buffer);
            evaluate(tree);
            freeAST(tree);
            buffer[0] = '\0';
            continue;
        }
        strcat(buffer, linea);
    }
}