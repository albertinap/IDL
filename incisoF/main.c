#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX "+127.9960"
#define MIN "-128"

int esDigito(char);
int numeroValido(char*);
int leerNumero(char*);
int dentroRango(char*);
int convertirNumABinario(char*);
void convertirNumBinarioAHexa(int, char*);
char convertirDigitoBinarioAHexa(int);

int main()
{
    char numIngresado[10]; // (+/-)eee.ffff + '\0'
    int res = numeroValido(numIngresado);

    while (res == 1)
        res = numeroValido(numIngresado);

    printf("El numero en decimal es: %s", numIngresado);

    int numeroPuntoFijo; // binario
    numeroPuntoFijo=convertirNumABinario(numIngresado);

    printf("\nEl numero FINAL en binario es: ");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (numeroPuntoFijo >> i) & 1);  // Extraer cada bit individual
    }

    char numeroHexa[4]={0}; // hexadecimal 0xHHHH
    convertirNumBinarioAHexa(numeroPuntoFijo, numeroHexa);

    printf("\nEl numero en hexadecimal es:");
    printf("%.*s\n", 4, numeroHexa);  // Imprime "ABCD"

    return 0;
}

int esDigito(char c)
{
    return (c >= '0' && c <= '9') ? 0 : 1;
}

int numeroValido(char *numIngresado)
{

    if (leerNumero(numIngresado) == 1)
    {
        printf("El numero ingresado no cumple con el formato (+/-)eee.ffff \n");
        return 1; // no cumpli� con el formato
    }

    // si llego ac�, esta bien el formato, pero no se si est� dentro del rango
    if (dentroRango(numIngresado) == 2)
    {
        printf("El numero se sale del rango de representacion \n");
        return 1;
    }

    return 0; // salio todo bien
}

int leerNumero(char *numIngresado)
{

    printf("\nIngrese un numero con el siguiente formato: +eee.ffff o -eee.ffff \n");
    scanf(" %s", numIngresado);

    if (numIngresado[0] != '+' && numIngresado[0] != '-')
        return 1; // hubo error en formato

    if (numIngresado[4] != '.')
    {
        return 1; // hubo error en formato
    }

    if (strlen(numIngresado) != 9)
    {
        return 1; // hubo error en formato
    }

    int i = 1;
    int aux = esDigito(numIngresado[i]);
    // verifica uno por uno, que el string contenga n�meros donde corresponde
    while (aux == 0 && i < 9)
    {
        if (i != 4)
            aux = esDigito(numIngresado[i]);
        i++;
    }

    return aux; // si est� todo bien retorna 0, si no retorna 1
}

int dentroRango(char *numIngresado)
{

    if (numIngresado[0] == '+')
    {
        if (strcmp(numIngresado, MAX) > 0)
        {
            return 2; // no lo puedo representar
        }
        return 0;
    }

    if (strcmp(numIngresado, MIN) > 0)
    {
        return 2; // no lo puedo representar
    }

    return 0;
}

int convertirNumABinario(char *numIngresado){
    int numeroPuntoFijo = 0;
    char signo=numIngresado[0];

    // Extraer la parte entera
    int parteEntera = (numIngresado[1] - '0') * 100 + (numIngresado[2] - '0') * 10 + (numIngresado[3] - '0');

    // Convertir parte fraccionaria a binario
    int parteFraccionaria = (numIngresado[5] - '0') * 1000 + (numIngresado[6] - '0') * 100 +
                            (numIngresado[7] - '0') * 10 + (numIngresado[8] - '0');

    int fraccionBinaria = 0;
    for (int i = 0; i < 8; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 10000) {
            fraccionBinaria |= (1 << (7 - i));
            parteFraccionaria -= 10000;
        }
    }

    numeroPuntoFijo= parteEntera & 0x7F;
    numeroPuntoFijo = (numeroPuntoFijo*256)|fraccionBinaria;

    printf("\nEl numero ANTES en binario es: ");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (numeroPuntoFijo >> i) & 1);  // Extraer cada bit individual
    }

    // Si es negativo, aplicar complemento a 2
    if (numIngresado[0] == '-') {
        numeroPuntoFijo = (~numeroPuntoFijo -1);  // Complemento a 2 en 16 bits
    }


    return numeroPuntoFijo;
}

void convertirNumBinarioAHexa(int numEnBinario, char *numeroHexa)
{
    unsigned short int aux; //set de 4 bits

    int j = 0;
    for (j = 0; j < 4; j++)
    {
        aux = numEnBinario>>(4*j) & 0b1111;
        numeroHexa[j] = convertirDigitoBinarioAHexa(aux);
    }

}

char convertirDigitoBinarioAHexa(int unChar)
{
    switch (unChar){
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            return -1; //hubo un error
    }
}
