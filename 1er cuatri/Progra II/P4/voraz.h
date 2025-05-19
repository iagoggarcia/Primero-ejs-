#ifndef VORAZ_H
#define VORAZ_H

typedef struct {
    char id_proceso[2];
    int tiempo;
} TProceso;

void leer_archivo(char* nombre_archivo, TProceso* procesos);
char* conseguirNombre_archivo(int argc, char *argv[]);
int contarProcesos(char* nombre_archivo);
void intercambiar(TProceso *a, TProceso *b);
int partition(TProceso *v1, int primer_elem, int ultimo_elem, int orden);
void quickSort(TProceso *v1, int primer_elem, int ultimo_elem, int orden);

#endif // VORAZ_H