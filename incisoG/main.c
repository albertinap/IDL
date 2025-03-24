#include <stdio.h>
#include <stdlib.h>
#include "miLibreria.h"
#define MAX_HEXA "FFFF"
#define MIN_HEXA "0000"

int numeroHexadecimalValido(char[]);
void convertirNumHexaABinario(char[], int[]);
void convertirNumBinarioADecimal(int[], char[]);
int leerNumeroHexadecimal(char[]);
int esDigitoHexa(char);
int dentroRangoHexa(char[]);
int convertirDigitoHexaABinario(char);

int main()
{
    char hexaIngresado[5]; // 0xHHHH + '\0'
    int res = numeroHexadecimalValido(hexaIngresado);

    while (res == 1)
        res = numeroHexadecimalValido(hexaIngresado);

    printf("\nEl numero en hexadecimal es: %s", hexaIngresado);

    int numeroPuntoFijo[16]; // binario
    convertirNumHexaABinario(hexaIngresado, numeroPuntoFijo);
    printf("\nEl numero en binario es: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", numeroPuntoFijo[i]);
    }

    char numeroDecimal[10]; // decimal --> �eee.ffff + '\0'
    convertirNumBinarioADecimal(numeroPuntoFijo, numeroDecimal);

    printf("\nEl numero en decimal es: %s", numeroDecimal);

    return 0;
}

int numeroHexadecimalValido(char *hexaIngresado)
{
    if (leerNumeroHexadecimal(hexaIngresado) == 1)
    {
        printf("El n�mero ingresado no cumple con el formato 0xHHHH \n");
        return 1; // no cumpli� con el formato
    }

    // si llego ac�, esta bien el formato, pero no se si est� dentro del rango
    if (dentroRangoHexa(hexaIngresado) == 2)
    {
        printf("El n�mero se sale del rango de representaci�n \n");
        return 1;
    }

    return 0; // salio todo bien
}

int esDigitoHexa(char c)
{
    // me fijo si el caracter est� entre 'A' y 'F', o '0' y '9'
    if ((c > ('A' - 1)) && (c < ('F' + 1)))
        return 0;
    if ((c > ('0' - 1)) && (c < ('9' + 1)))
        return 0;
    return 1;
}

int leerNumeroHexadecimal(char *hexaIngresado)
{
    printf("\nIngrese un n�mero hexadecimal con el siguiente formato: 0xHHHH \n");
    scanf("%s", hexaIngresado);

    printf("\nEl hexa ingresado es: %s\n", hexaIngresado);
    printf("\nLongitud es: %d\n", strlen(hexaIngresado));

    if (strlen(hexaIngresado) != 4)
    {             // entiendo que el strlen no me cuenta el terminador \0
        return 1; // hubo error en formato
    }

    int i = 0;
    int aux = esDigitoHexa(hexaIngresado[0]);
    // verifica uno por uno, que el string contenga digitos hexadecimales
    while (aux == 0 && i < 3)
    {
        i++;
        aux = esDigitoHexa(hexaIngresado[i]);
    }

    return aux; // si est� todo bien retorna 0, si no retorna 1
}

int dentroRangoHexa(char *hexaIngresado)
{

    if (strcmp(hexaIngresado, MAX_HEXA) > 0)
    {
        return 2; // no lo puedo representar
    }

    if (strcmp(hexaIngresado, MIN_HEXA) < 0)
    {
        return 2; // no lo puedo representar
    }

    return 0; // est� dentro del rango
}

int convertirDigitoHexaABinario(char c)
{
    switch (c)
    {
    case '0':
        return 0b0000; // prefijo 0b para indicar binario
    case '1':
        return 0b0001; // si no lo indico, entonces me toma
    case '2':
        return 0b0010; // como n�meros octales y no como binario
    case '3':
        return 0b0011;
    case '4':
        return 0b0100;
    case '5':
        return 0b0101;
    case '6':
        return 0b0110;
    case '7':
        return 0b0111;
    case '8':
        return 0b1000;
    case '9':
        return 0b1001;
    case 'A':
        return 0b1010;
    case 'B':
        return 0b1011;
    case 'C':
        return 0b1100;
    case 'D':
        return 0b1101;
    case 'E':
        return 0b1110;
    case 'F':
        return 0b1111;
    default:
        return -1; // hubo un error
    }
}

void convertirNumHexaABinario(char *hexaIngresado, int *numeroPuntoFijo)
{
    int i = 0; // �ndice para recorrer hexaIngresado 0xHHHH
    int j = 0; // �ndice para recorrer los bits de cada d�gito hexadecimal
    int k = 0; // �ndice para cargar los bits en numeroPuntoFijo

    // Recorro cada d�gito hexa
    for (i = 0; i < 4; i++)
    {
        // Convierto el d�gito hexa a binario de 4 bits
        int aux = convertirDigitoHexaABinario(hexaIngresado[i]);

        // Cargo los 4 bits en numeroPuntoFijo
        for (j = 3; j >= 0; j--)
        {
            // Extraigo de atr�s para adelante, y voy cargando en numeroPuntoFijo
            numeroPuntoFijo[k] = (aux >> j) & 1;
            k++; // Avanzar al siguiente bit en numeroPuntoFijo
        }
    }

    printf("\n\nA ver el binario final: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", numeroPuntoFijo[i]);
    }
}

void convertirNumBinarioADecimal(int *numeroPuntoFijo, char *numeroDecimal)
{
    // guardo signo
    int signo = numeroPuntoFijo[0];

    // extraigo parte entera (7 bits)
    int parteEntera = 0;
    for (int i = 1; i < 8; i++)
    {
        parteEntera += numeroPuntoFijo[i] * (1 << (7 - i));
    }

    // extraigo parte fraccionaria (8 bits)
    int parteFraccionaria = 0;
    for (int i = 8; i < 16; i++)
    {
        parteFraccionaria += numeroPuntoFijo[i] * (1 << (15 - i));
    }

    // combino parte entera y fraccionaria en un mismo n�mero
    int resultado = parteEntera * 256 + parteFraccionaria;
    // ac� multiplico por 256, para desplazar el numero 8 lugares (2^8) y dejar esos bits en la parte baja para meter la parte fraccionaria

    parteEntera = resultado / 256;       // parte entera real (dividir por 256)
    parteFraccionaria = resultado % 256; // parte fraccionaria real (el resto de 256)

    // genero el string en formato �eee.ffff
    sprintf(numeroDecimal, "%s%d.%04d", (signo == 1) ? "-" : "+", parteEntera, parteFraccionaria);
}
