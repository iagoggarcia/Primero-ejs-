/*
 * PROGRAMA PARA CALCULAR LA RAÍZ CUADRADA Y EL MÁXIMO COMÚN DIVISOR DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE VS CODE. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS SIGUIENTES CASOS PASANDOLOS TANTO COMO ARGUMENTOS COMO DEJANDO QUE EL PROGRAMA PIDA LOS VALORES
 * 10 2 (sqrt=3.162278, gcd=2)
 * 2 10 (sqrt=1.414214, gcd=2)
 * 49 7 (sqrt=7., gcd=7)
 * -5 1 (sqrt no existe por ser negativo, gcd=1)
 * -5 -3 (sqrt no existe por ser negativo, gcd=1)
 * 3 0  (sqrt=1.732051, gcd=3)
 * 0 10 (sqrt=0.000977, gcd=10) // La raíz cuadrada de 0 es 0, pero el método de Newton es un método estimado. Podéis comprobarlo jugando con el parámetro margen
 * 0 0 (sqrt=0.000977, gcd=0)
 */

/* a) Corregir los errores comentando la línea incorrecta y poniendo la incorrecta a continuación
 * b) Fija un breakpoint e inicia la ejecución en modo depuración ¿Qué sucede al ejecutar paso a paso
 *    (botón “Step into” [F11]) la sentencia donde se invoca la función sqrt()?
 *    RESPUESTA: Lo que sucede es que al invocar la función sqrt con el "Step into", entramos desde el main al código
 *    de dicha función situado en sqrt.c y se ejecuta línea a línea con el número conseguido con el código del main.c.
 *    Una vez acaba y tiene el resultado, vuelve al main y continúa con el código.
 * 
 * c) Al llegar a la función sqrt(), utiliza el botón “STEP OVER” [F10]  en  lugar  del  botón  “Step into” [F11]
 *   ¿Qué  diferencias observas frente a la ejecución del apartado b?
 *   RESPUESTA: La diferencia es que con el "Step over"se calcula la raíz directamente desde el main, es decir, sin
 *   entrar a la llamada de la función ni al código del sqrt.c, sin embargo con el "Step into" sí que lo hacemos.
 * 
 * d) Repite la ejecución en modo depuración visualizando todas las variables. 
 *    Indica qué sucede con la ventana de variables cuando el flujo del programa continúa DENTRO de la función
 *    Justifica la información que aparece en la solapa "Call Stack"
 *    RESPUESTA: Poniendo un breakpoint en la linea 53 del main, vemos que al principio las variables salen en la
 *    caja superior izquierda y al pasar la línea del scanf desaparecen hasta que metemos por teclado los números que
 *    pide y de nuevo aparecen todas las variables con a y b actualizadas según el valor que le hayamos dado. Cuando llegamos
 *    a la definición de s y la ejecutamos, esta variable se actualiza como la raíz cuadrada de a. De la misma forma
 *    pasa con g, que se actualiza como el mcd de a y b. En la solapa call stack aparece la función en la que se está
 *    ejecutando código. Si vamos ejecutando desde la primera linea del main veremos que en esa solapa se hace referencia
 *    a la función int main(in argc, char** argv). Si llegamos a las líneas donde se define s como la raíz de a o donde g
 *    se define como el mcd de a y b y hacemos un "Step into", iremos al archivo .c donde está esa función y en el call stack
 *    saldrá la función cuyo código está siendo ejecutado y la int main debido a que la función correspondiente está siendo
 *    llamada desde ahí.
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv) {

    int a, b;
    double s; // float s;
    int g; // float g;

    if (argc != 0){ // if (argc == 0){
        printf("Introduce dos números enteros: ");
        scanf(" %d %d", &a, &b); // scanf("%f%d", a, &b);
    } else {
        a = atoi(argv[0]); // a = argv[0];
        b = atoi(argv[1]); //b = argv[1];
    }
    
    if (a >= 0){ // if (a > 0){
        s = sqrt(a);
        printf("Raíz cuadrada(%d) = %f\n", a, s);
    }else{
        printf("Error raíz: el parámetro (%d) no es un entero positivo\n", a);
    }
        
    g = gcd(a, b);
    printf("Máximo común divisor(%d,%d) = %d\n", a, b, g); // printf("Máximo común divisor(%f,%d) = %f\n", a, b, g);

    return (EXIT_SUCCESS);
}

