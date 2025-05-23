typedef struct{
    long proceso;
    int prioridad;
} TELEMENTO;

typedef struct celda {
    TELEMENTO elemento;
    struct celda * sig;} TCELDA;

typedef TCELDA * POSICION;

typedef struct lista {
    POSICION inicio;
    int longitud;
    POSICION fin;
} * TLISTA;

typedef TLISTA TCOLAPRIO;


long primeroColaPrio(TCOLAPRIO procesosencolados) {
    POSICION pos;
    long prioritario = 0;
    int prioridadMax = 0;

    if (esVacia(procesosencolados)) {
        return -1;
    }
    else {
        pos = primero(procesosencolados);
        while (pos != fin(procesosencolados)) {
            if (pos->elemento.prioridad > prioridadMax) {
                prioridadMax = pos->elemento.prioridad;
                prioritario = pos->elemento.proceso;
            }
            pos = Siguiente(procesosencolados, pos);
        }
    }
    return prioritario;
}