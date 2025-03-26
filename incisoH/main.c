#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 65535.99997
#define min -65536.00000
#define maxM "0.999969"
#define minM "-1.000000"
#define maxB "127.9960"
#define minB "-128.0000"

int esDigito(char);
int numeroValidoB(char*);
int dentroRangoB(char*);
int leerNumeroB(char*);

int numeroValidoM(char*);
int dentroRangoM(char*);
int leerNumeroM(char*);

int validarX(char *, long int, long int);
int dentroRangoX(char *, long int, long int);
int leerNumeroX(char*);

long int convertirNumXABinario(char*);
long int convertirNumBABinario(char*);
long int convertirNumMABinario(char*);

void convertirNumBinarioAHexa(long int, char*);
char convertirDigitoBinarioAHexa(int);



int main()
{
    //ingresar los valores de m, b, x, luego validar la entrada
    int res;

    char b[17]; //Q(7,8) y un bit para '/0'
    res = numeroValidoB(b);
    while (res == 1)
        res = numeroValidoB(b);

    long int bb; // binario
    bb=convertirNumBABinario(b);

    printf("\n\nla variable B en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (bb >> i) & 1);  // Extraer cada bit individual
    }

    char m[17]; //Q(0,15) y un bit para '/0'
    res = numeroValidoM(m);
    while (res == 1)
        res = numeroValidoM(m);

    long int mb; // binario
    mb=convertirNumMABinario(m); //ya queda en Q(16,15)

    //aca es donde tengo que ver que si el valor de x hace que y tenga overflow


    long int prueba= (bb*mb);
    printf("\n\nla variable calculo en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (prueba >> i) & 1);  // Extraer cada bit individual
    }

    char x[33];//Q(16,15) y un bit para '/0'
    res = validarX(x, bb, mb);

    while (res == 1)
        res = validarX(x, bb, mb);

    int binarioX=convertirNumXABinario(x);


    /*

    //--------------------------------------------------------------

    int xb; // binario
    xb=convertirNumXABinario(x);

    printf("\nla variable x en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (xb >> i) & 1);  // Extraer cada bit individual
    }

    char xh[8]; // hexadecimal 0xHHHHHHHH
    convertirNumBinarioAHexa(xb, xh);

    printf("\nla variable x en hexadecimal es: %.*s\n",8,xh);


    //--------------------------------------------------------------

    int bb; // binario
    bb=convertirNumBABinario(b); //ya queda en Q(16,15)
    printf("\nla ordenada al origen b en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (bb >> i) & 1);  // Extraer cada bit individual
    }

    char bh[8];
    convertirNumBinarioAHexa(bb, bh);

    printf("\nla ordenada al origen b hexadecimal es: %.*s\n",8, bh);

    //--------------------------------------------------------------

    int mb; // binario
    mb=convertirNumMABinario(m); //ya queda en Q(16,15)
    printf("\nla pendiente m en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (mb >> i) & 1);  // Extraer cada bit individual
    }

    char mh[8]; // hexadecimal 0xHHHHHHHH
    convertirNumBinarioAHexa(mb, mh);

    printf("\nla pendiente m en hexadecimal es: %.*s\n",8, mh);

    //---------------------------------------------------------------------


    int ordenada = (convertirNumMABinario(m) * convertirNumXABinario(x))/32768 + convertirNumBABinario(b);

    char ordenadaDecimal[12];
    convertirNumBinarioADecimal(ordenada,ordenadaDecimal);
    printf("La ordenada es: %s", ordenada);

    char yh[8]; // hexadecimal 0xHHHHHHHH
    convertirNumBinarioAHexa(ordenada,yh);
    printf("\nla ordenada al origen b hexadecimal es: %.*s\n",8, yh);
*/
    return 0;
}

//------------------METODOS NUESTROS------------------------------------------------

//devuelve 0 si esta bien
int esDigito(char c){
    return (c >= '0' && c <= '9') ? 0 : 1;
}

//----------------METODOS PARA LEER Y VALIDAR B-------------------------------------
//devuelve 0 si b es valido, 1 o 2 si no lo es
int numeroValidoB(char*b){
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

int dentroRangoB(char *b){
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
int validarX(char *x, long int b, long int m){
    if (leerNumeroX(x) == 1)
    {
        printf("El numero ingresado no cumple con el formato +eeeee.fffff o -eeeee.fffff\n");
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
int dentroRangoX(char *x, long int b, long int m)
{

    //tengo que devolver 2 si hay overflow y 0 si no lo hay
    int xpf = convertirNumXABinario(x);

    printf("\nla variable X en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (xpf >> i) & 1);  // Extraer cada bit individual
    }
    printf("\nla variable M en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (m >> i) & 1);  // Extraer cada bit individual
    }
    printf("\nla variable B en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (b >> i) & 1);  // Extraer cada bit individual
    }

    int calculoAux =(m*xpf)+b;

    printf("\nla variable Y en binario es: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (calculoAux >> i) & 1);  // Extraer cada bit individual
    }

    char ystring [12];
    convertirNumBinarioADecimal(calculoAux,ystring);
    printf("\n\nEL VALOR DE Y: %s",ystring);

    if (calculoAux > (max) || calculoAux < (min))
        return 2;

    return 0;
}

//----------METODOS PARA CONVERTIR NUMEROS DE STRING A BINARIOS Q(16,15)------------

long int convertirNumBABinario(char* b){ //+- eee.ffff
    int numeroPuntoFijo = 0;
    char signo=b[0];

    // Extraer la parte entera (+-)eee.ffff
    int parteEntera = (b[1] - '0')* 100 + (b[2] - '0') * 10 + (b[3] - '0');

    // Extraer la parte fraccionaria
    int parteFraccionaria = (b[5] - '0') * 1000 + (b[6] - '0') * 100 + (b[7] - '0') * 10 + (b[8] - '0');

    int fraccionBinaria = 0;
    for (int i = 0; i < 8; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 10000) {
            fraccionBinaria |= (1 << (7 - i));
            parteFraccionaria -= 10000;
        }
    }

    numeroPuntoFijo= parteEntera & 0xFFFF;
    numeroPuntoFijo = (numeroPuntoFijo*256)|fraccionBinaria;

    long int b32 = 0x00000000;
    b32=numeroPuntoFijo;
    b32 = b32 << 7; //Q(7,8)

    int signoBinario= b32&0b0000000001000000000000000000; //para signo

    if(signoBinario!=0){
        b32= b32^0b10000000010000000000000000000000; //para actualizar los signos
    }

    if(signo=='-'){
        b32=(~b32-1);
    }

    return b32;
}

long int convertirNumMABinario(char* numIngresado){
    int numeroPuntoFijo = 0;
    char signo=numIngresado[0];

    // Extraer la parte entera (+-)e.ffffff
    int parteEntera = (numIngresado[1] - '0');

    //si es -1 directamente lo devuelvo
    if(parteEntera==1)
        return 0xFFFFFFFF;

    // Extraer la parte fraccionaria
    int parteFraccionaria = (numIngresado[3] - '0') * 100000 + (numIngresado[4] - '0') * 10000 +
                            (numIngresado[5] - '0') * 1000 + (numIngresado[6] - '0')*100 + (numIngresado[7] - '0')*10 + (numIngresado[8] - '0');

    int fraccionBinaria = 0;
    for (int i = 0; i < 15; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 1000000) {
            fraccionBinaria |= (1 << (14 - i));
            parteFraccionaria -= 1000000;
        }
    }

    numeroPuntoFijo = fraccionBinaria & 0x7FFF;

    int m32 = 0x00000000;
    m32=numeroPuntoFijo;

    int signoBinario= m32&0b00000000000000001000000000000000; //para signo

    if(signoBinario!=0){
        m32= m32^0b10000000000000001000000000000000; //para actualizar los signos
    }

    if(signo=='-'){
        m32=(~m32-1);
    }

    return m32;
}


long int convertirNumXABinario(char* numIngresado){

    long int numeroPuntoFijo = 0;
    char signo=numIngresado[0];

    // Extraer la parte entera (+-)eeeee.fffff
    int parteEntera = (numIngresado[1] - '0') * 10000 + (numIngresado[2] - '0') * 1000 +
                            (numIngresado[3] - '0') * 100 + (numIngresado[4] - '0')*10 + (numIngresado[5] - '0')*1;

    // Extraer la parte fraccionaria
    int parteFraccionaria = (numIngresado[7] - '0') * 10000 + (numIngresado[8] - '0') * 1000 +
                            (numIngresado[9] - '0') * 100 + (numIngresado[10] - '0')*10 + (numIngresado[11] - '0')*1;

    int fraccionBinaria = 0; //Q(16,15)
    for (int i = 0; i < 15; i++) {
        parteFraccionaria *= 2;
        if (parteFraccionaria >= 100000) {
            fraccionBinaria |= (1 << (14 - i));
            parteFraccionaria -= 100000;
        }
    }

    numeroPuntoFijo = parteEntera & 0xFFFF;
    numeroPuntoFijo = (numeroPuntoFijo*32768)|fraccionBinaria;

    if(signo=='-'){
        numeroPuntoFijo=(~numeroPuntoFijo-1);
    }

    return numeroPuntoFijo;
}

//convierte un numero de 32 bits de Q(16,15) a un decimal (+/-)eeeee.fffff
void convertirNumBinarioADecimal(int numeroPuntoFijo, char *numeroDecimal)
{
    // Extraer el bit de signo (bit 15)
    int signo = (numeroPuntoFijo >> 31) & 1;
    // Extraer parte entera (16 bits, posiciones 30 a 15)
    int parteEntera = (numeroPuntoFijo >> 30) & 0b1111111111111111;
    // Extraer parte fraccionaria (15 bits, posiciones 14 a 0)
    int parteFraccionaria = numeroPuntoFijo & 0b0111111111111111;

    // Para números negativos: calcular el valor absoluto
    if (signo == 1) {
        // Invertir bits y restar 1 (ca2)
        int valorAbsoluto = (~numeroPuntoFijo - 1) & 0x7FFFFFFF; // Máscara para 15 bits
        parteEntera = (valorAbsoluto >> 15) & 0x7FFF;
        parteFraccionaria = valorAbsoluto & 0b0111111111111111;
    }

    // Calcular la parte fraccionaria como valor decimal (0.xxxxx)
    int fraccionEscalada = (parteFraccionaria * 100000) / 512;  // Escalar a 5 decimales

    // Formatear el resultado
    sprintf(numeroDecimal, "%s%d.%d",(signo == 1) ? "-" : "+",parteEntera,fraccionEscalada);
}

void convertirNumBinarioAHexa(long int numEnBinario, char *numeroHexa){
    unsigned short int aux; //set de 4 bits

    int j = 0;
    for (j = 0; j < 8; j++){
        aux = numEnBinario>>(4*j) & 0b1111;
        numeroHexa[j] = convertirDigitoBinarioAHexa(aux);
    }
}

char convertirDigitoBinarioAHexa(int unChar){
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
