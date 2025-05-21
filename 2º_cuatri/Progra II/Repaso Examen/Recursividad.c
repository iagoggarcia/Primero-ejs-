#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Utiliza una estrategia Divide y Vencerás para implementar una función palíndromo que dado un
array de caracteres determine si es un palíndromo. Escribe el código C de la solución y
posteriormente razona sobre la complejidad computacional del método. Puedes poner los
argumentos necesarios en esa función, que debe ser recursiva y no puede utilizar estructuras
iterativas (no se puede incluir lazos for o while).*/

int esPalindromoRec(char str[], int inicio, int fin) {
    if (inicio >= fin) { // si el inicio es mayor o igual que el fin, es porque ya comparé todos los caracteres necesarios
        return 1;
    }
    if (str[inicio] != str[fin]) { // si el primer caracter y el último son distintos, no va a ser palíndromo
        return 0;
    }
    return esPalindromoRec(str, inicio + 1, fin - 1); // si no sucedió lo anterior, sigo comparando caracteres
}

/*Implementa de manera recursiva una función que dada una base b y un exponente e (ambos
enteros mayores o iguales que cero) calcule be*/

int Exponente (int base, int exponente) {
    if (exponente == 0) {
        return 1; // Caso base: cualquier número elevado a 0 es 1
    } else {
        return base * Exponente(base, exponente - 1); // Paso recursivo
    }
}


/* En el siglo XVIII, el astrónomo Johann Daniel Titius propuso una regla para calcular la
distancia del sol a cada uno de los planetas conocidos en ese momento. Para aplicar esa regla,
que ahora se conoce como la Ley de Titius-Bode, se utiliza la secuencia:
b1=1 b2=3 b3=6 b4=12 b5=24 b6=48 ….
donde a partir del tercer elemento en la secuencia cada elemento es el doble del anterior.
Si numeramos los planetas por cercanía al Sol (Mercurio 1, Venus 2, etc) la distancia aproximada
de cada planeta al Sol vendría dada por la fórmula:
di = (4+bi)/10 (donde di sería la distancia en UAs -unidades astronómicas- del planeta i-ésimo al
Sol).
Escribe una función recursiva que dado el número del planeta (entero positivo) calcule la distancia
aproximada en UAs al sol. La función no puede tener ningún tipo de lazos. La solución debe ser una
única función recursiva que calcule directamente los UAs de modo recursivo. No sirve hacer una
función recursiva que calcule los bi para luego usarla para calcular las distancias. */
float distPlaneta(int planeta) {
    if (planeta == 1) {
        return ((4 + 1) / 10.0);
    }
    else if (planeta == 2) {
        return ((4+3) / 10.0);
    }
    else if (planeta == 3) {
        return ((4+6) / 10.0);
    }
    else {
        return (4 + (2 * (10* distPlaneta(planeta - 1) - 4)) / 10.0); // al ser el doble del anterior, se hace 4+2*bi (que es 10*di-4, se saca de la fórmula), entre 10
    }
}

/*El máximo común divisor (mcd) se puede calcular mediante la regla de Euclides que dice que si
x es divisible por y entonces y es el mcd de x e y y que, en otro caso, el mcd de x e y es igual al
mcd de y y el resto de dividir x por y. Haz una función recursiva que calcule el mcd de dos
enteros positivos de este modo.*/

int gcd(int x, int y) {
    int resto = x%y;
    if (resto == 0) {
        return y;
    }
    else {
        gcd(y, resto);
    }
}


// Programa que recibe un número y devuelve la suma de sus dígitos
int sumaDigitos(int n) {
    if (n < 10) { // si el número tiene solo 1 cifra
        return n; // devuelvo el número
    }
    else {
        return ((n%10) + sumaDigitos(n/10)); // n%10 da el último dígito, y n/10 lo quita
    }
}

/* La raíz digital de un entero es la suma repetida de sus dígitos hasta que queda un único dígito.
Haz una función recursiva que realice este cálculo. No se puede utilizar la función del ejercicio
anterior ni tampoco utilizar lazos.*/
int raizDigital(int n) {
    if (n < 10) {
        return n;
    }
    else {
        int suma = (n % 10) + raizDigital(n/10);
        return raizDigital(suma);
    }
}

/* Función que implementa el triángulo de pascal*/
int Pascal(int n, int k){
    if(k==0 || n==k) {
        return 1;
    }
    else {
        return (Pascal(n-1,k-1)+Pascal(n-1,k));
    }
}

/*Escribe una función recursiva reverso que, dada una cadena de caracteres, produzca la cadena
de caracteres al revés.*/
char* Reverso(char arr[], int inicio, int final){
    if(inicio>=final){
        return arr;
    }
    char temp=arr[final-1];
    arr[final-1]=arr[inicio];
    arr[inicio]=temp;
    return Reverso(arr,inicio+1,final-1);
}


int main() {
    char palabra[] = "anilina";
    int len = strlen(palabra);
    if (esPalindromoRec(palabra, 0, len - 1))
        printf("Es palindromo\n");
    else {
        printf("No es palindromo\n");
    }

    int resultado = Exponente(3,3);
    printf("Resultado: %d\n", resultado);

    int distancia = distPlaneta(3);
    printf("Distancia: %d\n", distancia);

    int mcd = gcd(14, 49);
    printf("Máximo común divisor: %d\n", mcd);

    int suma_digitos = sumaDigitos(12345);
    printf("Resultado de la suma: %d\n", suma_digitos);

    int raiz = raizDigital(123);
    printf("Raíz digital: %d\n", raiz);

    int pascal = Pascal(7,2);
    printf("Pascal: %d\n", pascal);

    char inversa[] = "hola";
    Reverso(inversa,0,4);
    printf("Palabra del revés: %s\n", inversa);

    return 0;
}