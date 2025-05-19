#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

/* a) Utilizando el panel “Watch”, visualiza las siguientes expresiones, que indican la dirección de memoria
 de los respectivos elementos del array: &a[0] &a[1] &a[2] &a[3]. --> Hay que darle al + en el panel watch
 y poner &a[0] y darle al enter, repetir para los 4 elementos.

 b) ¿Cuál es el mayor y cuál el menor? Calcula la diferencia entre las direcciones de dos elementos
 consecutivos. Trata de justificar los resultados. --> La dirección más grande es la de a[3] y la menor es la
 de a[0]. Esto es porque se toma la dirección del array y la dirección del primer elemento coincide con ella,
 luego se va sumando 4 a esa dirección para avanzar dentro del array y avanzar a la dirección del siguiente
 elemento. Es decir, la diferencia entre elementos es de 4 bytes(32 bits), que es lo necesario para almacenar
 un int.

 Direcciones:
    - &a[0] --> 0x7fffffffd9a0 = &a
    - &a[1] --> 0x7fffffffd9a4 = &a[0] + 4
    - &a[2] --> 0x7fffffffd9a8 = &a[1] + 4
    - &a[3] --> 0x7fffffffd9ac = &a[2] + 4
 */

int main(int argc, char** argv)
{
    float a[4], num1, num2, num3, num4;
    float c[4];

    printf("Escribe os 4 elementos do array: ");
    scanf("%f %f %f %f", &num1,&num2, &num3, &num4);
    while ( ( num1 < 0) || ( num2 < 0) || ( num3 < 0) || ( num4 < 0)){
        printf("Non hai raíces de números negativos, introduce 4 elementos positivos: ");
        scanf("%f %f %f %f", &num1,&num2, &num3, &num4);
    }

    a[0] = num1;
    a[1] = num2;
    a[2] = num3;
    a[3] = num4;
 
    

    for (int i = 0; i < 4; i++){
        c[i] = sqrt(a[i]);
    }

    printf("O array raíz cadrada é: [%f, %f, %f, %f]\n", c[0], c[1], c[2], c[3]);

    return (EXIT_SUCCESS);
}
