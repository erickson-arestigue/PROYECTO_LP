#ifndef LEXER_H
#define LEXER_H

#include "token.h"

/*
 * Inicializa el lexer con el código fuente
 * que será analizado.
 */
void initLexer(char* source);
/*
 * Obtiene el siguiente token del código fuente.
 * Es la función principal del análisis léxico.
 */
Token getNextToken();

#endif