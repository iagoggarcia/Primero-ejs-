#include <stdio.h>
#include <stdlib.h>
#include <voraz.h>
#include <string.h>

int main (int argc, char *argv[]) {
    TProceso* procesos = NULL; // array donde guardaré los procesos
    char* nombre_archivo = NULL;
    int n_lineas; // para saber los procesos que hay y asignarle memoria al array
    char opcion[1]; // para saber si se quiere odenar creciente o decrecientemente
    int tiempo_espera = 0;
    
    
    nombre_archivo = conseguirNombre_archivo(argc, argv); // llamo a la función que me devuelve el nombre del archivo
    
    n_lineas = contarProcesos(nombre_archivo); // llamo a la función que cuenta los procesos y me devuelve el número de líneas del archivo

    procesos = (TProceso*)malloc(n_lineas * sizeof(TProceso)); // asigno memoria para el array de procesos
    if (procesos == NULL) { // si hubo problemas asignando memoria
        printf("Error en la asignación de memoria\n"); // imprimo mensaje de error y salgo
        return (EXIT_FAILURE); // hago return sin nada para que salga de la función pero no del programa
    }

    leer_archivo(nombre_archivo, procesos); // llamo a la función que lee el archivo

    do {
        printf("\n------------------\na) Ordenar de forma creciente \nb) Ordenar de forma decreciente\n------------------\n");
        scanf("%s", opcion); // leo la opción del usuario
    
        if (strcmp(opcion, "a") == 0) { // si la opción es 'a'
            quickSort(procesos, 0, n_lineas - 1, 1); // llamo a la función que ordena el array de procesos
        }
        else if (strcmp(opcion, "b") == 0) { // si la opción es 'b'
            quickSort(procesos, 0, n_lineas - 1, -1); // llamo a la función que ordena el array de procesos
        }
        else {
            printf("Opción no válida. Introduce 'a' o 'b'.\n");
        }
    } while (strcmp(opcion, "a") != 0 && strcmp(opcion, "b") != 0);
    

    for (int j = 0; j < n_lineas; j++) { // imprimo el array de procesos
        printf("%s, %d\n", procesos[j].id_proceso, procesos[j].tiempo);
    }

    int tiempo_acumulado = 0; // Variable para acumular los tiempos
    for (int i = 0; i < n_lineas - 1; i++) { // Es hasta n_lineas - 1 porque no se cuenta el tiempo del último proceso
        tiempo_acumulado += procesos[i].tiempo; // Acumula el tiempo del proceso actual
        tiempo_espera += tiempo_acumulado; // Suma el tiempo acumulado al tiempo de espera total
    }

    printf("\nTiempo de espera total: %d\n", tiempo_espera); // imprimo el tiempo de espera total

    return (EXIT_SUCCESS);
}