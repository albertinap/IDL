#ifndef MILIBRERIA_H_INCLUDED
#define MILIBRERIA_H_INCLUDED

// Declaración de funciones

//verifica si un char es un número. Retorna 0 si es digito, y 1 caso contrario
int esDigito(char);

//lee un número decimal escrito en string y verifica que sea una entrada valida:
//o sea que cumpla con el formato ±eee.ffff; y que esté dentro de un rango preestablecido
//retorna 0 si el número es valido, y 1 en caso contrario
int numeroValido(char[]);

//lee un número decimal de teclado en formato string, y verifica que cumpla con el formato ±eee.ffff
//devuelve 0 si el formato es válido, y 1 en caso contrario
int leerNumero(char[]);

//verifica que un número decimal escrito en formato string esté dentro de un rango
//retorna 0 si está dentro, y 2 en caso contrario
int dentroRango(char[]);

//convierte un número decimal escrito en string, a un número en binario
//retorna el número en binario en la variable pasada por parámetro
void convertirNumABinario(char[], int[]);

//convierte un número en binario, a un número en hexadecimal 0xHHHH
//retorna el número en hexa en la variable pasada por parámetro
void convertirNumBinarioAHexa(int[], char[]);

//convierte un set de cuatro dígitos binarios, a un número en hexa
//retorna el hexadecimal correspondiente
char convertirDigitoBinarioAHexa(char[]);

//suma dos números binarios, teniendo en cuenta los carrys
void sumarBinarios(int[], int[]);


#endif // MILIBRERIA_H_INCLUDED
