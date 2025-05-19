#include "matriz.h"

float obtenerElemento(int fila, int columna, matriz *M) {
    float x; // int x;

    if (M != 0) {
        fila = fila - 1; // liña engadida
        columna = columna - 1; // liña engadida
        if ((fila < 0 || fila >= M->filas) || (columna < 0 || columna >= M->columnas)) { // if ((fila < 0 || fila > M->filas) || (columna < 0 || columna > M->columnas)) {
            printf("Ese elemento no existe\n");
            return 0;
        }
        x = *((M->datos) + fila * M->columnas + columna);
        return x;
    } else { // else
        printf("La matriz no existe\n");
        return 0; // liña engadida
    } // liña engadida
}
