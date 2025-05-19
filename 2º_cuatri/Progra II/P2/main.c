#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "getopt.h" // para que funcione bien el getopt
#include "lista-1.h"
#include "cola-1.h"
#include "clave.h"

void _strip_line(char * linea){
    linea[strcspn(linea , "\r\n")] = 0;
}

char* conseguirNombre_archivo(int argc, char** argv) {
    int opt;
    char* archivo = NULL;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        archivo = (char*)malloc(strlen(optarg) * sizeof(char)); // asigno memoria
        if (archivo == NULL) {
            printf("Error en la asignación de memoria\n");
            exit(EXIT_FAILURE);
        }
        strcpy(archivo, optarg); // copia el contenido de optarg a la memoria dinámica, si no no puedo liberar el nombre al salir del programa
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

void leer_archivo(char* nombre_archivo, TLISTA lista) {
    FILE* archivo = NULL;
    TIPOELEMENTOLISTA usuario;
    usuario.clave = NULL; // inicializo la clave a NULL para que no dé problemas al leer el archivo
    char buffer[256];

    if (nombre_archivo != NULL) { // si hay nombre de archivo
        archivo = fopen(nombre_archivo, "r"); // abro el archivo
        if (archivo == NULL) { // si hubo problemas abriéndolo
            printf("Error en la apertura del archivo\n"); // imprimo mensaje de error y salgo
            return; // hago return sin nada para que salga de la función pero no del programa
        }

        while (fgets(buffer, sizeof(buffer), archivo) != NULL) { // leo línea a línea el archivo
            char *claveTemp = (char*)malloc(25*sizeof(char)); // claveTemp es para guardar la clave sin cifrar mientras no se lee el cifrado, que hace falta para cifrarla

            char *token = strtok(buffer, ",");
            _strip_line(token);
            strncpy(usuario.correo, token, sizeof(usuario.correo)); // guardo el correo

            token = strtok(NULL, ",");
            _strip_line(token);
            if (token) {
                strncpy(usuario.apellido, token, sizeof(usuario.apellido)); // guardo el apellido
            }

            token = strtok(NULL, ",");
            _strip_line(token);
            if (token) {
                strncpy(usuario.nombre, token, sizeof(usuario.nombre)); // guardo el nombre
            }

            token = strtok(NULL, ",");
            _strip_line(token);
            if (token) {
                usuario.edad = atoi(token); // paso a int la edad y la guardo
            }

            token = strtok(NULL, ",");
            _strip_line(token);
            if (claveTemp == NULL) {
                printf("Error en la asignación de memoria");
            }

            if (token) {
                strcpy(claveTemp, token); // guardo la clave temporal
            }

            token = strtok(NULL, ",");
            _strip_line(token);
            if (token) {
                usuario.cifrado = atoi(token); // paso a int el cifrado y lo guardo
            }


            usuario.clave = (clave*)malloc(sizeof(clave)); // asigno memoria nueva para que cada clave tenga una dirección distinta

            cadena2clave(&usuario.clave, claveTemp, usuario.cifrado); // asigno la clave cifrada

            insertarElementoLista(&lista, finLista(lista), usuario);

            free(claveTemp); // libero la memoria de la clave temporal
        }
        fclose(archivo);
    }
}

int existeCorreo (TLISTA lista, char* correo) {
    TPOSICION pos = primeroLista(lista);
    TIPOELEMENTOLISTA usuario;

    while (pos != finLista(lista)) {  // pasa por todos los nodos
        recuperarElementoLista(lista, pos, &usuario);
        if (strcmp(correo, usuario.correo) == 0) { // si el correo introducido ya existe para algún usuario
            return 1; // devuelvo 1
        }
        pos = siguienteLista(lista, pos);  // si en el nodo que estoy el correo es distinto, avanzo al siguiente
    }
    return 0; // si no hay ningún correo igual, devuelvo 0
}

void anhadirUsuario(TLISTA lista, TPOSICION p) {
    TIPOELEMENTOLISTA usuario;
    usuario.clave = NULL; // inicializo la clave a NULL para que no dé problemas
    char buffer[25]; // buffer para guardar el cifrado y pasarlo a int
    char claveTemp[25]; // Buffer local para la clave

    printf("Introduce el correo: ");
    fgets(usuario.correo, sizeof(usuario.correo), stdin); // pido y guardo el correo
    _strip_line(usuario.correo);

    if (existeCorreo(lista, usuario.correo) == 1) {
        printf("Error: el correo ya está registrado.\n");
        return;  // salgo de la función sin añadir el usuario
    }

    printf("Introduce el nombre: ");
    fgets(usuario.nombre, sizeof(usuario.nombre), stdin);
    _strip_line(usuario.nombre);

    printf("Introduce el apellido: ");
    fgets(usuario.apellido, sizeof(usuario.apellido), stdin);
    _strip_line(usuario.apellido);

    printf("Introduce la edad: ");
    fgets(buffer, sizeof(buffer), stdin);
    _strip_line(buffer);
    usuario.edad = atoi(buffer);
    if (usuario.edad < 18) { // Compruebo que el usuario es mayor de edad
        printf("Error: el usuario debe ser mayor de edad\n");
        return; // Si es menor, salgo de la función sin añadir el usuario
    }

    printf("Introduce la clave: ");
    fgets(claveTemp, sizeof(claveTemp), stdin); // guardo la clave en la variable temporal mientras no guardo el cifrado
    _strip_line(claveTemp);

    printf("Introduce el cifrado: ");
    fgets(buffer, sizeof(buffer), stdin);
    _strip_line(buffer);
    usuario.cifrado = atoi(buffer); // paso el cifrado a int y lo guardo

    cadena2clave(&usuario.clave, claveTemp, usuario.cifrado); // Paso la clave temporal y el cifrado a cadena2clave para guardarlo en usuario.clave

    insertarElementoLista(&lista, finLista(lista), usuario);

    printf("Usuario añadido correctamente.\n");
}

void eliminarUsuario(TLISTA lista) {
    TIPOELEMENTOLISTA usuario;
    TPOSICION pos = primeroLista(lista); // empiezo en el primer usuario
    char correo[256], contrasenha[25];

    printf("Introduce el correo: "); // pido el correo
    fgets(correo, sizeof(correo), stdin); // lo guardo
    _strip_line(correo);

    while (pos != finLista(lista)) { // voy mirando los nodos de la lista
        recuperarElementoLista(lista, pos, &usuario);
        if (strcmp(usuario.correo, correo) == 0) { // si el correo existe (porque el introducido es igual a alguno de la lista)
            break; // paro el bucle con la posición actual
        }
        pos = siguienteLista(lista, pos); // si no, paso al siguiente nodo y comparo otra vez
    }

    if (pos == finLista(lista)) { // si llego al final de la lista sin haber encontrado el correo
        printf("Error: Usuario no encontrado.\n"); // es porque no existe un usuario con ese correo
        return;
    }

    printf("Introduce la clave: ");  // pido la clave
    fgets(contrasenha, sizeof(contrasenha), stdin); // la guardo
    _strip_line(contrasenha); // limpio la cadena para evitar problemas

    unsigned short tamanho = longitud(&usuario.clave); // guardo el tamanho de la clave
    int clave_correcta = 1; // asumo que la clave es correcta

    if (strlen(contrasenha) != tamanho) { // si el tamanho de la introducida por teclado y el de la de usuario.clave son distintos
        clave_correcta = 0; // la clave es incorrecta
    } 
    else {
        for (unsigned short i = 0; i < tamanho; i++) {
            if (recuperar(&usuario.clave, i) != contrasenha[i]) { // descifro los caracteres de usuario.clave y los comparo con los de la clave introducida por teclado 1 a 1
                clave_correcta = 0; // si algún caracter no coincide, la clave es incorrecta
                break;
            }
        }
    }

    if (clave_correcta) {
        liberar(&usuario.clave); // libero la memoria de la clave
        suprimirElementoLista(&lista, pos); // Elimino el usuario de la lista
        printf("Usuario eliminado correctamente.\n");
    }
    else {
        printf("Error: Clave incorrecta.\n");
    }
}

void recepcionSolicitudes(TCOLA* cola, TLISTA lista, int* num_solicitudes) {
    TIPOELEMENTOLISTA usuario;
    TIPOELEMENTOCOLA usuarioCola;
    TPOSICION pos = primeroLista(lista); // empiezo en el primer usuario
    char cadena[256], clave[25]; // cadena para guardar los correos o el '0' para parar el bucle, clave para las contraseñas
    int clave_correcta = 0; // asumo que la clave es incorrecta
    
    do{
        printf("Introduce el correo del usuario: " );
        fgets(cadena, sizeof(cadena), stdin); // pido y guardo el correo
        _strip_line(cadena); // limpio la cadena

        if (strcmp(cadena, "0") == 0) { // si el usuario introduce "0", salgo del bucle ya antes de guardar el correo en usuario_cola.correo y hacer comprobaciones
            break;
        }

        strcpy(usuarioCola.correo, cadena); // guardo el correo en la cola

        if(existeCorreo(lista, usuarioCola.correo) == 0) { // si el correo no existe
            printf("Error: el correo no está registrado.\n");
        }
        else {
            printf("Introduce la clave: ");
            fgets(clave, sizeof(clave), stdin); // pido y guardo la clave
            _strip_line(clave); // limpio la cadena

            clave_correcta = 0; // asumo que la clave es incorrecta

            while (pos != finLista(lista)) {
                recuperarElementoLista(lista, pos, &usuario);
                if (strcmp(usuario.correo, usuarioCola.correo) == 0) { // si el correo coincide
                    unsigned short tamanho = longitud(&usuario.clave); // obtengo la longitud de la clave
                    if (strlen(clave) == tamanho) { // si las claves tienen el mismo tamanho
                        clave_correcta = 1; // asumo que la clave es correcta
                        for (unsigned short i = 0; i < tamanho; i++) {
                            if (recuperar(&usuario.clave, i) != clave[i]) { // comparo caracter por caracter
                                clave_correcta = 0; // si algún caracter no coincide, la clave es incorrecta
                                break;
                            }
                        }
                    }
                    break; // salgo del bucle
                }
                pos = siguienteLista(lista, pos); // paso al siguiente nodo
            }

            if (clave_correcta) {
                anadirElementoCola(cola, usuarioCola); // añado el usuario a la cola
                printf("Solicitud de %s %s recibida.\n", usuario.nombre, usuario.apellido);
                (*num_solicitudes)++; // incremento el número de solicitudes para la función numSolicitudes
            } else {
                printf("Error: Clave incorrecta.\n");
            }
        }
    } while(1); // bucle infinito porque la comprobación del "0" está dentro del do-while
}

void numSolicitudes (int* num_solicitudes) {
    printf("Número de solicitudes: %d\n", *num_solicitudes);
}

void venderEntradas(TCOLA* cola, int *num_solicitudes) {
    TIPOELEMENTOCOLA usuarioCola; // variable para imprimir los correos de los usuarios que consiguen entrada
    int num_entradas, vendidas = 0; // vendidas es para saber cuántas entradas se han vendido y poder hacer el printf del bucle

    if (cola == NULL) { // si la cola no existe
        printf("No hay solicitudes para la compra de entradas.\n");
        return; // salgo de la función porque no hay gente para comprar entradas
    }

    if (esColaVacia(*cola)) { // si la cola está vacía
        printf("No hay solicitudes para la compra de entradas.\n");
        return; // salgo de la función porque no hay gente para comprar entradas
    }

    // si paso del if, es porque hay solicitudes
    printf("Introduce el número de entradas a vender: ");
    scanf("%d", &num_entradas); // leo el número de entradas que se van a vender

    for (int i = 0; i < num_entradas; i++) {
        consultarPrimerElementoCola(*cola, &usuarioCola); // consulto el primer elemento de la cola
        printf("Entrada vendida a: %s\n", usuarioCola.correo); // imprimo el correo del usuario que compra la entrada
        suprimirElementoCola(cola); // elimino el primer elemento de la cola (el que acaba de comprar la entrada)
        (*num_solicitudes)--; // resto uno al número de solicitudes porque se acaba de vender una entrada
        vendidas++;
        if (esColaVacia(*cola)) { // si la cola se queda vacía al vender esa entrada
            printf("Se han vendido %d de las %d que se querían vender, no había la suficiente cola para vender todas.\n", vendidas, num_entradas); // imprimo el número de entradas vendidas
            break; // salgo del bucle
        }
    }

    if (*num_solicitudes < 0) {
        (*num_solicitudes) = 0; // si se queda en negativo lo pongo a 0, no puede haber menos de 0 solicitudes
    }
}

void escribirArchivo(TLISTA lista, char* nombre_archivo) {
    FILE* archivo = NULL;
    TIPOELEMENTOLISTA usuario;
    TPOSICION pos = primeroLista(lista);
    char* contrasenha = NULL;
    usuario.clave = NULL; // inicializo la clave a NULL para que no dé problemas al leer el archivo

    if (nombre_archivo != NULL) { // si hay nombre de archivo
        archivo = fopen(nombre_archivo, "w"); // abro el archivo
        if (archivo == NULL) { // si hubo problemas abriéndolo
            printf("Error en la apertura del archivo\n"); // imprimo mensaje de error y salgo
            return; // hago return sin nada para que salga de la función pero no del programa
        }

        while (pos != finLista(lista)) {  // paso por todos los nodos
            recuperarElementoLista(lista, pos, &usuario);
            contrasenha = obtenerClave(&usuario.clave); // obtengo la clave cifrada
            fprintf(archivo, "%s,%s,%s,%d,%s,%d\n", usuario.correo, usuario.apellido, usuario.nombre, usuario.edad,contrasenha, usuario.cifrado);
            free(contrasenha); // libero memoria una vez ya escribí toda la información del usuario
            pos = siguienteLista(lista, pos);  // avanzo al siguiente nodo
        }        

        fclose(archivo);
    }
}

void imprimirLista(TLISTA lista) { // función para imprimir la lista despues de añadir o eliminar un usuario
    TIPOELEMENTOLISTA usuario;
    TPOSICION pos = primeroLista(lista);
    char* clave = NULL;

    printf("Lista actualizada:\n");
    while (pos != finLista(lista)) {
        recuperarElementoLista(lista,pos,&usuario);
        clave = obtenerClave(&usuario.clave);
        printf("Nombre: %s, Apellido: %s, Correo: %s, Edad: %d, Clave: %s, Cifrado: %d\n", usuario.nombre, usuario.apellido, usuario.correo, usuario.edad, clave, usuario.cifrado);
        free(clave);
        pos = siguienteLista(lista, pos);
    }
    
}

int main(int argc, char** argv) {
    TLISTA lista = NULL;
    TCOLA cola = NULL;
    char* nombre_archivo = NULL;
    int num_solicitudes = 0, hayCola = 0; // flag sirve para saber si hay cola o no (lo uso en la opción e)
    char opcion;
    
    nombre_archivo = conseguirNombre_archivo(argc, argv); // guardo el nombre de archivo después del -f
    if (nombre_archivo){ // si hay un nombre de archivo pasado por terminal
        crearLista(&lista); // paso la dirección de lista para modificarla
        leer_archivo(nombre_archivo, lista); // y abro y leo el archivo, guardo los usuarios y los meto en la lista
    }

    do{
        printf("\n--------------------\n");
        printf("\na) Añadir usuario");
        printf("\nb) Eliminar usuario");
        printf("\nc) Iniciar proceso de recepción de solicitudes para evento");
        printf("\nd) Ver número de solicitudes para evento");
        printf("\ne) Vender entradas para evento");
        printf("\ns) Salir");
        printf("\n--------------------\n");
        printf("\nOpcion: ");
        scanf(" %c", &opcion);
        getchar(); // para limpiar el \n del buffer y que no dé problemas en los fgets de anhadirUsuario
        switch(opcion){
            case 'a':
                anhadirUsuario(lista, finLista(lista));
                break;
            case 'b':
                if (esListaVacia(lista)) {
                    printf("Error: no hay usuarios registrados.\n");
                    break; // salgo porque no hay usuarios
                }
                else {
                    eliminarUsuario(lista);
                }
                break;
            case 'c':
                if (esListaVacia(lista)) {
                    printf("Error: no hay usuarios registrados.\n");
                    break; // salgo porque no hay usuarios
                }
                else {
                    if (cola == NULL) { // si no hay cola
                        crearCola(&cola); // la creo
                        hayCola = 1; // pongo el hayCola a 1 porque ahora hay cola
                    }
                    recepcionSolicitudes(&cola, lista, &num_solicitudes); // llamo a la función para añadir solicitudes
                }
                break;
            case 'd':
                numSolicitudes(&num_solicitudes); // llamo a la función para ver el número de solicitudes
                break;
            case 'e':
                if (!hayCola) { // si no hay cola
                    printf("Error: no hay solicitudes para comprar entradas.\n"); // no se pueden vender entradas
                }
                else {
                    venderEntradas(&cola, &num_solicitudes); // llamo a la función para vender entradas
                }
                break;
            case 's':
                escribirArchivo(lista, nombre_archivo); // escribo los usuarios en el archivo
                
                // Antes de salir libero la memoria de la lista, la cola y del nombre del archivo:
                if (lista) {
                    destruirLista(&lista);
                }

                if(nombre_archivo) { // si hay nombre de archivo
                    free(nombre_archivo);
                }

                if(cola) {
                    destruirCola(&cola);
                }

                printf("Memoria liberada correctamente, saliendo del programa.\n");
                
                break;
            default:
                printf("Opcion incorrecta\n");
                break;
            }
    }while (opcion!='s');
    return (EXIT_SUCCESS);
}
