#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tiempos.h"

void inicializaVectorRand(int *v1, int n, int modo_op) {
    if (modo_op == 1) { // si se quiere hacer la búsqueda de pares
        for (int i = 0; i < n; i++) {
            v1[i] = rand() % 101; // genero números entre 0 y 100
        }
    }
    else if (modo_op == 2 || modo_op == 3) { // si se quiere hacer quicksort
        for (int i = 0; i < n; i++) {
            v1[i] = rand() % 10001; // genero números entre 0 y 10.000
        }
    }
}

void busquedaPares(int *v1, int n, int cantidad) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((v1[i] + v1[j]) == cantidad) {
                printf("%d + %d = %d\n", v1[i], v1[j], cantidad);
            }
        }
    }
}

// Función para intercambiar los valores de dos elementos
void intercambiar(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
  }
  
  // Función para encontrar la posición de la partición
int particionar(int *v1, int bajo, int alto) {
    
    // Seleccionamos el último elemento como pivote
  int pivote = v1[alto];
    
    // Puntero para el elemento mayor
  int i = (bajo - 1);
  
    // Recorremos cada elemento del v1
    // y lo comparamos con el pivote
  for (int j = bajo; j < alto; j++) {
    if (v1[j] <= pivote) {          
        // Si encontramos un elemento menor que el pivote
        // lo intercambiamos con el elemento mayor apuntado por i
      i++;
        
        // Intercambiamos el elemento en i con el elemento en j
      intercambiar(&v1[i], &v1[j]);
    }
  }
  
    // Intercambiamos el pivote con el elemento mayor en i
  intercambiar(&v1[i + 1], &v1[alto]);
    
    // Retornamos el punto de partición
  return (i + 1);
}
  
void quickSort(int *v1, int bajo, int alto) {
  if (bajo < alto) {
      
      // Encontramos el pivote tal que
      // los elementos menores que el pivote estén a la izquierda del pivote
      // y los elementos mayores que el pivote estén a la derecha del pivote
    int pivote = particionar(v1, bajo, alto);
      
      // Llamada recursiva sobre la parte izquierda del pivote
    quickSort(v1, bajo, pivote - 1);
      
      // Llamada recursiva sobre la parte derecha del pivote
    quickSort(v1, pivote + 1, alto);
  }
}
  

void insertionSort(int *v1, int tamanho) {
  for (int paso = 1; paso < tamanho; paso++) {
    int clave = v1[paso];
    int j = paso - 1;
  
      // Compara la clave con cada elemento a su izquierda hasta encontrar
      // un elemento más pequeño que ella.
      // Para orden descendente, cambia clave < v1[j] por clave > v1[j].
    while (j >= 0 && clave < v1[j]) {
      v1[j + 1] = v1[j]; // Mueve el elemento hacia la derecha
      --j;
    }
    v1[j + 1] = clave; // Coloca la clave en su posición correcta
  }
} 


void imprimirVector(int *v1, int n) {
  printf("Vector ordenado:\n");
  for (int i = 0; i < n; i++) {
      printf("%d ", v1[i]);
  }
  printf("\n");
}