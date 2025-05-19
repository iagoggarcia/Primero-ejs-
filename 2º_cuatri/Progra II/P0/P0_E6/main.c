/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - número de filas o columnas: 0
 * - acceder a un dato con índices negativos
 * - verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - número de filas y columnas distintos en las dos matrices
 *      - número de filas igual y de columnas distinto
 *      - número de columnas igual y de filas distinto
 */

#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    int f,c; // int i, k, f, c;
    float valor;
    matriz *a = 0, *b = 0, *aux = 0;
    char opcion, resp;


    do {
        printf("---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion); // scanf(" %c", opcion);

        switch (opcion) {
            case '0':
                printf("Saliendo del programa\n");
                break;
            case '1':
                printf("Introduzca el numero de filas de la matriz 'a': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);

                break;
            case '2':
                printf("Matriz A\n");
                if (a != 0) { // liña engadida
                    for (f = 0; f < a->filas; f++)
                        for (c = 0; c < a->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, a);
                        }
                    } // liña engadida
                else { // liña engadida
                    printf("Matriz con columnas o filas igual a 0\n"); // liña engadida
                } // liña engadida
                printf("Matriz B\n");
                if (b != 0) { // liña engadida
                    for (f = 0; f < b->filas; f++)
                        for (c = 0; c < b->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, b); // asignarElemento(f, c, valor, a);
                        }
                    } // liña engadida
                else { // liña engadida
                    printf("Matriz con columnas o filas igual a 0\n"); // liña engadida
                } // liña engadida
                break;
            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');
                if ((resp =='a' && a != 0) || (resp == 'b' && b != 0)) { // liña engadida
                    printf("Introduce fila y columna (fila columna): ");
                    scanf("%d %d", &f, &c);
                    if (resp == 'a') {
                        valor = obtenerElemento(f, c, a); // valor = obtenerElemento(f, c, b);
                        if (f>0 && c>0 && a->filas >= f && a->columnas >= c) { // liña engadida    
                            printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                        }
                    } else if (resp == 'b') {
                        valor = obtenerElemento(f, c, b); // valor = obtenerElemento(f, c, a);
                        if (f>0 && c>0 && b->filas >= f && b->columnas >= c) { // liña engadida   
                            printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                        } // liña engadida
                    }
                }    // liña engadida
                else { // liña engadida
                    printf("No es posible obtener elementos de la matriz %c\n", resp); // liña engadida
                } // liña engadida
                break;
            case '4':
                printf("Matriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                break;
            case '6':
                aux = producto(a, b);
                imprimirMatriz(aux);
                destruirMatriz(aux);
                // destruirMatriz(aux);
                break;
            case '7':
                destruirMatriz(a);
                destruirMatriz(b);
                printf("Matrices eliminadas...\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
        }
    } while (opcion != '0');

    return (EXIT_SUCCESS);
}