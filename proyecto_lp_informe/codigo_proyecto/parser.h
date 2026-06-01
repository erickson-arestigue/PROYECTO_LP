#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

/*
 * Analiza el código fuente recibido y construye
 * el Árbol de Sintaxis Abstracta (AST).
 */
AST* parse(char* source);

#endif