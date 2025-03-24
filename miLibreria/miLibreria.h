#ifndef MILIBRERIA_H_INCLUDED
#define MILIBRERIA_H_INCLUDED
#define MAX "+127.9960"
#define max 127.9960 * 256
#define MIN "-128"
#define min -128.0 * 256
// Declaraci�n de funciones

// verifica si un char es un n�mero. Retorna 0 si es digito, y 1 caso contrario
int esDigito(char);

// lee un n�mero decimal escrito en string y verifica que sea una entrada valida:
// o sea que cumpla con el formato �eee.ffff; y que est� dentro de un rango preestablecido
// retorna 0 si el n�mero es valido, y 1 en caso contrario
int numeroValido(char *);

// lee un n�mero decimal de teclado en formato string, y verifica que cumpla con el formato �eee.ffff
// devuelve 0 si el formato es v�lido, y 1 en caso contrario
int leerNumero(char *);

// verifica que un n�mero decimal escrito en formato string est� dentro de un rango
// retorna 0 si est� dentro, y 2 en caso contrario
int dentroRango(char *);

// convierte un n�mero decimal escrito en string, a un n�mero en binario
// retorna el n�mero en binario en la variable pasada por par�metro
void convertirNumABinario(char *, int *);

// convierte un n�mero en binario, a un n�mero en hexadecimal 0xHHHH
// retorna el n�mero en hexa en la variable pasada por par�metro
void convertirNumBinarioAHexa(int *, char *);

// convierte un set de cuatro d�gitos binarios, a un n�mero en hexa
// retorna el hexadecimal correspondiente
char convertirDigitoBinarioAHexa(char *);

// suma dos n�meros binarios, teniendo en cuenta los carrys
void sumarBinarios(int *, int *);

#endif // MILIBRERIA_H_INCLUDED
