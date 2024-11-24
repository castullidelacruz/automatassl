%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Prototipos
void yyerror(const char *s);
int yylex(void);

// RUTINAS SEMÁNTICAS
int validar_rango(float resultado);
int es_entero(float numero);
int convertir_a_entero(float resultado);
int validar_division(float divisor);
%}

%union {
    float valor;
}

%token <valor> DECIMAL
%type <valor> expr term factor

%%

input:  
    input_line
    | input input_line
    ;

input_line: 
    expr '=' { 
        printf("El resultado es: %f\n", $1);

        // Verificar rango
        printf("[DEBUG] Llamando a validar_rango...\n");
        if (!validar_rango($1)) {
            yyerror("El resultado está fuera del rango permitido (-500 a 500).");
        } else {
            printf("El resultado está dentro del rango permitido.\n");
        }

        // Verificar si es entero
        printf("[DEBUG] Llamando a es_entero...\n");
        if (es_entero($1)) {
            printf("El resultado es un número entero exacto.\n");
        } else {
            printf("El resultado es un número decimal.\n");
        }

        // Convertir a entero
        printf("[DEBUG] Llamando a convertir_a_entero...\n");
        int resultado_entero = convertir_a_entero($1);
        printf("El resultado convertido a entero es: %d\n", resultado_entero);
    }
    ;

expr:   expr '+' term { 
            $$ = $1 + $3; 
            printf("[DEBUG] Suma: %f + %f = %f\n", $1, $3, $$);
        }
    | expr '-' term { 
            $$ = $1 - $3; 
            printf("[DEBUG] Resta: %f - %f = %f\n", $1, $3, $$);
        }
    | term { $$ = $1; }
    ;

term:   term '*' factor { 
            $$ = $1 * $3; 
            printf("[DEBUG] Multiplicación: %f * %f = %f\n", $1, $3, $$);
        }
    | term '/' factor { 
            if (validar_division($3)) {
                $$ = $1 / $3;
                printf("[DEBUG] División: %f / %f = %f\n", $1, $3, $$);
            } else {
                yyerror("División por cero.");
                $$ = 0;  // Evitar propagación de errores
            }
        }
    | factor { $$ = $1; }
    ;

factor: DECIMAL { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    ;

%%

// MAIN
int main() {
    printf("Ingrese una operación matemática:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

// RUTINAS SEMÁNTICAS
int validar_rango(float resultado) {
    printf("[DEBUG] Validando rango para: %f\n", resultado);
    return resultado >= -500 && resultado <= 500;
}

int es_entero(float numero) {
    printf("[DEBUG] Verificando si es entero: %f\n", numero);
    return (numero == (int)numero);
}

int convertir_a_entero(float resultado) {
    printf("[DEBUG] Convirtiendo a entero: %f\n", resultado);
    return (int)resultado;  // Convierte truncando los decimales
}

int validar_division(float divisor) {
    if (divisor == 0) {
        return 0;  // División no válida
    }
    if (fabs(divisor) < 0.00001) {
        yyerror("El divisor es demasiado pequeño; puede causar desbordamiento.");
        return 0;
    }
    return 1;
}
