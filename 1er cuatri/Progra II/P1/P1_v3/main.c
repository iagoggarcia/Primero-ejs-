#include <stdio.h>
#include <stdlib.h>
#include "clave.h"

int main(int argc, char** argv) {
    clave clave1 = NULL; // lo pongo como null porque cadena2clave detectaba que no estaba vacío y por eso no le creaba espacio
    unsigned short l, cifrado, posicion;
    TELEMENTO valor;
    char opcion;

    if (argc >= 3) {
        unsigned long cifrado = strtoul(argv[argc - 1], NULL, 10); // transformo el char '9' (por ejemplo) a unsigned long para poder operar con él
    
        l = argc - 2; // la longitud de la clave es la cantidad de argumentos menos el nombre del programa y el número para el cifrado (2 en total)
        // printf("Longitud: %d\n", l); // para comprobar que se guarda correctamente la longitud de la clave
    
        crear(&clave1, l, cifrado); // creo espacio para guardar los valores
            
        for (unsigned short i = 1; i < argc - 1; i++) { // salto el nombre del programa para leer los caracteres de la clave y paro antes del cifrado
            asignar(&clave1, i - 1, argv[i][0]); // los voy guardando con asignar, es argv[i][0] y no argv[0] porque son tipo TELEMENTO
        }
    
        // imprimir(&clave1, '0'); // para comprobar que se guarda correctamente la clave
    
        // printf("\nNúmero de cifrado: %lu\n", cifrado); // para comprobar que se guarda correctamente el cifrado
    }
    
    do{
        printf("\n--------------------\n");
        printf("\na) Crea clave");
        printf("\nb) Liberar clave");
        printf("\nc) Recuperar posición de una clave");
        printf("\nd) Longitud de la clave");
        printf("\ne) Imprimir clave sin ocultar caracteres");
        printf("\nf) Imprime clave ocultando todos los caracteres");
        printf("\ng) Imprime clave ocultando algunos caracteres");
        printf("\nh) Crea clave a partir de cadena de texto");
        printf("\ni) Comprueba contraseña(completa)");
        printf("\nj) Comprueba contraseña(partes)");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);
        switch(opcion){
            case 'a':
                if (clave1 == NULL) {
                    printf("Introduce el tamanho de la clave: ");
                    scanf("%hu", &l);
                    printf("Introduce el número para cifrar la clave: ");
                    scanf("%hu", &cifrado);
                    crear(&clave1, l, cifrado);
                    /*Asigno valores a la clave a partir de lo que teclea el
                    usuario*/
                    for (posicion=0; posicion<l; posicion++) {
                        printf("Elemento %d de la clave: ", posicion);
                        scanf(" %c", &valor);
                        asignar(&clave1, posicion, valor);
                    }
                }
                else {
                    liberar(&clave1);
                    if (clave1 == NULL) { // compruebo que la clave se liberó correctamente
                        printf("Clave liberada para crear otra nueva\n");
                        
                        printf("Introduce el tamanho de la clave: ");
                        scanf("%hu", &l);
                        
                        printf("Introduce el número para cifrar la clave: ");
                        scanf("%hu", &cifrado);
                        
                        crear(&clave1, l, cifrado);
                        /*Asigno valores a la clave a partir de lo que teclea el
                        usuario*/
                        for (posicion=0; posicion<l; posicion++) {
                            printf("Elemento %d de la clave: ", posicion);
                            scanf(" %c", &valor);
                            asignar(&clave1, posicion, valor);
                        }
                    }
                    else {
                        printf("La clave no se ha podido liberar para crear otra nueva\n");
                    }
                }
                break;
            case 'b':
                if(clave1 != NULL) {
                    liberar(&clave1);
                    if (clave1 == NULL) { // compruebo que la clave se liberó correctamente
                        printf("Clave liberada");
                    }
                    else {
                        printf("La clave no se ha podido liberar");
                    }
                }
                else{
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'c':
                if (clave1 != NULL) {
                    printf("Introduce la posición del elemento que quieres recuperar: ");
                    scanf("%hu", &posicion);
                    valor = recuperar(&clave1, posicion);
                    if (valor == '\0'){
                        printf("No existe una clave o la posición está fuera del rango");
                    }
                    else {
                        printf("Letra en la posición %d: %c", posicion, valor);
                    }
                }
                else{
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'd':
                if (clave1 != NULL) {
                    l = longitud(&clave1);
                    printf("Tamanho de la clave: %hu", l);
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'e':
                if (clave1 != NULL) {
                    imprimir(&clave1, '0');
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'f':
                if (clave1 != NULL) {
                    imprimir(&clave1, '1');
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'g':
                if (clave1 != NULL) {
                    imprimir(&clave1, '2');
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'h':
                if (clave1 == NULL) {
                    char* cadena;
                    cadena = (char*)malloc(100 * sizeof(char)); // asigno memoria para la clave
                    printf("Introduce la clave como cadena de texto: ");
                    scanf(" %s", cadena); // la leo y la guardo

                    printf("Introduce el número para cifrar la clave: ");
                    scanf("%hu", &cifrado);

                    cadena2clave(&clave1, cadena, cifrado); // creo la clave
                }
                else {
                    liberar(&clave1);
                    if (clave1 == NULL) { // compruebo que la clave se liberó correctamente
                        printf("Clave liberada para crear otra nueva\n");
                        
                        char* cadena;
                        cadena = (char*)malloc(100 * sizeof(char)); // asigno memoria para la clave
                        printf("Introduce la clave como cadena de texto: ");
                        scanf(" %s", cadena); // la leo y la guardo

                        printf("Introduce el número para cifrar la clave: ");
                        scanf("%hu", &cifrado);

                        cadena2clave(&clave1, cadena, cifrado); // creo la clave
                    }
                }
                break;
            case 'i':
                if(clave1 != NULL) {
                    unsigned short resultado = compruebaclave(&clave1, '0');
                    if (resultado == 1) {
                        printf("Clave correcta");
                    }
                    else {
                        printf("Clave incorrecta");
                    }
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }
                break;
            case 'j':
                if (clave1 != NULL) {
                    unsigned short resultado2 = compruebaclave(&clave1, '1');
                    if (resultado2 == 1) {
                        printf("\nClave correcta");
                    }
                    else {
                        printf("\nClave incorrecta");
                    }
                }
                else {
                    printf("Todavía no existe ninguna clave\n");
                }    
            break;
            case 's':
                if (clave1 != NULL) { // compruebo que la clave no está liberada aun para, en ese caso, liberarla
                    liberar(&clave1);
                }
                printf("Salimos del programa\n");
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
            }
    }while (opcion!='s');
    return (EXIT_SUCCESS);
}