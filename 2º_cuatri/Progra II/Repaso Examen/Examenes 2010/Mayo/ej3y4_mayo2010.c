#include <stdlib.h>
#include <stdio.h>

void VaciaHasta3(TPILA *p) {
    while (EsVacia(*p) == 0 && Cima(*p) != 3) {
        Pop(p);
    }
}

void crea_Cola_dada_una_Pila(TPILA *p1) {
    TPILA p2;
    PilaVacia(&p2);
    TELEMENTO e;

    while (EsVacia(*p1) == 0) {
        Cima(*p1, &e);
        Pop(p1);
        Push(&p2, e);
    }

    TCOLA q;
    ColaVacia(&q);
    while (EsVacia(p2) == 0) {
        Cima(p2, &e);
        Pop(p2);
        anadirCola(&q, e);
    }
}