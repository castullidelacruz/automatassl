//------------------------------------------------------CABECERAS------------------------------------------------------
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int cantidadDecimales = 0;
int cantidadOctales = 0;
int cantidadHexa = 0;

//------------------------------------------------------PROTOTIPOS------------------------------------------------------
int verifica(char* s);
int verificarCadenaVacia(char* s);
int esPalabra(const char* palabra);
int columna(int c);
void imprimirCantidad();
void procesarPunto1();
void procesarPunto2();
void procesarPunto3();
int esHexadecimal(char* s, int inicio);
int esOctal(char* s);
int esDecimal(char* s, int inicio);
int convertirCaracter(char c);
int evaluarExpresion(const char* expresion);
int precedencia(char c);
int realizarOperacion(int operando1, int operando2, char operador);
int esOperador(char c);

//------------------------------------------------------PRINCIPAL------------------------------------------------------
int main(void) {
    int opcion = 0;
    printf("Ingresar 1 para procesar cadenas (punto 1)\n");
    printf("Ingresar 2 para convertir un caracter (punto 2)\n");
    printf("Ingresar 3 para procesar una expresion matematica (punto 3)\n");
    
    scanf("%d",&opcion);
    getchar();

    if (opcion == 1) {
        procesarPunto1();
    } else if (opcion == 2) {
        procesarPunto2();
    } else if (opcion == 3) {
        procesarPunto3();
    } else {
        printf("Opcion invalida\n");
    }

    return 0;
}

//------------------------------------------------------FUNCIONES------------------------------------------------------

void procesarPunto1(){
    char cadena[100];
	int opcion = 0;

	printf("Ingresar 1 para entrada de cadena por consola\n");
	printf("Ingresa 2 para leer cadena desde archivo \n");
	scanf("%d",&opcion);
    getchar();
	if (opcion == 1){
		printf("ingresa una cadena %s",cadena);
		scanf("%99s",cadena);
		char* palabra = strtok(cadena,"#");
		while (palabra != NULL)
		{
			if (verifica(palabra)) { 
                    esPalabra(palabra); 
            }
			palabra = strtok(NULL,"#");
		}

		imprimirCantidad();
		
	} else if (opcion ==2){

		FILE* f = fopen("cadenaprueba.txt","r");

		while (fgets(cadena, sizeof(cadena), f) != NULL) {
            cadena[strcspn(cadena, "\n")] = '\0';
            char* palabra = strtok(cadena,"#");
			while (palabra != NULL)
			{
				if (verifica(palabra)) { 
                    esPalabra(palabra); 
            	}
				palabra = strtok(NULL,"#");
			}
        }
        fclose(f);

		imprimirCantidad();

	} else {
		printf("Opcion incorrecta");
	}

}

void imprimirCantidad(){
	printf("La cantidad de decimales es: %d \n", cantidadDecimales);
	printf("La cantidad de octales es: %d \n", cantidadOctales);
	printf("La cantidad de hexadecimales es: %d \n", cantidadHexa);
}

int verificarCadenaVacia(char* s) {
    if (s == NULL || s[0] == '\0') {
        printf("La cadena está vacía o es nula.\n");
        return 0;
    }
    return 1;
}


int verifica(char* s) {
    if (!verificarCadenaVacia(s)) return 0;

    int i = 0;

  
    if (s[i] == '+' || s[i] == '-') i++;

    // Hexadecimal
    if (s[i] == '0' && (s[i + 1] == 'x' || s[i + 1] == 'X')) {
        return esHexadecimal(s, i + 2);
    }

    // Octal
    if (s[i] == '0' && s[i + 1] != '\0' && s[i + 1] != '.') {
        return esOctal(s);
    }

    // Decimal
    return esDecimal(s, i);
}

int esHexadecimal(char* s, int inicio) {
    if (s[inicio] == '\0') {
        printf("No es una cadena válida: falta valor hexadecimal.\n");
        return 0;
    }

    for (int i = inicio; s[i]; i++) {
        if (!(isdigit(s[i]) || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'))) {
            printf("No es una cadena válida: '%c' no es un carácter hexadecimal.\n", s[i]);
            return 0;
        }
    }

    printf("Es una cadena válida: número hexadecimal.\n");
    return 1;
}

int esOctal(char* s) {
    for (int i = 1; s[i]; i++) {
        if (s[i] < '0' || s[i] > '7') {
            printf("No es una cadena válida: '%c' no es un carácter octal.\n", s[i]);
            return 0;
        }
    }

    printf("Es una cadena válida: número octal.\n");
    return 1;
}

int esDecimal(char* s, int inicio) {
    int punto_encontrado = 0;
    int tiene_digitos = 0;

    for (int i = inicio; s[i]; i++) {
        if (s[i] == '.') {
            if (punto_encontrado) {
                printf("No es una cadena válida: múltiples puntos en el número.\n");
                return 0;
            }
            punto_encontrado = 1;
        } else if (!isdigit(s[i])) {
            printf("No es una cadena válida: '%c' no es un dígito válido.\n", s[i]);
            return 0;
        } else {
            tiene_digitos = 1;
        }
    }

    if (!tiene_digitos) {
        printf("No es una cadena válida: no contiene dígitos.\n");
        return 0;
    }

    printf("Es una cadena válida: número decimal.\n");
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
	static int tt[11][26] ={{5,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1},
							{2,2,2,2,2,2,2,2,2,2,9,9,9,9,9,9,9,9,9,9,9,9,3,9,9,9},
							{2,2,2,2,2,2,2,2,2,2,9,9,9,9,9,9,9,9,9,9,9,9,3,9,9,9},
							{4,4,4,4,4,4,4,4,4,4,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{4,4,4,4,4,4,4,4,4,4,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{6,6,6,6,6,6,6,6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,3,7,7,9},
							{6,6,6,6,6,6,6,6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
							{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9},
							{8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9},
							{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
						  };
	int e=0;
	int i=0;
	int c=palabra[0];

	
	while(c!='\0'&& e!=9){
		e=tt[e][columna(c)];
		i++;
		c=palabra[i];
	}
	if(e==5 || e==1 || e==2 || e == 4){
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

void procesarPunto2(){
	char c;
    int entero;

    printf("Ingresar el caracter a convertir\n");
    scanf("%c", &c);
	getchar();
    entero = convertirCaracter(c);

    printf("El caracter '%c' convertido es: %d\n", c, entero);
}

int convertirCaracter(char c) {
    return c - '0';
}

void procesarPunto3(){
	char expresion[100];
    int opcion;

    printf("Ingresar 1 para entrada de cadena por consola\n");
    printf("Ingresar 2 para leer cadena desde archivo\n");
    scanf("%d", &opcion);
    getchar(); 

    if (opcion == 1) {
        printf("Ingresa una expresion matematica: ");
        fgets(expresion, sizeof(expresion), stdin);
        expresion[strcspn(expresion, "\n")] = '\0'; 

        int resultado = evaluarExpresion(expresion);
        printf("Resultado: %d\n", resultado);

    } else if (opcion == 2) {
        FILE* f = fopen("expresionprueba.txt", "r");
        if (f == NULL) {
            printf("No se pudo abrir el archivo.\n");
            return;
        }
        while (fgets(expresion, sizeof(expresion), f) != NULL) {
            expresion[strcspn(expresion, "\n")] = '\0'; 
            int resultado = evaluarExpresion(expresion);
            printf("Expresion: %s\n", expresion);
            printf("Resultado: %d\n", resultado);
        }
        fclose(f);

    } else {
        printf("Opción incorrecta.\n");
    }
}

int evaluarExpresion(const char* expresion) {
    int operandos[100];  
    char operadores[100]; 
    int topOperandos = -1, topOperadores = -1;
    int i = 0, numero = 0, leyendoNumero = 0;

    while (expresion[i] != '\0') {
        char c = expresion[i];
        if (isdigit(c)) {
            numero = numero * 10 + (c - '0'); 
            leyendoNumero = 1;
        } else {
            if (leyendoNumero) {
                operandos[++topOperandos] = numero; 
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
                operadores[++topOperadores] = c; 
            }
        }
        i++;
    }


    if (leyendoNumero) {
        operandos[++topOperandos] = numero;
    }


    while (topOperadores >= 0) {
        int op2 = operandos[topOperandos--];
        int op1 = operandos[topOperandos--];
        char operador = operadores[topOperadores--];
        operandos[++topOperandos] = realizarOperacion(op1, op2, operador);
    }

    return operandos[topOperandos]; 
}

int precedencia(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}


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


int esOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}