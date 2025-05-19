#include <stdio.h>
#include <stdlib.h>

typedef char TELEMENTO;
typedef struct {
    TELEMENTO *datos;
    unsigned short tam;
    unsigned short cifrado;
}STCLAVE;

typedef STCLAVE *clave;

void crear(clave *c, unsigned short longitud, unsigned short cifrado) {
    unsigned short i;

    *c = (clave)malloc(sizeof(STCLAVE));
    (*c)->datos = (TELEMENTO *)malloc(longitud*sizeof(TELEMENTO));
    (*c)->tam = longitud;
    (*c)->cifrado = cifrado;

    for (i=0; i<longitud; i++)
        *((*c)->datos + i) = 'a';
}

void asignar(clave *c, unsigned short posicion, TELEMENTO valor) {
    *((*c)->datos + posicion) = valor + posicion*(*c)->cifrado;
}