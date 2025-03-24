#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miLibreria.h"

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
