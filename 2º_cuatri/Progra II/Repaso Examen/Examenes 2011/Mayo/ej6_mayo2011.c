// tengo 3 listas con los dnis de gente y quiero meterlos todos a una lista única

void crea_Lista_Unica(TLISTA l1, TLISTA l2, TLISTA l3, TLISTA *l_unica) {
    TPOSICION pos, posicion_lista; /*pos es para dentro de los bucles y posicion_lista para saber en que posición de la lista guardar el dni*/
    TIPOELEMENTO e;

    Crea(l_unica);

    pos = primero(l1);
    while (pos != fin(l1)) {
        recupera(l1, pos, &e);
        Inserta(l_unica, fin(*l_unica), e);
        pos = Siguiente(l1, pos);
    }
    
    pos = primero(l2);
    while (pos != fin(l2)) {
        recupera(l2, pos, &e);
        Inserta(l_unica, fin(*l_unica), e);
        pos = Siguiente(l2, pos);
    }

    pos = primero(l3);
    while (pos != fin(l3)) {
        recupera(l3, pos, &e);
        Inserta(l_unica, fin(*l_unica), e);
        pos = Siguiente(l3, pos);
    }
}