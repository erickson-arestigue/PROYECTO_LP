#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

/*
 * Analiza un programa completo y devuelve
 * el AST correspondiente.
 */
AST* parse(char *source);

#endif