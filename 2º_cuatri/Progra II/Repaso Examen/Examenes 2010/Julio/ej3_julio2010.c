// SE PUEDE HACER MUCHO MÁS SENCILLO GUARDANDO LAS PILAS EN UN ARRAY Y CON UN FOR IR HACIENDO LOS BUCLES UTILIZANDO pilas[i], donde i va de 0 a 2.

void crea_lista_dadas_3_pilas(TPILA *p1, TPILA *p2, TPILA *p3, TLISTA *l) {
    TIPOELEMENTO isbn; // elemento de las pilas
    TPILA aux1, aux2, aux3;
    TPOSICION pos;
    TIPOELEMENTO e; // elemento de la lista
    int existe = 0;

    crea(l); //creo la lista
    PilaVacia(&aux1);
    PilaVacia(&aux2);
    PilaVacia(&aux3);


    while (EsVacia(*p1) == 0) {
        Cima(*p1, &isbn);
        Pop(p1);
        Push(&aux1, isbn);
        
        existe = 0;

        pos = primero(*l);
        if (EsVacia(*l) == 1) {
            Inserta(l, pos, isbn);
        }
        else {
            while (pos != fin(*l)) {
                Recupera(*l, pos, &e);
                if (isbn == e) {
                    existe = 1;
                    break;
                }
                pos = siguiente(*l, pos);
            }
            if (existe == 0) {
                Inserta(l, fin(*l), isbn);
            }
        }
    }

    while (EsVacia(*p2) == 0) {
        Cima(*p2, &isbn);
        Pop(p2);
        Push(&aux2, isbn);
        
        existe = 0;

        pos = primero(*l);
        if (EsVacia(*l) == 1) {
            Inserta(l, pos, isbn);
        }
        else {
            while (pos != fin(*l)) {
                Recupera(*l, pos, &e);
                if (isbn == e) {
                    existe = 1;
                    break;
                }
                pos = siguiente(*l, pos);
            }
            if (existe == 0) {
                Inserta(l, fin(*l), isbn);
            }
        }
    }

    while (EsVacia(*p3) == 0) {
        Cima(*p3, &isbn);
        Pop(p3);
        Push(&aux3, isbn);
        
        existe = 0;

        pos = primero(*l);
        if (EsVacia(*l) == 1) {
            Inserta(l, pos, isbn);
        }
        else {
            while (pos != fin(*l)) {
                Recupera(*l, pos, &e);
                if (isbn == e) {
                    existe = 1;
                    break;
                }
                pos = siguiente(*l, pos);
            }
            if (existe == 0) {
                Inserta(l, fin(*l), isbn);
            }
        }
    }

    // Ahora, volver a dejar las pilas como estaban

    while (EsVacia(aux1) == 0) {
        Cima(aux1, &isbn);
        Pop(&aux1);
        Push(p1, isbn);
    }

    while (EsVacia(aux2) == 0) {
        Cima(aux2, &isbn);
        Pop(&aux2);
        Push(p2, isbn);
    }

    while (EsVacia(aux3) == 0) {
        Cima(aux3, &isbn);
        Pop(&aux3);
        Push(p3, isbn);
    }
}