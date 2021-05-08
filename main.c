#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CARTAS 52
#define NUM_CARTAS_PALO 13
#define NUM_CARTAS_MANO 5
#define NUM_PALOS 4
#define N 649739
#define M 40


/*
Se declara un nuevo tipo llamado carta, los atributos que pueden componener a este mismo estan definidos de la siguiente manera:

    Palo = {B (Basto), (C) Corazon, (D) Diamante, (T) Trebol}
    Numero = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}

*/

typedef struct
{
    char palo;
    int numero;

} carta;




int CoeficienteBinomial(int n, int k)

/*
 * Funcion: Calcula el coeficiente binomial
 * --------------------------------------------------
 *  
 *   n: un número natural 
 *   k: otro número natural
 *
 *   Retorna: El número de formas de escoger k elementos a partir de un conjunto de n elementos
*/

{
    // Casos base para el cálculo de coeficiente binomial según su fórmula multiplicativa
    
    if(k == 0)return 1;
    if(n <= k) return 0;

    // Se utiliza la fórmula multiplicativa para calcular por recursión de cola el coeficiente binomial

    return (n*CoeficienteBinomial(n-1,k-1))/k;
}




void mostrar_mazo(carta array_cartas[], int n)

/*
 * Rutina: Imprime el mazo de cartas
 * --------------------------------------------------
 *  
 *   array_cartas[]: arreglo de tipo cartas a mostrar
 *   n: un número natural
 *
*/

{
    for(int i=0; i < n; i++)
        printf("Carta %c\t%d\n", array_cartas[i].palo, array_cartas[i].numero);
}



void mezclar_mazo(carta array_cartas[])
/*
 * Rutina: Mezcla los elementos de un array tipo carta
 * ---------------------------------------------------
 *  
 *   array_cartas[]: arreglo de tipo cartas
 *
*/

{
    srand(time(NULL));
  
    for (int i=0; i < NUM_CARTAS; i++)
    {
        int r = i + (rand() % (52 -i));

        carta temp = array_cartas[i];
        array_cartas[i] = array_cartas[r];
        array_cartas[r] = temp;
    }
}

void mostrar_informacion_general () {

printf("Poker probabilities\n\n");

};

void mostrar_barra_progreso(int contador_actual, int valor_maximo, int porcentage) {
/*
 * Rutina: Muestra el consola el progreso en relacion a el proceso que se este ejecutando
 * ---------------------------------------------------
 * 
 *   contador_actual: Numero natural que representa el valor de progreso actual en relacion al valor maximo
 *   valor maximo: El numero de iteraciones totales del proceso que se esta ejecutando
 *   porcentaje: Numero natural que pertenece de {0,1,2...100}
 *
*/

    char progress_array[102] = {' '};

    // Se limpia la consola en pantalla

    system("clear");
    printf("\e[?25l");
    mostrar_informacion_general();
    progress_array[0] = '[';
    progress_array[101] = ']';

    for (int i = 1; i < 101; i++) {
        progress_array[i] = i < porcentage ? '#' : ' ';
    }

    printf("\r%s%d%%", progress_array, porcentage);
    fflush(stdout);

}

int main () {

/* 
    Se calculan las probabilidades de cada uno de los eventos haciendo un conteo de casos que verifican el el evento conjunto
    con el total de casos de un evento, para luego aplicar LaPlace. Esto lo hacemos con el uso de coeficientes binomiales.
*/

mostrar_informacion_general();

float pRoyalFlush = CoeficienteBinomial(4,1) / (float) CoeficienteBinomial(52,5);
double pDosPares = (CoeficienteBinomial(13, 2) * pow(CoeficienteBinomial(4,2), 2) * 11 * 4 ) / (float) CoeficienteBinomial(52, 5);
double pFullHouse = (CoeficienteBinomial(13, 1) * CoeficienteBinomial(4, 3) * 12 * CoeficienteBinomial(4,2)) / (float) CoeficienteBinomial(52, 5);
float pQuad = (13 * 12 * 4) / (float) CoeficienteBinomial(52, 5);
float pTotal = pRoyalFlush + pDosPares + pFullHouse + pFullHouse + pQuad;

//printf("La probabilidad de un doble par es de %f\n", pDosPares);

printf("P(Doble Par) = %f\n", pDosPares);
printf("P(Full House) = %f\n", pFullHouse);
printf("P(Quad) = %f\n", pQuad);
printf("P(Royal Flush) = %f\n", pRoyalFlush);
printf("P(Total) = %f\n", pTotal);

printf("Presione ENTER para continuar con las pruebas empiricas");
char c = getchar();

/*
    Se crea un array constante que contiene los caracteres para representar cada palo, estos
    están definidos de la siguiente manera:

    B = Bastos
    C = Corazon
    D = Diamante
    T = Trebol
*/

char tipoPalos[4] = {'B', 'C', 'D', 'T'};

// Se crea el array que se encargara de manejar el mazo de cartas

carta array_cartas[52];


// Todas las asignan todos los valores de las cartas correspondientes a una baraja inglesa

int pos = 0;
for (int i = 0; i < NUM_PALOS; i++) {
    
    for(int j = 1; j <= NUM_CARTAS_PALO; j++) {

        array_cartas[pos].palo = tipoPalos[i];
        array_cartas[pos].numero = j;
        pos += 1;
    }
}


//mostrar_mazo(array_cartas, NUM_CARTAS);

// Se crea el un nuevo array tipo carta para tomar una mano del mazo

carta cartas_mano[5];


/* 

Se instancian dos variables necesarias para contabilizar el progreso de el proceso

division_porcentage = Contador que mide el porcentaje para sacar
m_iteration_value = Contador que se encarga de medir el numero de iteracion de la muestra

*/

int division_porcentage = 1;
int m_iteration_value = 1;
int linear_count = 0;



for (int i = 0; i < M; i++){

    for (int j = 0; j < N; j++) {

        // Se mezcla el mazo para cada vez que se saca una mano

        mezclar_mazo(array_cartas);

        for (int i = 0; i < NUM_CARTAS_MANO; i++) {

        // Se leen los primeros cinco valores del array de cartas y se toman como una mano

            cartas_mano[i] = array_cartas[i]; 
        }

        // Al contador lineal se le asigna el numero de iteraciones totales hasta el momento

        linear_count = j + (m_iteration_value - 1) * N;

        // Condicionante que pregunta si el valor lineal ha llegado al porcentaje siguiente de las iteraciones totales

        if (linear_count == round( ((division_porcentage) / (float) 100 ) * (M * N) ) )  {

            // Se incrementa el porcentaje que buscaremos para la proxima iteracion

            division_porcentage += 1;

            mostrar_barra_progreso((j + (m_iteration_value - 1) * N), M * N, division_porcentage);

        }

    }

    // El valor de la iteracion de muestra es actualizado

    m_iteration_value += 1;
    
}
printf("\n");

return 0;

}

