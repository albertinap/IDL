#include <stdio.h>
#include <stdlib.h>
#include "miLibreria.h"
#define MAX_HEXA "FFFF"
#define MIN_HEXA "0000"

int numeroHexadecimalValido(char[]);
void convertirNumHexaABinario(char[],int[]);
void convertirNumBinarioADecimal (int[],char[]);
int leerNumeroHexadecimal(char[]);
int esDigitoHexa(char);
int dentroRangoHexa(char[]);
char convertirDigitoHexaABinario(char[]);

int main()
{
    char hexaIngresado [5]; //0xHHHH + '\0'
    int res=numeroHexadecimalValido(hexaIngresado);

    while(res==1)
        res=numeroHexadecimalValido(hexaIngresado);

    printf("\nEl numero en hexadecimal es: %s", hexaIngresado);

    int numeroPuntoFijo [16]; //binario
    convertirNumHexaABinario(hexaIngresado, numeroPuntoFijo);
    printf("\nEl numero en binario es: ");
    for (int i=0; i<16; i++){
        printf("%d", numeroPuntoFijo[i]);
    }

    char numeroDecimal [10]; //decimal --> ±eee.ffff + '\0'
    convertirNumBinarioADecimal(numeroPuntoFijo,numeroDecimal);

    printf("\nEl numero en hexadecimal es: %s",numeroDecimal);

    return 0;
}



int numeroHexadecimalValido(char[] hexaIngresado){
    if (leerNumeroHexadecimal(hexaIngresado)==1){
        printf("El número ingresado no cumple con el formato 0xHHHH \n");
        return 1; //no cumplió con el formato
    }

    //si llego acá, esta bien el formato, pero no se si está dentro del rango
    if(dentroRangoHexa(hexaIngresado)==2){
        printf("El número se sale del rango de representación \n");
        return 1;
    }

    return 0; //salio todo bien
}

int esDigitoHexa(char){
    //me fijo si el caracter está entre 'A' y 'Z', o '0' y '9'
    if ((char>(A-1) && char<(Z+1))
        return 0;
    if (char>47 && char<58)
        return 0;
    return 1;
}

int leerNumeroHexadecimal(char* hexaIngresado){
    printf("\nIngrese un número hexadecimal con el siguiente formato: 0xHHHH \n");
    scanf(" %s", hexaIngresado);

    if(strlen(hexaIngresado) != 5){
        return 1; //hubo error en formato
    }

    int i=0;
    int aux=esDigitoHexa(hexaIngresado[0]);
    //verifica uno por uno, que el string contenga digitos hexadecimales
    while(aux==0 && i<5){
        aux=esDigitoHexa(hexaIngresado[i]);
        i++;
    }

    return aux; //si está todo bien retorna 0, si no retorna 1
}

int dentroRangoHexa(char* hexaIngresado){

    if(strcmp(hexaIngresado,MAX_HEXA)>0){
        return 2; //no lo puedo representar
    }

    if(strcmp(hexaIngresado, MIN_HEXA)>0){
        return 2; //no lo puedo representar
    }

    return 0; //está dentro del rango
}

int convertirDigitoHexaABinario(char c){
    if (c=='0')
        return 0000;
    if (c=='1')
        return 0001;
    if (c=='2')
        return 0010;
    if (c=='3')
        return 0011;
    if (c=='4')
        return 0100;
    if (c=='5')
        return 0101;
    if (c=='6')
        return 0110;
    if (c=='7')
        return 0111;
    if (c=='8')
        return 1000;
    if (c=='9')
        return 1001;
    if (c=='A')
        return 1010;
    if (c=='B')
        return 1011;
    if (c=='C')
        return 1100;
    if (c=='D')
        return 1101;
    if (c=='E')
        return 1110;
    if (c=='F')
        return 1111;
}

void convertirNumHexaABinario(char[],int[]){
    int i=0;
    for(i=0;i<4;i++){

    }
}

void convertirNumBinarioADecimal (int[],char[]){
}



