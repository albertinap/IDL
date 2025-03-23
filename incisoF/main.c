#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miLibreria.h"

#define MAX "+127.9960" //10 char \n
#define MIN "-128"

int esDigito(char); //función para verificar que un char es un número
int leerNumero(char[]);
int numeroValido(char[]);
int dentroRango(char[]);
void convertirNumABinario(char[], int[]);
void convertirNumBinarioAHexa(int[], char[]);
char convertirDigitoBinarioAHexa(char[]);
void sumarBinarios(int[], int[]);

int main()
{

    char numIngresado [10]; //±eee.ffff + '\0'
    int res=numeroValido(numIngresado);

    while(res==1)
        res=numeroValido(numIngresado);

    printf("El numero en decimal es: %s", numIngresado);

    int numeroPuntoFijo [16]; //binario
    convertirNumABinario(numIngresado, numeroPuntoFijo);
    printf("\nEl numero en binario es: ");
    for (int i=0; i<16; i++){
        printf("%d", numeroPuntoFijo[i]);
    }

    char numeroHexa [4]; //hexadecimal 0xHHHH
    convertirNumBinarioAHexa(numeroPuntoFijo,numeroHexa);

    printf("\nEl numero en hexadecimal es: %s",numeroHexa);

    return 0;
}

int numeroValido(char* numIngresado){

    if (leerNumero(numIngresado)==1){
        printf("El número ingresado no cumple con el formato ±eee.ffff \n");
        return 1; //no cumplió con el formato
    }

    //si llego acá, esta bien el formato, pero no se si está dentro del rango
    if(dentroRango(numIngresado)==2){
        printf("El número se sale del rango de representación \n");
        return 1;
    }

    return 0; //salio todo bien
}


int esDigito(char){
    //me fijo si el caracter está entre '0' y '9'
    if (char>47 && char<58)
        return 0;

    return 1;
}

int leerNumero(char* numIngresado){

    printf("\nIngrese un número con el siguiente formato: ±eee.ffff \n");
    scanf(" %s", numIngresado);

    if(numIngresado[0] != '+' && numIngresado[0] != '-')
        return 1; //hubo error en formato

    if(numIngresado[4] != '.'){
        return 1; //hubo error en formato
    }

    if(strlen(numIngresado) != 9){
        return 1; //hubo error en formato
    }

    int i=1;
    int aux=esDigito(numIngresado[i]);
    //verifica uno por uno, que el string contenga números donde corresponde
    while(aux==0 && i<10){
        if(i!=4)
            aux=esDigito(numIngresado[i]);
        i++;
    }

    return aux; //si está todo bien retorna 0, si no retorna 1
}

int dentroRango(char* numIngresado){

    if(numIngresado[0] == '+'){
        if(strcmp(numIngresado,MAX)>0){
            return 2; //no lo puedo representar
        }
        return 0;
    }

    if(strcmp(numIngresado, MIN)>0){
        return 2; //no lo puedo representar
    }

    return 0;
}

void convertirNumABinario(char* numIngresado, int* numeroPuntoFijo){

    numeroPuntoFijo[0]=0;

    int parteEntera= (numIngresado[1]-48)*100 + (numIngresado[2]-48)*10 + numIngresado[3]-48;

    for (int i=1; i<8; i++){
        numeroPuntoFijo[8-i]= (parteEntera%2);
        parteEntera = parteEntera/2;
    }

    int parteFraccionaria= (numIngresado[5]-48)*1000 + (numIngresado[6]-48)*100 + (numIngresado[7]-48)*10 + numIngresado[8]-48;

    for (int i=8; i<16; i++){
        parteFraccionaria*=2;

        if (parteFraccionaria>9999){
            numeroPuntoFijo[i]=1;
            parteFraccionaria-=10000;
        }
        else
            numeroPuntoFijo[i]=0;

    }

    if(numIngresado[0]=='-'){
        for (int k=0;k<16;k++)
            numeroPuntoFijo[k]=!numeroPuntoFijo[k];
        int aux [16]={0};
        aux [15]=1;
        sumarBinarios(numeroPuntoFijo, aux);
    }
}

void convertirNumBinarioAHexa(int* numEnBinario, char* numeroHexa){
    static char aux [4];
    int j=0; int i=0;
    for(j=0;j<4;j++){
        for(i=0;i<4;i++){
            aux[i]=numEnBinario[((j*4)+i)]+48;
        }
        numeroHexa[j]=convertirDigitoBinarioAHexa(aux);
        i=0;
    }
}

char convertirDigitoBinarioAHexa(char* c){
    if (strcmp(c, "0000")==0)
        return '0';
    if (strcmp(c, "0001")==0)
        return '1';
    if (strcmp(c, "0010")==0)
        return '2';
    if (strcmp(c, "0011")==0)
        return '3';
    if (strcmp(c, "0100")==0)
        return '4';
    if (strcmp(c, "0101")==0)
        return '5';
    if (strcmp(c, "0110")==0)
        return '6';
    if (strcmp(c, "0111")==0)
        return '7';
    if (strcmp(c, "1000")==0)
        return '8';
    if (strcmp(c, "1001")==0)
        return '9';
    if (strcmp(c, "1010")==0)
        return 'A';
    if (strcmp(c, "1011")==0)
        return 'B';
    if (strcmp(c, "1100")==0)
        return 'C';
    if (strcmp(c, "1101")==0)
        return 'D';
    if (strcmp(c, "1110")==0)
        return 'E';
    if (strcmp(c, "1111")==0)
        return 'F';
}

void sumarBinarios(int* sumando, int*sumador){
    int longitud=16;
    int carry=0;
    int aux=0;
    //le resto 1 a las posiciones porque el vector va desde la pos 0, hasta la 15
    for (int i=0;i<longitud;i++){

        aux=carry+sumando[longitud-i-1]+sumador[longitud-i-1];

        if(aux==0){
            carry=0;
            sumando[longitud-i-1]=0;
        }
        else if(aux==1){
            carry=0;
            sumando[longitud-i-1]=1;
        }
        else if(aux==2){
            carry=1;
            sumando[longitud-i-1]=0;
        }
        else if(aux==3){
            carry=1;
            sumando[longitud-i-1]=1;
        }
    }
}
