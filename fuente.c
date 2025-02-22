#include<stdio.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>

// ER: ([1-9][0-9]* | 0(\.[0-9]+)?) | 0([0-7]+) | 0[xX]([0-9a-fA-F]+)

// Variables globales para contar cantidades
int cantidadDecimales = 0;
int cantidadOctales = 0;
int cantidadHexa = 0;

int verifica(char* s);
int verificarCadenaVacia(char* s);
int esPalabra(const char* palabra);
int imprimirCantidad();
int convertirCaracter();

int main(void){

    return 0;
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

int convertirCaracter(){
	char caracter;
	int entero = 0;

	printf("Ingresa un caracter: \n");
	scanf("%c", &caracter);
	entero = caracter - '0';
	printf("El valor ingresado es: %i",entero);
	return 0;
}