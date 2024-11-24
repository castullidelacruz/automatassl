%{
#include "y.tab.h"
#include <stdio.h>

void yyerror(const char *s);
%}

%%

[-]?[0-9]+(\.[0-9]+)? {
    printf("[DEBUG] Token DECIMAL reconocido: %s\n", yytext);
    yylval.valor = atof(yytext); 
    return DECIMAL; 
}

[-+\/*()=] {
    printf("[DEBUG] Operador reconocido: %c\n", *yytext);
    return *yytext; 
}

. {
    printf("[DEBUG] Caracter no reconocido: %s\n", yytext);
    yyerror("NO RECONOCIDO\n");
}

%%

int yywrap() {
    return 0;  // Permite continuar leyendo entradas
}
