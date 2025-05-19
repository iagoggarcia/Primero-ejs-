#include <stdio.h>
#include <stdlib.h>
#include <voraz.h>
#include <getopt.h>
#include <string.h>

char* conseguirNombre_archivo(int argc, char** argv) {
    int opt;
    char* archivo = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        archivo = (char*)malloc(strlen(optarg) * sizeof(char)); // asigno memoria
        if (archivo == NULL) {
            printf("Error en la asignación de memoria\n");
            exit(EXIT_FAILURE);
        }
        strcpy(archivo, optarg); // copia el contenido de optarg a la memoria dinámica, lo es porque si no no puedo liberar el nombre al salir del programa
    }

    if (archivo) {
        printf("Archivo: %s\n", archivo);
        return (archivo);
    }
    else {
        printf("No se introdujo el nombre del archivo\n");
    }

    return (archivo);    
}

void leer_archivo(char* nombre_archivo, TProceso* procesos) {
    FILE* archivo = NULL;
    char buffer[256]; // buffer para leer el archivo
    int i = 0; // índice para el array de procesos

    if (nombre_archivo != NULL) { // si hay nombre de archivo
        archivo = fopen(nombre_archivo, "r"); // abro el archivo
        if (archivo == NULL) { // si hubo problemas abriéndolo
            printf("Error en la apertura del archivo\n"); // imprimo mensaje de error y salgo
            return; // hago return sin nada para que salga de la función pero no del programa
        }

        while (fgets(buffer, sizeof(buffer), archivo) != NULL) { // leo el archivo línea a línea
            sscanf(buffer, "%s %d", procesos[i].id_proceso, &procesos[i].tiempo); // leo el id y el tiempo del proceso
            //printf("ID: %s, Tiempo: %d\n", proceso.id_proceso, proceso.tiempo);
            i++; // incremento el índice del array
        }

        fclose(archivo);
    }
}

int contarProcesos(char* nombre_archivo) {
    FILE* archivo = NULL;
    int n_lineas = 0; // para saber los procesos que hay y asignarle memoria al array
    char buffer[256];

    archivo = fopen(nombre_archivo, "r"); // abro el archivo en modo lectura
    if (archivo == NULL) { // si hubo problemas abriéndolo
        printf("Error en la apertura del archivo\n"); // imprimo mensaje de error y salgo
        return (EXIT_FAILURE); // hago return sin nada para que salga de la función pero no del programa
    }

    while (fgets(buffer, sizeof(buffer), archivo) != NULL) { // leo el archivo línea a línea
        n_lineas++; // cuento las líneas
    }

    fclose(archivo); // cierro el archivo

    return n_lineas;
}



// PARA LA ORDENACIÓN DEL ARRAY DE PROCESOS
void intercambiar(TProceso *a, TProceso *b) { // intercambia los valores de a y b
    TProceso t = *a; // almacena el valor de a en una variable auxiliar
    *a = *b; // asigna el valor de b a a
    *b = t;  // asigna el valor de a(almacenado en t) a b
  }
  
  int partition(TProceso *v1, int primer_elem, int ultimo_elem, int orden) {
    int pivote = v1[ultimo_elem].tiempo;
    int i = primer_elem - 1;

    for (int j = primer_elem; j < ultimo_elem; j++) {
        if ((orden == 1 && v1[j].tiempo <= pivote) || (orden == -1 && v1[j].tiempo >= pivote)) {
            i++;
            intercambiar(&v1[i], &v1[j]);
        }
    }

    intercambiar(&v1[i + 1], &v1[ultimo_elem]);
    return i + 1;
}

void quickSort(TProceso *v1, int primer_elem, int ultimo_elem, int orden) {
    if (primer_elem < ultimo_elem) {
        int pivote = partition(v1, primer_elem, ultimo_elem, orden);

        quickSort(v1, primer_elem, pivote - 1, orden);
        quickSort(v1, pivote + 1, ultimo_elem, orden);
    }
}