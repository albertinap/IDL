#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miLibreria.h"

int main()
{

    char numIngresado[10]; // �eee.ffff + '\0'
    int res = numeroValido(numIngresado);

    while (res == 1)
        res = numeroValido(numIngresado);

    printf("El numero en decimal es: %s", numIngresado);

    int numeroPuntoFijo[16]; // binario
    convertirNumABinario(numIngresado, numeroPuntoFijo);
    printf("\nEl numero en binario es: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d", numeroPuntoFijo[i]);
    }

    char numeroHexa[4]; // hexadecimal 0xHHHH
    convertirNumBinarioAHexa(numeroPuntoFijo, numeroHexa);

    printf("\nEl numero en hexadecimal es: %s", numeroHexa);

    return 0;
}
