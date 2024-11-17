#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int cantidadDecimales = 0;
int cantidadOctales = 0;
int cantidadHexa = 0;

int verifica(char* s);
int verificarCadenaVacia(char* s);
int esPalabra(const char* palabra);
int imprimirCantidad();
int convertirCaracter(char c);
void mostrarCaracterConvertido();
void procesarPunto1();
void procesarPunto3();

int main(void) {
    int opcion;

    printf("Ingresar 1 para procesar cadenas (punto 1)\n");
    printf("Ingresar 2 para procesar una expresion matematica (punto 3)\n");
    printf("Ingresar 3 para convertir un caracter (punto 2)\n");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    if (opcion == 1) {
        procesarPunto1();
    } else if (opcion == 2) {
        procesarPunto3();
    } else if (opcion == 3) {
        mostrarCaracterConvertido();
    } else {
        printf("Opcion incorrecta\n");
    }

    return 0;
}


void procesarPunto1(){
    char cadena[100];
	int opcion = 0;

	printf("Ingresar 1 para entrada de cadena por consola");
	printf("Ingresa 2 para leer cadena desde archivo \n");
	scanf("%d",&opcion);
	if (opcion == 1){
		printf("ingresa una cadena %s",cadena);
		scanf("%99s",cadena);
		char* palabra = strtok(cadena,"#");
		while (palabra != NULL)
		{
			verifica(palabra);
			esPalabra(palabra);
			palabra = strtok(NULL,"#");
		}

		imprimirCantidad();
		getchar();
	} else if (opcion ==2){

		FILE* f = fopen("cadenaprueba.txt","r");

		while (fgets(cadena, sizeof(cadena), f) != NULL) {
            cadena[strcspn(cadena, "\n")] = '\0';
            char* palabra = strtok(cadena,"#");
			while (palabra != NULL)
			{
				verifica(palabra);
				esPalabra(palabra);
				palabra = strtok(NULL,"#");
			}
        }
        fclose(f);

		imprimirCantidad();

	} else {
		printf("Opcion incorrecta");
	}

}

int imprimirCantidad(){
	printf("La cantidad de decimales es: %i \n", cantidadDecimales);
	printf("La cantidad de octales es: %i \n", cantidadOctales);
	printf("La cantidad de hexadecimales es: %i \n", cantidadHexa);
}

int verificarCadenaVacia(char* s){
    if (s[0] == '\0') {
        printf("No es una cadena valida! \n");
        return 0;
    }
	return 1;
}

int verifica(char* s)
{
    verificarCadenaVacia(s);

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {

        if (s[2] == '\0') {
            printf("No es una cadena valida! \n");
            return 0;
        }


        for (int i = 2; s[i]; i++) {
            if (!(isdigit(s[i]) || 
                  (s[i] >= 'a' && s[i] <= 'f') || 
                  (s[i] >= 'A' && s[i] <= 'F')))  {
                printf("No es una cadena valida! \n");
                return 0;
            }
        }
    } else {

        for (int i = 0; s[i]; i++) {
            if (!(isdigit(s[i]) || s[i] == '+' || s[i] == '-')) {
                printf("No es una cadena valida! \n");
                return 0;
            }
        }
    }

    printf("Es una cadena valida! \n");
    return 1;
}

int columna(int c)
{	
	switch (c)
	{
	case '0':
		return 0;
		break;
	case '1':
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;
	case '7':
		return 7;
		break;
	case '8':
		return 8;
		break;
	case '9':
		return 9;
		break;
	case 'a':
		return 10;
		break;
	case 'b':
		return 11;
		break;
	case 'c':
		return 12;
		break;
	case 'd':
		return 13;
		break;
	case 'e':
		return 14;
		break;	
	case 'f':
		return 15;
		break;
	case 'A':
		return 16;
		break;
	case 'B':
		return 17;
		break;
	case 'C':
		return 18;
		break;
	case 'D':
		return 19;
		break;	
	case 'E':
		return 20;
		break;
	case 'F':
		return 21;
		break;
	case '.':
		return 22;
		break;
	case 'x':
		return 23;
		break;
	case 'X':
		return 24;
		break;	
	default:
		return 25;
		break;
	}

}

int esPalabra(const char* palabra)
{
	static int tt[10][25] ={{5,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{2,2,2,2,2,2,2,2,2,2,9,9,9,9,9,9,9,9,9,9,9,9,3,9,9},
							{2,2,2,2,2,2,2,2,2,2,9,9,9,9,9,9,9,9,9,9,9,9,3,9,9},
							{4,4,4,4,4,4,4,4,4,4,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{4,4,4,4,4,4,4,4,4,4,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{6,6,6,6,6,6,6,6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,7,7},
							{6,6,6,6,6,6,6,6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9},
							{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9},
							{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
						  };
	int e=0;
	int i=0;
	int c=palabra[0];

	
	while(c!='\0'&& e!=9){
		e=tt[e][columna(c)];
		i++;
		c=palabra[i];
	}
	if(e==2 || e == 4){
		cantidadDecimales ++;
	}

	if(e==6){
		cantidadOctales ++;
	}

	if(e==8){
		cantidadHexa ++;
	}


	return 0;

}

void mostrarCaracterConvertido() {
    char c;
    int entero;

    printf("Ingresar el caracter a convertir\n");
    scanf("%c", &c);
    entero = convertirCaracter(c);

    printf("El caracter '%c' convertido es: %d\n", c, entero);
}

int convertirCaracter(char c) {
    return c - '0';
}


#include <stdlib.h>

// Función para verificar si un carácter es un operador
int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Función para asignar precedencia a los operadores
int precedencia(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

// Función para realizar una operación entre dos operandos
int realizarOperacion(int operando1, int operando2, char operador) {
    switch (operador) {
        case '+': return operando1 + operando2;
        case '-': return operando1 - operando2;
        case '*': return operando1 * operando2;
        case '/': 
            if (operando2 == 0) {
                printf("Error: Division por cero.\n");
                exit(EXIT_FAILURE);
            }
            return operando1 / operando2;
    }
    return 0;
}

// Función para evaluar la expresión matemática
int evaluarExpresion(const char* expresion) {
    int operandos[100];  // Pila de operandos
    char operadores[100]; // Pila de operadores
    int topOperandos = -1, topOperadores = -1;
    int i = 0, numero = 0, leyendoNumero = 0;

    while (expresion[i] != '\0') {
        char c = expresion[i];
        if (isdigit(c)) {
            numero = numero * 10 + (c - '0'); // Acumular el número
            leyendoNumero = 1;
        } else {
            if (leyendoNumero) {
                operandos[++topOperandos] = numero; // Push del operando
                numero = 0;
                leyendoNumero = 0;
            }

            if (esOperador(c)) {
                while (topOperadores >= 0 && precedencia(operadores[topOperadores]) >= precedencia(c)) {
                    int op2 = operandos[topOperandos--];
                    int op1 = operandos[topOperandos--];
                    char operador = operadores[topOperadores--];
                    operandos[++topOperandos] = realizarOperacion(op1, op2, operador);
                }
                operadores[++topOperadores] = c; // Push del operador actual
            }
        }
        i++;
    }

    // Push del último número si quedó pendiente
    if (leyendoNumero) {
        operandos[++topOperandos] = numero;
    }

    // Procesar operadores restantes
    while (topOperadores >= 0) {
        int op2 = operandos[topOperandos--];
        int op1 = operandos[topOperandos--];
        char operador = operadores[topOperadores--];
        operandos[++topOperandos] = realizarOperacion(op1, op2, operador);
    }

    return operandos[topOperandos]; // El resultado final está en la cima de la pila de operandos
}

void procesarPunto3() {
    char expresion[100];
    int opcion;

    printf("Ingresar 1 para entrada de cadena por consola\n");
    printf("Ingresar 2 para leer cadena desde archivo\n");
    scanf("%d", &opcion);
    getchar(); // Limpiar el buffer

    if (opcion == 1) {
        printf("Ingresa una expresion matematica: ");
        fgets(expresion, sizeof(expresion), stdin);
        expresion[strcspn(expresion, "\n")] = '\0'; // Eliminar salto de línea

        int resultado = evaluarExpresion(expresion);
        printf("Resultado: %d\n", resultado);

    } else if (opcion == 2) {
        FILE* f = fopen("expresionprueba.txt", "r");
        if (f == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return;
        }
        while (fgets(expresion, sizeof(expresion), f) != NULL) {
            expresion[strcspn(expresion, "\n")] = '\0'; // Eliminar salto de línea
            int resultado = evaluarExpresion(expresion);
            printf("Expresion: %s\n", expresion);
            printf("Resultado: %d\n", resultado);
        }
        fclose(f);

    } else {
        printf("Opción incorrecta.\n");
    }
}
