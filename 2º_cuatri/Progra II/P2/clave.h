typedef char TELEMENTO;
typedef void* clave;

void crear(clave *c, unsigned short longitud, unsigned short cifrado);

void asignar(clave *c, unsigned short posicion, TELEMENTO valor);

void liberar(clave *c);

TELEMENTO recuperar(clave *c, unsigned short posicion);

unsigned short longitud(clave *c);

char* imprimir(clave *c, char modo_op);

void cadena2clave(clave *c, char* cadena, unsigned short cifrado);

unsigned short compruebaclave(clave *c, char modo_op);

char* imprimir_comprobar_partes(clave *c);

char* obtenerClave(clave *c);