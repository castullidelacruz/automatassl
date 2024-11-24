%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
//RUTINAS SEMANTICAS
int validar_division(float divisor);
int convertir_a_entero(float resultado);
%}

%union {
    float valor;  
}

%token <valor> DECIMAL

%type <valor> expr term factor

%%

input:  
    | input expr '=' { 
        printf("El resultado es: %f\n", $2); 
        int resultado_entero = convertir_a_entero($2);
        printf("El resultado convertido a entero es: %d\n", resultado_entero);
    }
    ;

expr:   expr '+' term { $$ = $1 + $3; }
    | expr '-' term { $$ = $1 - $3; }
    | term { $$ = $1; }
    ;

term:   term '*' factor { $$ = $1 * $3; }
    | term '/' factor { 
        if (validar_division($3)) {
            $$ = $1 / $3;
        } else {
            yyerror("Division por cero");
            $$ = 0; //devuelve cero para poder continuar el analsis
        } }
    | factor { $$ = $1; }
    ;

factor: DECIMAL
    | '(' expr ')' { $$ = $2; }
    ;

%%

int main() {
    printf("Ingresa operacion matematica: \n");
     
        yyparse();

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error sintactico: %s\n", s);
}

//RUTINAS SEMANTICAS
int validar_division(float divisor) {
    return divisor != 0;
}

int convertir_a_entero(float resultado) {
    // Convierte un decimal a entero truncando los decimales
    return (int) resultado;
}
