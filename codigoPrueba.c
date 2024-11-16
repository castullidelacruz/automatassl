#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Variables globales para contar cantidades
int cantidadDecimales = 0;
int cantidadOctales = 0;
int cantidadHexa = 0;

// Declaración de funciones
void procesarPunto1();
int esPalabra(const char* palabra);
int verificarCadenaVacia(const char* s);
int columna(int c);
void imprimirCantidad();
int evaluarExpresion(const char* expresion);
int esExpresionMatematica(const char* expresion);
int convertirCaracter(char c);
void mostrarCaracterConvertido(char c);

int main(void) {
    int opcion;

    printf("Ingresar 1 para procesar cadenas (punto 1)\n");
    printf("Ingresar 2 para procesar una expresion matematica (punto 3)\n");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    if (opcion == 1) {
        procesarPunto1();
    } else if (opcion == 2) {
        char expresion[100];
        printf("Ingresa una expresión matemática: ");
        fgets(expresion, sizeof(expresion), stdin);
        expresion[strcspn(expresion, "\n")] = '\0';

        // Validar los números en la expresión como válidos
        int esValida = esExpresionMatematica(expresion);
        
        if (esValida) {
            int resultado = evaluarExpresion(expresion);
            printf("El resultado de la expresión es: %d\n", resultado);
        } else {
            printf("La expresión matemática ingresada no es válida\n");
        }
    } else {
        printf("Opción incorrecta\n");
    }

    return 0;
}

// Procesar cadenas del punto 1
void procesarPunto1() {
    char cadena[100];
    int opcion;

    printf("Ingresar 1 para entrada de cadena por consola\n");
    printf("Ingresar 2 para leer cadena desde archivo\n");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    if (opcion == 1) {
        printf("Ingresa una cadena con números separados por '#': ");
        fgets(cadena, sizeof(cadena), stdin);
        cadena[strcspn(cadena, "\n")] = '\0';
    } else if (opcion == 2) {
        FILE* f = fopen("cadenaprueba.txt", "r");
        if (!f) {
            printf("Error al abrir el archivo\n");
            return;
        }
        fgets(cadena, sizeof(cadena), f);
        fclose(f);
        cadena[strcspn(cadena, "\n")] = '\0';
    } else {
        printf("Opción incorrecta\n");
        return;
    }

    char* palabra = strtok(cadena, "#");
    while (palabra != NULL) {
        if (esPalabra(palabra)) {
            printf("Palabra válida: %s\n", palabra);
        } else {
            printf("Palabra inválida: %s\n", palabra);
        }
        palabra = strtok(NULL, "#");
    }

    imprimirCantidad();
}

// Validar palabras como números válidos (decimales, octales, hexadecimales)
int esPalabra(const char* palabra) {
    int i = 0;

    // Si el número comienza con 0 (octal o hexadecimal)
    if (palabra[0] == '0') {
        if (palabra[1] == 'x' || palabra[1] == 'X') {
            // Verificar que los caracteres después de "0x" sean válidos en hexadecimal
            for (i = 2; palabra[i] != '\0'; i++) {
                if (!isxdigit(palabra[i])) {
                    return 0; // Número inválido, contiene caracteres no válidos
                }
            }
            cantidadHexa++; // Es hexadecimal
        } else if (palabra[1] == 'o' || palabra[1] == 'O') {
            // Verificar que los caracteres después de "0o" sean válidos en octal
            for (i = 2; palabra[i] != '\0'; i++) {
                if (palabra[i] < '0' || palabra[i] > '7') {
                    return 0; // Número inválido, contiene caracteres no válidos en octal
                }
            }
            cantidadOctales++; // Es octal
        } else {
            // Si comienza con 0 pero no es "0x" o "0o", es decimal
            for (i = 1; palabra[i] != '\0'; i++) {
                if (!isdigit(palabra[i])) {
                    return 0; // Número inválido, contiene caracteres no válidos
                }
            }
            cantidadDecimales++; // Es decimal
        }
    } else {
        // Si no comienza con 0, es un número decimal normal
        for (i = 0; palabra[i] != '\0'; i++) {
            if (!isdigit(palabra[i])) {
                return 0; // Número inválido, contiene caracteres no válidos
            }
        }
        cantidadDecimales++; // Es decimal
    }

    return 1; // Es un número válido
}


// Validar si una cadena es una expresión matemática válida
int esExpresionMatematica(const char* expresion) {
    int longitud = strlen(expresion);
    int i = 0;
    int tieneOperador = 0;
    int tieneNumero = 0;

    // Si el primer carácter es un signo, lo permitimos
    if (expresion[i] == '+' || expresion[i] == '-') {
        i++;  // Avanzamos al siguiente carácter
    }

    while (i < longitud) {
        char c = expresion[i];

        // Si encontramos un número
        if (isdigit(c)) {
            tieneNumero = 1;
        }
        // Si encontramos un operador
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // No puede haber dos operadores consecutivos ni operador al inicio
            if (!tieneNumero || tieneOperador) {
                return 0; // Error, operadores consecutivos o falta de número
            }
            tieneOperador = 1;
        } 
        // Si el carácter no es ni número ni operador, es inválido
        else {
            return 0; // Caracter no válido
        }
        i++;
    }

    // La expresión debe terminar con un número, no un operador
    return tieneNumero; 
}


// Evaluar una expresión matemática
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int evaluarExpresion(const char* expresion) {
    int longitud = strlen(expresion);
    int numeros[100]; // Array para almacenar números
    char operadores[100]; // Array para almacenar operadores
    int numIndex = 0, opIndex = 0;
    int numero = 0;
    char operador = '+';

    // Evaluación de * y / primero
    for (int i = 0; i < longitud; i++) {
        char c = expresion[i];

        if (isdigit(c)) {
            numero = numero * 10 + (c - '0');
        }

        // Cuando encontramos un operador o llegamos al final
        if ((!isdigit(c) && c != ' ') || i == longitud - 1) {
            if (operador == '+') {
                numeros[numIndex++] = numero;
            } else if (operador == '-') {
                numeros[numIndex++] = -numero;
            } else if (operador == '*') {
                numeros[numIndex - 1] *= numero;
            } else if (operador == '/') {
                if (numero == 0) {
                    printf("Error: División por cero\n");
                    return 0;
                }
                numeros[numIndex - 1] /= numero;
            }

            operador = c;
            numero = 0;
        }
    }

    // Ahora procesamos + y -
    int resultado = 0;
    for (int i = 0; i < numIndex; i++) {
        resultado += numeros[i];
    }

    return resultado;
}

void mostrarCaracterConvertido(char c) {
    int entero = convertirCaracter(c);
    printf("El carácter '%c' convertido es: %d\n", c, entero);
}

int convertirCaracter(char c) {
    return c - '0';
}

void imprimirCantidad() {
    printf("Cantidad de decimales: %d\n", cantidadDecimales);
    printf("Cantidad de octales: %d\n", cantidadOctales);
    printf("Cantidad de hexadecimales: %d\n", cantidadHexa);
}

int columna(int c) {
    switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 10;
    case 'b': return 11;
    case 'c': return 12;
    case 'd': return 13;
    case 'e': return 14;
    case 'f': return 15;
    case 'A': return 16;
    case 'B': return 17;
    case 'C': return 18;
    case 'D': return 19;
    case 'E': return 20;
    case 'F': return 21;
    case '.': return 22;
    case 'x': return 23;
    case 'X': return 24;
    default: return 25;
    }
}
