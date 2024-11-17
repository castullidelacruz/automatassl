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
void procesarPunto3();

int main(void) {
    int opcion;

    printf("Ingresar 1 para procesar cadenas (punto 1)\n");
    printf("Ingresar 2 para procesar una expresion matematica (punto 3)\n");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    if (opcion == 1) {
        procesarPunto1();
    } else if (opcion == 2) {
        procesarPunto3();
    } else {
        printf("Opcion incorrecta\n");
    }

    return 0;
}

void procesarPunto3() {
    char expresion[100];
    printf("Ingresa una expresion matematica: ");
    fgets(expresion, sizeof(expresion), stdin);
    expresion[strcspn(expresion, "\n")] = '\0';

    // Separar números y operadores
    char* token = strtok(expresion, "+-*/");
    while (token != NULL) {
        if (!esPalabra(token)) { // Reutilizar función del punto 1
            printf("Error: La expresión contiene un número inválido: %s\n", token);
            return;
        }
        token = strtok(NULL, "+-*/");
    }

    // Reconstruir la expresión para evaluarla (si es válida)
    int resultado = evaluarExpresion(expresion);
    printf("El resultado de la expresion es: %d\n", resultado);
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

    if (palabra[0] == '0') {
        if (palabra[1] == 'x' || palabra[1] == 'X') {
            for (i = 2; palabra[i] != '\0'; i++) {
                if (!isxdigit(palabra[i])) {
                    return 0;
                }
            }
            cantidadHexa++;
        } else {
            for (i = 1; palabra[i] != '\0'; i++) {
                if (palabra[i] < '0' || palabra[i] > '7') {
                    return 0;
                }
            }
            cantidadOctales++;
        }
    } else {
        for (i = 0; palabra[i] != '\0'; i++) {
            if (!isdigit(palabra[i])) {
                return 0;
            }
        }
        cantidadDecimales++;
    }

    return 1;
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
        else if (c != ' ') {
            return 0; // Caracter no válido (espacios son permitidos)
        }
        i++;
    }

    // La expresión debe terminar con un número, no un operador
    return tieneNumero; 
}
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Función para determinar la precedencia de un operador
int precedencia(char operador) {
    if (operador == '*' || operador == '/') return 2;
    if (operador == '+' || operador == '-') return 1;
    return 0;
}

// Función para realizar una operación matemática básica
int operar(int a, int b, char operador) {
    switch (operador) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                printf("Error: División por cero\n");
                return 0;
            }
            return a / b;
        default: return 0;
    }
}

// Función para evaluar una expresión matemática respetando la precedencia
int evaluarExpresion(const char* expresion) {
    int numeros[100], numTop = -1;
    char operadores[100];
    int opTop = -1;
    int i = 0, numero = 0, leyendoNumero = 0;

    while (expresion[i] != '\0') {
        char c = expresion[i];

        if (isdigit(c)) {
            numero = numero * 10 + (c - '0'); // Construir número
            leyendoNumero = 1;
        } else {
            if (leyendoNumero) {
                numeros[++numTop] = numero; // Guardar número en la pila
                numero = 0;
                leyendoNumero = 0;
            }
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                // Procesar operadores en la pila mientras tengan mayor o igual precedencia
                while (opTop >= 0 && precedencia(operadores[opTop]) >= precedencia(c)) {
                    int b = numeros[numTop--];
                    int a = numeros[numTop--];
                    char op = operadores[opTop--];
                    numeros[++numTop] = operar(a, b, op);
                }
                operadores[++opTop] = c; // Guardar operador actual en la pila
            }
        }
        i++;
    }

    if (leyendoNumero) {
        numeros[++numTop] = numero; // Guardar el último número
    }

    // Procesar los operadores restantes en la pila
    while (opTop >= 0) {
        int b = numeros[numTop--];
        int a = numeros[numTop--];
        char op = operadores[opTop--];
        numeros[++numTop] = operar(a, b, op);
    }

    return numeros[0]; // El resultado final está en la parte superior de la pila
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
