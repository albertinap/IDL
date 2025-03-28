#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define max ((int64_t)2147483647)
#define min ((int64_t)-2147483648)
#define maxX "+65535.99997" 
#define minX "-65536.00000"
#define maxM "+0.999969"
#define minM "-1.000000"
#define maxB "+127.9960"
#define minB "-128.0000"

int esDigito(char);
int numeroValidoB(char * );
int dentroRangoB(char*);
int leerNumeroB(char*);

int numeroValidoM(char*);
int dentroRangoM(char*);
int leerNumeroM(char * ); 

int validarX(char *, int32_t , int32_t );
int dentroRangoX(char *, int32_t , int32_t );
int leerNumeroX(char* );
int xvalido(char *);

int32_t convertirNumXABinario(char*);
int32_t convertirNumBABinario(char*);
int32_t convertirNumMABinario(char*);

void imprimirQ16_15(int64_t );


int main()
{
    int res;

    char b[17]; //Q(7,8) y un bit para '/0'
    res = numeroValidoB(b);
    while (res == 1)
        res = numeroValidoB(b);

    int32_t bb; // binario
    bb=convertirNumBABinario(b);

    char m[17]; //Q(0,15) y un bit para '/0'
    res = numeroValidoM(m);
    while (res == 1)
        res = numeroValidoM(m);

    int32_t mb; // binario
    mb = convertirNumMABinario(m); //ya queda en Q(16,15)

    char x[33];//Q(16,15) y un bit para '/0'
    res = validarX(x, bb, mb);

    while (res == 1)
        res = validarX(x, bb, mb);
    
    int32_t xb=convertirNumXABinario(x);
    
    int64_t y;
    y=(int64_t)mb * (int64_t)xb;
    y >>=15;
    y += (int64_t)bb;
    
    printf("Valor de y en hexadecimal: 0x%08X\n", y);
    imprimirQ16_15(y);
    
    return 0;
}

//------------------METODOS NUESTROS------------------------------------------------

//devuelve 0 si esta bien
int esDigito(char c){
    return (c >= '0' && c <= '9') ? 0 : 1;
}

//----------------METODOS PARA LEER Y VALIDAR B-------------------------------------
//devuelve 0 si b es valido, 1 o 2 si no lo es
int numeroValidoB(char* b ){
    if (leerNumeroB(b) == 1){
        printf("El numero ingresado no cumple con el formato +eee.ffff o -eee.ffff\n");
        return 1; // no cumplio con el formato
    }

    // si llego aca, esta bien el formato, pero no se si esta dentro del rango
    if (dentroRangoB(b) == 2){
        printf("El numero se sale del rango de representacion \n");
        return 1;
    }

    return 0; // salio todo bien
}

//devuelve 0 si b es valido, 1 si no lo es
int leerNumeroB(char *b){
    printf("\nIngrese un numero (B) con el siguiente formato: +eee.ffff o -eee.ffff \n");
    scanf(" %s", b);

    if (b[0] != '+' && b[0] != '-')
        return 1; // hubo error en formato

    if (b[4] != '.')
        return 1; // hubo error en formato

    if (strlen(b) != 9)
        return 1; // hubo error en formato

    int i = 1;
    int aux = esDigito(b[i]);
    // verifica uno por uno, que el string contenga n�meros donde corresponde
    while (aux == 0 && i < 9){
        if (i != 4)
            aux = esDigito(b[i]);
        i++;
    }

    return aux; // si esta todo bien retorna 0, si no retorna 1
}

int dentroRangoB(char * b){
    if (b[0] == '+'){
        if (strcmp(b, maxB) > 0)
            return 2; // no lo puedo representar
        return 0;
    }

    if (strcmp(b, minB) > 0)
        return 2; // no lo puedo representar

    return 0;
}


//----------------METODOS PARA LEER Y VALIDAR M-------------------------------------
int numeroValidoM(char* m){
    if (leerNumeroM(m) == 1)
    {
        printf("El numero ingresado no cumple con el formato +e.ffffff o -e.ffffff\n");
        return 1; // no cumplio con el formato
    }

    // si llego aca, esta bien el formato, pero no se si esta dentro del rango
    if (dentroRangoM(m) == 2)
    {
        printf("El numero se sale del rango de representacion \n");
        return 1;
    }

    return 0; // salio todo bien
}

int leerNumeroM(char *numIngresado){
    printf("\nIngrese un numero (M) con el siguiente formato: +e.ffffff o -e.ffffff \n");
    scanf(" %s", numIngresado);

    if (numIngresado[0] != '+' && numIngresado[0] != '-')
        return 1; // hubo error en formato

    if (numIngresado[2] != '.')
        return 1; // hubo error en formato


    if (strlen(numIngresado) != 9)
        return 1; // hubo error en formato

    int i = 1;
    int aux = esDigito(numIngresado[i]);
    // verifica uno por uno, que el string contenga n�meros donde corresponde
    while (aux == 0 && i < 9){
        if (i != 2)
            aux = esDigito(numIngresado[i]);
        i++;
    }

    return aux; // si est� todo bien retorna 0, si no retorna 1
}

int dentroRangoM(char *m){
    if (m[0] == '+'){
        if (strcmp(m, maxM) > 0)
            return 2; // no lo puedo representar
        return 0;
    }

    if (strcmp(m, minM) > 0)
        return 2; // no lo puedo representar

    return 0;
}


//----------------METODOS PARA LEER Y VALIDAR X-------------------------------------

/*devuelve 1 si x no es valido, 0 si lo es*/
int validarX(char * x, int32_t bb, int32_t mb){
    if (leerNumeroX(x) == 1)
    {
        printf("El numero ingresado no cumple con el formato +eeeee.fffff o -eeeee.fffff\n");
        return 1; // no cumplio con el formato
    }

    // si llego aca, esta bien el formato, pero no se si esta dentro del rango
    if (dentroRangoX(x, bb, mb) == 2)
    {
        printf("El numero se sale del rango de representacion \n");
        return 1;
    }

    return 0; // salio todo bien
}

// Valida el formato "+eeeee.fffff" o "-eeeee.fffff" (5 enteros + 5 fraccionarios)
int leerNumeroX(char *numIngresado) {
    printf("\nIngrese un numero (X) con formato: +eeeee.fffff o -eeeee.fffff\n");
    scanf("%s", numIngresado);

    // Validar longitud exacta (12 caracteres)
    if (strlen(numIngresado) != 12) {
        return 1; // Error: longitud incorrecta
    }

    // Validar signo (+/-)
    if (numIngresado[0] != '+' && numIngresado[0] != '-') {
        return 1; // Error: signo inválido
    }

    // Validar punto decimal en posición 6 (índice 5)
    if (numIngresado[6] != '.') {
        return 1; // Error: punto mal ubicado
    }

    // Validar dígitos (parte entera: posiciones 1-5, fraccionaria: 7-11)
    for (int i = 1; i < 12; i++) {
        if (i != 6) { // Ignorar el punto
            if (esDigito(numIngresado[i]) != 0) {
                return 1; // Error: carácter no es dígito
            }
        }
    }
    return 0; // Éxito: formato válido
}

//devuelve 0 si esta bien, 2 si esta mal
int dentroRangoX(char * x, int32_t bb, int32_t mb)
{

    //devuelvo 2 si x en si no es valido
    if(xvalido(x) == 2)
        return 2;
    int32_t xpf = convertirNumXABinario(x);

    int64_t calculoAux;
    calculoAux=(int64_t)mb * (int64_t)xpf;
    calculoAux >>=15;
    calculoAux += (int64_t)bb;
    
    if (calculoAux > (max) || calculoAux < (min))
        return 2;

    return 0;
}
//devuelve 2 si x en si es no valido
int xvalido(char * x)
{
    if (x[0] == '+'){
        if (strcmp(x, maxX) > 0)
            return 2; // no lo puedo representar
        return 0;
    }

    if (strcmp(x, minX) > 0)
        return 2; // no lo puedo representar

    return 0;
}

//----------METODOS PARA CONVERTIR NUMEROS DE STRING A BINARIOS Q(16,15)------------

int32_t convertirNumBABinario(char * b ){ //+- eee.ffff
    int16_t numeroPuntoFijo = 0;
    char signo=b[0];

    // Extraer la parte entera (+-)eee.ffff
    int16_t parteEntera = (b[1] - '0')* 100 + (b[2] - '0') * 10 + (b[3] - '0');

    // Extraer la parte fraccionaria
    int32_t parteFraccionaria = (b[5] - '0') * 1000 + (b[6] - '0') * 100 + (b[7] - '0') * 10 + (b[8] - '0');

    int16_t fraccionBinaria = 0;
    for (int i = 0; i < 8; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 10000) {
            fraccionBinaria |= (1 << (7 - i));
            parteFraccionaria -= 10000;
        }
    }

    numeroPuntoFijo = parteEntera << 8 ;/*dejo lugar para parte fraccionaria*/
    numeroPuntoFijo = numeroPuntoFijo | fraccionBinaria;

    int32_t b32 = 0;
    b32 = numeroPuntoFijo;
    b32 = b32 << 7; /*para que tenga la parte fraccionaria con 15 bits igual q x*/

    if(signo == '+' ){
        return b32;
    }
    else
    {
        b32= ~b32 + 1;
        return b32;
    }
}

int32_t convertirNumMABinario(char * numIngresado){
    char signo=numIngresado[0];

    // Extraer la parte entera (+-)e.ffffff
    int16_t parteEntera = (numIngresado[1] - '0');

    //si es -1 directamente lo devuelvo
    if(parteEntera==1)
        return 0xFFFF8000;

    // Extraer la parte fraccionaria
    int32_t parteFraccionaria = (numIngresado[3] - '0') * 100000 + (numIngresado[4] - '0') * 10000 +
                            (numIngresado[5] - '0') * 1000 + (numIngresado[6] - '0')*100 + (numIngresado[7] - '0')*10 + (numIngresado[8] - '0');

    int16_t fraccionBinaria = 0;
    for (int i = 0; i < 15; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 1000000) {
            fraccionBinaria |= (1 << (14 - i));
            parteFraccionaria -= 1000000;
        }
    }

    int32_t m32 = fraccionBinaria;
    if(signo == '+'){
        return m32;
    }
    else
    {
        m32 = ~m32 + 1;
        return m32;
    }
}


int32_t convertirNumXABinario(char * numIngresado){

    int32_t numeroPuntoFijo = 0;
    char signo=numIngresado[0];

    // Extraer la parte entera (+-)eeeee.fffff
    int parteEntera = (numIngresado[1] - '0') * 10000 + (numIngresado[2] - '0') * 1000 +
                            (numIngresado[3] - '0') * 100 + (numIngresado[4] - '0')*10 + (numIngresado[5] - '0');

    // Extraer la parte fraccionaria
    int parteFraccionaria = (numIngresado[7] - '0') * 10000 + (numIngresado[8] - '0') * 1000 +
                            (numIngresado[9] - '0') * 100 + (numIngresado[10] - '0')*10 + (numIngresado[11] - '0');

    int fraccionBinaria = 0; //Q(16,15)
    for (int i = 0; i < 15; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 100000) {
            fraccionBinaria |= (1 << (14 - i));
            parteFraccionaria -= 100000;
        }
    }

    numeroPuntoFijo = parteEntera << 15;
    numeroPuntoFijo = numeroPuntoFijo | fraccionBinaria;

    if(signo=='+'){
        return numeroPuntoFijo;
    }
    else
    {
        numeroPuntoFijo = ~numeroPuntoFijo + 1;
        return numeroPuntoFijo;
    }
}

//----------METODOS PARA INFORMAR Q(16,15) EN DECIMAL------------

void imprimirQ16_15(int64_t num) {
    // Extraer la parte entera y la parte fraccionaria
    int32_t parte_entera = num >> 15; // Desplazamos 15 bits para obtener la parte entera
    int32_t parte_fraccionaria = num & 0x7FFF; // Máscara para obtener los 15 bits fraccionarios

    // Si el número es negativo, ajustamos la parte fraccionaria
    if (num < 0) {
        parte_entera = -parte_entera;
        parte_fraccionaria = -parte_fraccionaria;
        if (parte_fraccionaria < 0) { // Si al negar quedó negativa, corregimos
            parte_fraccionaria += 1 << 15;
            parte_entera -= 1;
        }
        printf("-");
    }

    // Imprimir la parte entera
    printf("%d.", parte_entera);

    // Convertir la parte fraccionaria a decimal sin usar flotantes
    int32_t fraccion_decimal = (parte_fraccionaria * 100000) >> 15; // Aproximamos a 5 decimales

    // Imprimir la parte fraccionaria con ceros iniciales si es necesario
    printf("%05d\n", fraccion_decimal);
}
