#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tiempos.h"

int pedirAlgoritmo() {
    int modo_op;
    printf("¿Qué algoritmo quieres usar?\n");
    printf("1. Búsqueda de pares\n");
    printf("2. QuickSort\n");
    printf("3. InsertionSort\n");
    printf("Elige una opción: ");
    scanf("%d", &modo_op);
    return modo_op;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <inicio> <fin> <paso>\n", argv[0]);
        return 1;
    }

    int inicio = atoi(argv[1]);
    int fin = atoi(argv[2]);
    int paso = atoi(argv[3]);

    if (inicio > fin || paso <= 0) {
        printf("Error: asegúrate de que inicio <= fin y paso > 0\n");
        return 1;
    }
    
    int modo_op = pedirAlgoritmo(); // pido el algoritmo a usar

    if (modo_op == 1) { // si se quiere hacer la búsqueda de pares
        int cantidad;
        printf("Introduce la suma que quieres conseguir: ");
        scanf("%d", &cantidad);

        FILE *archivo = fopen("tiemposBusquedaPares.txt", "w");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo");
            exit (EXIT_FAILURE);
        }

        srand(time(NULL));

        for (int n = inicio; n <= fin; n += paso) { // empiezo con n = inicio y voy sumando el paso hasta llegar al fin
            int *v1 = (int *)malloc(n * sizeof(int)); // creo el vector de tamaño n
            if (v1 == NULL) {
                printf("Error al reservar memoria");
                fclose(archivo);
                exit (EXIT_FAILURE);
            }

            inicializaVectorRand(v1, n, 1); // le doy valores aleatorios al vector

            clock_t t_inicio = clock();

            busquedaPares(v1, n, cantidad); // llamo a la función que busca los pares

            clock_t t_fin = clock();

            double tiempo = (double)(t_fin - t_inicio) / CLOCKS_PER_SEC;

            printf("n = %d, t(n) = %.4f segundos\n", n, tiempo); // imprimo n y t(n) en el archivo 
            fprintf(archivo, "%d %.4f\n", n, tiempo);  // y lo guardo en el archivo

            free(v1); // libero la memoria del vector
        }
        fclose(archivo); // cierro el archivo
    }
    else if (modo_op == 2){ // si se quiere hacer quicksort

        FILE *archivo = fopen("tiemposQuickSort.txt", "w");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo");
            exit (EXIT_FAILURE);
        }

        srand(time(NULL));

        for (int n = inicio; n <= fin; n += paso) { // empiezo con n = inicio y voy sumando el paso hasta llegar al fin
            int *v1 = (int *)malloc(n * sizeof(int)); // creo el vector de tamaño n
            if (v1 == NULL) {
                printf("Error al reservar memoria");
                fclose(archivo);
                exit (EXIT_FAILURE);
            }

            inicializaVectorRand(v1, n, 2); // le doy valores aleatorios al vector

            clock_t t_inicio = clock();

            quickSort(v1, 0, n-1); // llamo a la función que busca los pares

            clock_t t_fin = clock();

            // imprimirVector(v1, n); // para comprobar que imprime bien

            double tiempo = (double)(t_fin - t_inicio) / CLOCKS_PER_SEC;

            printf("n = %d, t(n) = %.4f segundos\n", n, tiempo); // imprimo n y t(n) en el archivo 
            fprintf(archivo, "%d %.4f\n", n, tiempo);  // y lo guardo en el archivo

            free(v1); // libero la memoria del vector
        }
        fclose(archivo); // cierro el archivo
    }
    else if (modo_op == 3) {
        FILE *archivo = fopen("tiemposInsertionSort.txt", "w");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo");
            exit (EXIT_FAILURE);
        }

        srand(time(NULL));

        for (int n = inicio; n <= fin; n += paso) { // empiezo con n = inicio y voy sumando el paso hasta llegar al fin
            int *v1 = (int *)malloc(n * sizeof(int)); // creo el vector de tamaño n
            if (v1 == NULL) {
                printf("Error al reservar memoria");
                fclose(archivo);
                exit (EXIT_FAILURE);
            }

            inicializaVectorRand(v1, n, 2); // le doy valores aleatorios al vector

            clock_t t_inicio = clock();

            insertionSort(v1, n); // llamo a la función que busca los pares

            clock_t t_fin = clock();

            // imprimirVector(v1, n); // para comprobar que ordena bien

            double tiempo = (double)(t_fin - t_inicio) / CLOCKS_PER_SEC;

            printf("n = %d, t(n) = %.4f segundos\n", n, tiempo); // imprimo n y t(n) en el archivo 
            fprintf(archivo, "%d %.4f\n", n, tiempo);  // y lo guardo en el archivo

            free(v1); // libero la memoria del vector
        }
        fclose(archivo); // cierro el archivo
    }
    

    return (EXIT_SUCCESS);
}

