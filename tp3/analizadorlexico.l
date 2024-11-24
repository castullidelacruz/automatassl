%{
#include "y.tab.h"

void yyerror(const char *s);
%}

%%

[-]?[0-9]+(\.[0-9]+)?    { yylval.valor = atof(yytext); return DECIMAL; } 
[-+\/*()=]      { return *yytext; }

.               { yyerror("NO RECONOCIDO\n"); }

%%

int yywrap() {
    return 1;
}
