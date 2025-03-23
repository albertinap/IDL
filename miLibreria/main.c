#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miLibreria.h"

#define MAX "+127.9960" //10 char \n
#define MIN "-128"

int main() {
    saludar();
    printf("La suma de 3 y 5 es: %d\n", sumar(3, 5));
    return 0;
}
