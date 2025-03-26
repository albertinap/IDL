#include <stdio.h>
#include <stdlib.h>

int numeroHexadecimalValido(char[]);
int convertirNumHexaABinario(char[]);
void convertirNumBinarioADecimal(int, char[]);
int leerNumeroHexadecimal(char[]);
int esDigitoHexa(char);
int convertirDigitoHexaABinario(char);

int main()
{
    char hexaIngresado[5]; // 0xHHHH + '\0'
    int res = numeroHexadecimalValido(hexaIngresado);

    while (res == 1)
        res = numeroHexadecimalValido(hexaIngresado);

    printf("\nEl numero en hexadecimal es: %s", hexaIngresado);

    int numeroPuntoFijo; // binario
    numeroPuntoFijo=convertirNumHexaABinario(hexaIngresado);

    printf("\nEl numero en binario es: ");
    for (int i = 15; i >= 0; i--) {
        printf("%d", (numeroPuntoFijo >> i) & 1);  // Extraer cada bit individual
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
        printf("El numero ingresado no cumple con el formato 0xHHHH \n");
        return 1; // no cumplio con el formato
    }

    return 0; // salio todo bien
}

int esDigitoHexa(char c)
{
    // me fijo si el caracter esta entre 'A' y 'F', o '0' y '9'
    if ((c > ('A' - 1)) && (c < ('F' + 1)))
        return 0;
    if ((c > ('0' - 1)) && (c < ('9' + 1)))
        return 0;
    return 1;
}

int leerNumeroHexadecimal(char *hexaIngresado)
{
    printf("\nIngrese un numero hexadecimal con el siguiente formato: 0xHHHH \n");
    scanf("%s", hexaIngresado);

    printf("\nEl hexa ingresado es: %s\n", hexaIngresado);

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

    return aux; // si esta todo bien retorna 0, si no retorna 1
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
        return 0b0010; // como numeros octales y no como binario
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

int convertirNumHexaABinario(char *hexaIngresado)
{
    char hex[5] = "FFFF";  // Ejemplo: FFFF en hexadecimal (4 dígitos)
    int numeroPuntoFijo = 0;       // Aquí guardaremos el binario como un número entero

    // Convertir cada carácter hexadecimal a su valor binario
    for (int i = 0; i < 4; i++) {
        char c = hexaIngresado[i];
        int valor;

        if (c >= '0' && c <= '9') {
            valor = c - '0';           // Dígitos 0-9
        } else if (c >= 'A' && c <= 'F') {
            valor = 10 + (c - 'A');     // Letras mayúsculas A-F
        } else {                    //no debería entrar aca, el valor ya tendria que ser valido
            printf("Error: '%c' no es un dígito hexadecimal válido.\n", c);
        }

        // Desplazar el binario 4 bits a la izquierda y agregar el nuevo valor
        numeroPuntoFijo = (numeroPuntoFijo << 4) | valor;
    }

    return numeroPuntoFijo;

}

void convertirNumBinarioADecimal(int numeroPuntoFijo, char *numeroDecimal)
{
    // Extraer el bit de signo (bit 15)
    int signo = (numeroPuntoFijo >> 15) & 1;
    // Extraer parte entera (7 bits, posiciones 14 a 8)
    int parteEntera = (numeroPuntoFijo >> 8) & 0b01111111;
    // Extraer parte fraccionaria (8 bits, posiciones 7 a 0)
    int parteFraccionaria = numeroPuntoFijo & 0b11111111;

    // Para números negativos: calcular el valor absoluto
    if (signo == 1) {
        // Invertir bits y restar 1 (ca2)
        int valorAbsoluto = (~numeroPuntoFijo - 1) & 0x7FFF; // Máscara para 15 bits
        parteEntera = (valorAbsoluto >> 8) & 0x7F;
        parteFraccionaria = valorAbsoluto & 0xFF;
    }

    // Calcular la parte fraccionaria como valor decimal (0.xxxx)
    int fraccionEscalada = (parteFraccionaria * 10000) / 256;  // Escalar a 4 decimales

    // Formatear el resultado
    sprintf(numeroDecimal, "%s%d.%d",(signo == 1) ? "-" : "+",parteEntera,fraccionEscalada);
}
