#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARTAS 52
#define NUM_CARTAS_PALO 13
#define NUM_CARTAS_MANO 5
#define NUM_PALOS 4
#define N 10
#define M 5000


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

int main () {

/* 
    Se calculan las probabilidades de cada uno de los eventos haciendo un conteo de casos que verifican el el evento conjunto
    con el total de casos de un evento, para luego aplicar LaPlace. Esto lo hacemos con el uso de coeficientes binomiales.
*/

float pRoyalFlush = CoeficienteBinomial(4,1) / (float) CoeficienteBinomial(52,5);
double pDosPares = (CoeficienteBinomial(13, 2) * pow(CoeficienteBinomial(4,2), 2) * 11 * 4 ) / (float) CoeficienteBinomial(52, 5);
double pFullHouse = (CoeficienteBinomial(13, 1) * CoeficienteBinomial(4, 3) * 12 * CoeficienteBinomial(4,2)) / (float) CoeficienteBinomial(52, 5);
float pQuad = (13 * 12 * 4) / (float) CoeficienteBinomial(52, 5);
float pTotal = pRoyalFlush + pDosPares + pFullHouse + pFullHouse + pQuad;

printf("La probabilidad de un doble par es de %f\n", pDosPares);
printf("La probabilidad de un Full House es de %f\n", pFullHouse);
printf("La probabilidad de un quad es de %f\n", pQuad);
printf("La probabilidad de un royal flush es de %f\n", pRoyalFlush);
printf("La probabilidad de cualquier evento es de %f\n", pTotal);

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


mostrar_mazo(array_cartas, NUM_CARTAS);
carta cartas_mano[5];

for (int i = 0; i < N; i++){

    for (int j = 0; j < M; j++) {
        mezclar_mazo(array_cartas);
        for (int i = 0; i < NUM_CARTAS_MANO; i++) {
            cartas_mano[i] = array_cartas[i]; 
        }

        printf("\n");
        mostrar_mazo(cartas_mano, NUM_CARTAS_MANO);

    }
}


return 0;

}


