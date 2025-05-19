#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (*c == NULL) { // compruebo que se asigne la memoria para la clave
        printf("Error en la asignación de memoria");
        exit (EXIT_FAILURE);
    }

    (*c)->datos = (TELEMENTO *)malloc(longitud*sizeof(TELEMENTO));
    if ((*c)->datos == NULL) { // compruebo que se asigne memoria para los datos(chars) de la clave
        printf("Error en la asignación de memoria");
        exit (EXIT_FAILURE);
    }
    
    (*c)->tam = longitud;
    (*c)->cifrado = cifrado;

    for (i=0; i<longitud; i++)
        *((*c)->datos + i) = 'a';
}

void asignar(clave *c, unsigned short posicion, TELEMENTO valor) {
    *((*c)->datos + posicion) = valor + posicion*(*c)->cifrado;
}

void liberar(clave *c) {
    if (c != NULL) { // si la clave no está vacía
        free((*c)->datos); // libero los datos (chars de la clave)
        free(*c); // y luego la memoria asignada para la clave
        *c = NULL; // le pongo NULL para asegurarme de que queda vacío
    }
}

TELEMENTO recuperar(clave *c, unsigned short posicion) {
    if (c == NULL || (posicion >= (*c)->tam)) {
        return '\0';
    }
    else {
        return (*c)->datos[posicion] - posicion*(*c)->cifrado;
    }
}

unsigned short longitud(clave *c) {
    return (*c)->tam;
}

void imprimir(clave *c, char modo_op) {
    unsigned short tamanho = longitud(c);
    printf("Clave: ");
    
    if (modo_op == '0'){
        for (unsigned short i = 0; i < tamanho; i++) { // voy iterando las posiciones
            TELEMENTO caracter = recuperar(c,i);
            printf("%c", caracter); // y voy imprimiendo la clave
        }
    }
    else if (modo_op == '1') {
        for (unsigned short i = 0; i < tamanho; i++) {
            printf("*");
        }
    }
    else if (modo_op == '2') {
        unsigned short asteriscos;
        char* clave_aleatoria = (char*)malloc(longitud(c)*sizeof(char));
        if (clave_aleatoria == NULL) {
            printf("Error en la asignación de memoria");
            exit (EXIT_FAILURE);
        }


        do {
            asteriscos = 0;

            for (unsigned short i = 0;i < tamanho; i++) {
                if (rand() % 2 == 0) { // cojo un num aleatorio y puede ser tanto par como impar, si es par
                    clave_aleatoria[i] = '*'; // en vez de guardar el caracter guardo un '*'
                    asteriscos++;
                }
                else { // si es impar
                    TELEMENTO caracter = recuperar(c,i);
                    clave_aleatoria[i] = caracter; // guardo el caracter
                }
            }
        }while (asteriscos == 0 || asteriscos==longitud(c));

        printf(" %s\n", clave_aleatoria);
    }
}

char* imprimir_comprobar_partes(clave *c) {
    unsigned short tamanho = longitud(c);
    printf("Clave: ");

    unsigned short asteriscos;
    char* clave_aleatoria = (char*)malloc(longitud(c)*sizeof(char));
    if (clave_aleatoria == NULL) {
        printf("Error en la asignación de memoria");
        exit (EXIT_FAILURE);
    }


    do {
        asteriscos = 0;

        for (unsigned short i = 0;i < tamanho; i++) {
            if (rand() % 2 == 0) { // cojo un num aleatorio y puede ser tanto par como impar, si es par
                clave_aleatoria[i] = '*'; // en vez de guardar el caracter guardo un '*'
                asteriscos++;
            }
            else { // si es impar
                TELEMENTO caracter = recuperar(c,i);
                clave_aleatoria[i] = caracter; // guardo el caracter
            }
        }
    }while (asteriscos == 0 || asteriscos==longitud(c));

    return clave_aleatoria;
}


void cadena2clave(clave *c, char* cadena, unsigned short cifrado) {
    unsigned short tamanho = strlen(cadena); // no hago tamanho=longitud() porque se supone que la clave está vacía, por eso no puede saber el tamaño
    if (*c == NULL) {
        crear(c, tamanho, cifrado);
    }
    else {
        liberar(c);
        crear(c, tamanho, cifrado);
    }

    for (unsigned short i = 0; i < strlen(cadena); i++) {
        TELEMENTO caracter = cadena[i];
        asignar(c, i, caracter);
    }
}

unsigned short compruebaclave(clave *c, char modo_op) {
    unsigned short tamanho = longitud(c);

    if (modo_op == '0') {
        char* cadena = (char*)malloc(tamanho*sizeof(char));
        if (cadena == NULL) {
            printf("No se pudo asignar la memoria");
            return EXIT_FAILURE;
        }

        printf("Introduce la clave: ");
        scanf("%s", cadena);
        
        if (strlen(cadena)!=tamanho){
            return 0;
        }
        else{
            for (unsigned short i = 0; i < tamanho; i++) {
                if (cadena[i] != recuperar(c, i)) { // si algún caracter es distinto(con la clave descifrada)
                    return 0; // retorna 0 (clave incorrecta)
                }
            }
        }
        return 1; // si pasa del for es que es igual, asi que return 1(clave correcta)
    }

    else if (modo_op == '1') {
        char* cadena = imprimir_comprobar_partes(c);
        unsigned short asteriscos = 0;
        
        for (unsigned short i = 0; i<tamanho;i++) {
            if (cadena[i] == '*') {
                asteriscos++;
            }
        }
        char* chars_ocultos = (char*)malloc(asteriscos*sizeof(char)); // asigno memoria suficiente para los caracteres que están ocultos
        if (chars_ocultos == NULL) {
            printf("Error en la asignación de memoria");
            exit (EXIT_FAILURE);
        }

        char* completan_cadena = (char*)malloc(asteriscos*sizeof(char)); // asigno memoria para los caracteres que se meten por teclado
        if (chars_ocultos == NULL) {
            printf("Error en la asignación de memoria");
            exit (EXIT_FAILURE);
        }

        unsigned short j = 0; /*esta variable la uso para colocar las letras ocultas de forma seguida, ya que si utilizara el i del bucle habría casos
        en los que saltaría a la siguiente posición por no ser asterisco y chars_ocultos solo tiene de tamaño máximo el número de asteriscos*/
        for (unsigned short i = 0; i<tamanho;i++) {
            if (cadena[i] == '*') {
                chars_ocultos[j] = recuperar(c,i);
                j++;
            }
        }
        printf("Clave encriptada: %s\n", cadena);
        
        printf("Introduce el o los caracteres que falten de la clave: ");
        scanf(" %s", completan_cadena);

        for (unsigned short i = 0; i < tamanho; i++) {
            if (completan_cadena[i] != chars_ocultos[i]) { // si algún caracter es distinto(con los chars descifrados previamente)
                return 0; // retorna 0 (clave incorrecta)
            }
        }

        return 1;
    }
}


/* Esta función hace lo mismo que void imprimir(clave *c, "0") pero en vez de imprimir la clave
   descifrada, la devuelve como char para usarla al salir del programa en el main y escribirla
   en el archivo*/
char* obtenerClave(clave *c) {
    unsigned short tamanho = longitud(c);
    char* contrasenha = (char*)malloc((tamanho) * sizeof(char)); // le asigno memoria
    if (contrasenha == NULL) {
        printf("Error en la asignación de memoria\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned short i = 0; i < tamanho; i++) { // voy iteranddo las posiciones
        TELEMENTO caracter = recuperar(c, i); // consigo los caracteres de la clave descifrados
        contrasenha[i] = caracter; // los guardo en el char que se devolverá
    }
    contrasenha[tamanho] = '\0'; // le añado el fin de cadena, si no daba problemas

    return contrasenha; // Retorno la cadena dinámica
}
