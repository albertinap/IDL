#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include "../miLibreria/miLibreria.h"*/

/******************************************************************************************************************************************************************************************** */
#define MAX "+127.9960"
#define MIN "-128"
#define min (-128.0 * 256)
#define max (127.9960 * 256)

int esDigito(char);
int numeroValido(char *);
int leerNumero(char *);
int dentroRango(char *);
void convertirNumABinario(char *, int *);
void convertirNumBinarioAHexa(int *, char *);
char convertirDigitoBinarioAHexa(char *);
void sumarBinarios(int *, int *);
/********************************************************************************************************************************************************************************************* */
int convertirAEnteroPF(char *);
int validarX(char *, char *, char *);
void mostrarNumeroEnHexa(int);
int dentroRangoX(char *x, char *b, char *m);

int main()
{
    /*ingresar los valores de m, b, x, luego validar la entrada*/
    int res;
    char b[10];
    res = numeroValido(b);

    while (res == 1)
        res = numeroValido(b);

    char m[10];
    res = numeroValido(m);

    while (res == 1)
        res = numeroValido(m);

    /*aca es donde tengo que ver que si el valor de x hace que y tenga overflow*/
    char x[10];
    res = validarX(x, b, m);

    while (res == 1)
        res = validarX(x, b, m);

    printf("todos los valores son validos");
    /*--------------------------------------------------------------*/
    int xb[16]; // binario
    convertirNumABinario(x, xb);
    printf("\nla variable x en binario es: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", xb[i]);
    }

    char xh[4]; // hexadecimal 0xHHHH
    convertirNumBinarioAHexa(xb, xh);

    printf("\nla variable x en hexadecimal es: %s", xh);
    /*------------------*/
    int bb[16]; // binario
    convertirNumABinario(b, bb);
    printf("\nla ordenada al origen b en binario es: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", bb[i]);
    }

    char bh[4]; // hexadecimal 0xHHHH
    convertirNumBinarioAHexa(bb, bh);

    printf("\nla ordenada al origen b hexadecimal es: %s", bh);
    /*------------------ */
    int mb[16]; // binario
    convertirNumABinario(m, mb);
    printf("\nla pendiente m en binario es: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", mb[i]);
    }

    char mh[4]; // hexadecimal 0xHHHH
    convertirNumBinarioAHexa(mb, mh);

    printf("\nla pendiente m en hexadecimal es: %s", mh);
    /*---------------------------------------------------------------------*/

    int ordenada = (convertirAEnteroPF(m) * convertirAEnteroPF(x)) / 256 + convertirAEnteroPF(b);

    printf("La ordenada es: %.4f\n", ordenada / 256.0);
    mostrarNumeroEnHexa(ordenada);

    return 0;
}

/*devuelve 1 si x no es valido, 0 si lo es*/
int validarX(char *x, char *b, char *m)
{
    if (leerNumero(x) == 1)
    {
        printf("El numero ingresado no cumple con el formato +eee.ffff o -eee.ffff\n");
        return 1; // no cumplio con el formato
    }

    // si llego aca, esta bien el formato, pero no se si esta dentro del rango
    if (dentroRangoX(x, b, m) == 2)
    {
        printf("El numero se sale del rango de representacion \n");
        return 1;
    }

    return 0; // salio todo bien
}

int dentroRangoX(char *x, char *b, char *m)
{
    /*tengo que devolver 2 si hay overflow y 0 si no lo hay */
    int xpf = convertirAEnteroPF(x);
    int mpf = convertirAEnteroPF(m);
    int bpf = convertirAEnteroPF(b); /*tenemos los valores por 256*/

    printf("xpf: %d\n", xpf); // Muestra el valor convertido de x
    printf("mpf: %d\n", mpf); // Muestra el valor convertido de m
    printf("bpf: %d\n", bpf); // Muestra el valor convertido de b

    if ((mpf * xpf) / 256 + bpf > max || (mpf * xpf) / 256 + bpf < min)
        return 2;

    return 0;
}

int convertirAEnteroPF(char *n)
{
    int signo = (n[0] == '+') ? 1 : -1;
    char parteEntera[] = {n[1], n[2], n[3], '\0'};
    int result = atoi(parteEntera) * 256;
    char parteFraccionaria[] = {n[5], n[6], n[7], n[8], '\0'};
    result += (atoi(parteFraccionaria) * 256 / 10000);
    return result * signo;
}

void mostrarNumeroEnHexa(int numero)
{
    // Imprime el número en formato hexadecimal
    printf("El numero en hexadecimal es: 0x%X\n", numero);
}
/*A PARTIR DE ACA PONGO TODAS LAS FUNCIONES QUE USO DE LA BIBLIOTECA PORQUE SINO NO ME ANDA*/
int esDigito(char c)
{
    return (c >= '0' && c <= '9') ? 0 : 1;
}

int numeroValido(char *numIngresado)
{

    if (leerNumero(numIngresado) == 1)
    {
        printf("El n�mero ingresado no cumple con el formato �eee.ffff \n");
        return 1; // no cumpli� con el formato
    }

    // si llego ac�, esta bien el formato, pero no se si est� dentro del rango
    if (dentroRango(numIngresado) == 2)
    {
        printf("El numero se sale del rango de representaci�n \n");
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

void convertirNumABinario(char *numIngresado, int *numeroPuntoFijo)
{

    numeroPuntoFijo[0] = 0;

    int parteEntera = (numIngresado[1] - 48) * 100 + (numIngresado[2] - 48) * 10 + numIngresado[3] - 48;

    for (int i = 1; i < 8; i++)
    {
        numeroPuntoFijo[8 - i] = (parteEntera % 2);
        parteEntera = parteEntera / 2;
    }

    int parteFraccionaria = (numIngresado[5] - 48) * 1000 + (numIngresado[6] - 48) * 100 + (numIngresado[7] - 48) * 10 + numIngresado[8] - 48;

    for (int i = 8; i < 16; i++)
    {
        parteFraccionaria *= 2;

        if (parteFraccionaria > 9999) /*no lo entiendo porque no pones mayor o igual a 1*/
        {
            numeroPuntoFijo[i] = 1;
            parteFraccionaria -= 10000;
        }
        else
            numeroPuntoFijo[i] = 0;
    }

    if (numIngresado[0] == '-')
    {
        for (int k = 0; k < 16; k++)
            numeroPuntoFijo[k] = !numeroPuntoFijo[k];
        int aux[16] = {0};
        aux[15] = 1;
        sumarBinarios(numeroPuntoFijo, aux);
    }
}

void convertirNumBinarioAHexa(int *numEnBinario, char *numeroHexa)
{
    static char aux[4];
    int j = 0;
    int i = 0;
    for (j = 0; j < 4; j++)
    {
        for (i = 0; i < 4; i++)
        {
            aux[i] = numEnBinario[((j * 4) + i)] + 48;
        }
        numeroHexa[j] = convertirDigitoBinarioAHexa(aux);
        i = 0;
    }
}

char convertirDigitoBinarioAHexa(char *c)
{
    if (strcmp(c, "0000") == 0)
        return '0';
    if (strcmp(c, "0001") == 0)
        return '1';
    if (strcmp(c, "0010") == 0)
        return '2';
    if (strcmp(c, "0011") == 0)
        return '3';
    if (strcmp(c, "0100") == 0)
        return '4';
    if (strcmp(c, "0101") == 0)
        return '5';
    if (strcmp(c, "0110") == 0)
        return '6';
    if (strcmp(c, "0111") == 0)
        return '7';
    if (strcmp(c, "1000") == 0)
        return '8';
    if (strcmp(c, "1001") == 0)
        return '9';
    if (strcmp(c, "1010") == 0)
        return 'A';
    if (strcmp(c, "1011") == 0)
        return 'B';
    if (strcmp(c, "1100") == 0)
        return 'C';
    if (strcmp(c, "1101") == 0)
        return 'D';
    if (strcmp(c, "1110") == 0)
        return 'E';
    if (strcmp(c, "1111") == 0)
        return 'F';
}

void sumarBinarios(int *sumando, int *sumador)
{
    int longitud = 16;
    int carry = 0;
    int aux = 0;
    // le resto 1 a las posiciones porque el vector va desde la pos 0, hasta la 15
    for (int i = 0; i < longitud; i++)
    {

        aux = carry + sumando[longitud - i - 1] + sumador[longitud - i - 1];

        if (aux == 0)
        {
            carry = 0;
            sumando[longitud - i - 1] = 0;
        }
        else if (aux == 1)
        {
            carry = 0;
            sumando[longitud - i - 1] = 1;
        }
        else if (aux == 2)
        {
            carry = 1;
            sumando[longitud - i - 1] = 0;
        }
        else if (aux == 3)
        {
            carry = 1;
            sumando[longitud - i - 1] = 1;
        }
    }
}
