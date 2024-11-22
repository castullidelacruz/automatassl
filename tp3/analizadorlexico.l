%{
#include "y.tab.h"

void yyerror(const char *s);
%}

%%

[-]?[0-9]+(\.[0-9]+)?    { yylval.fval = atof(yytext); return NUMBER; } 
[-+\/*()=]      { return *yytext; }
[ \t\n]         ;  // ignorar espacios en blanco y saltos de línea

.               { yyerror("Caracter no valido"); }

%%

int yywrap() {
    return 1;
}
