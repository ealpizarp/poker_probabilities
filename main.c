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

int validar_dospares(carta array_mano[]){
    /*  Para validar 2 pares usamos la lógica para vadilar full house:
        Se ulitizará un array de 13 campos que servirán como contador de apariciones para cada valor
        de las cartas. Luego se recorre la mano y se suma un 1 en el indice que le corresponde a esta 
        carta. Finalmente se recorre el array para verificar que hayan dos indicies con un valor de 2
    */

    // Contadores para cada valor: A,2,3,4,5,6,7,8,9,10,J,Q,K, o en este caso del 1 al 13
    int contadores[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    int parejas=0;//Variable para verificar que hayan 2 parejas

    int indice;
    for(int i=0;i<NUM_CARTAS_MANO;i++){
        /*
        Ya que las cartes están representadas del 1 al 13 para acceder a su respectivo 
        campo en el array de contadores es el valor que representa menos uno.
        */
        indice=array_mano[i].numero;
        contadores[indice-1]++;
    }

    //Cuenta las parejas
    for(int e=0;e<NUM_CARTAS_PALO;e++){
        if(contadores[e]==2)parejas++;
    }

    if (parejas==2) return 1;
    else return 0;
}

int validar_poker(carta array_mano[]){
    /*  Para validar 2 pares usamos la lógica para vadilar full house:
        Se ulitizará un array de 13 campos que servirán como contador de apariciones para cada valor
        de las cartas. Luego se recorre la mano y se suma un 1 en el indice que le corresponde a esta 
        carta finalmente se verifica que algún indique tenga el contador en 4.
    */

    // Contadores para cada valor: A,2,3,4,5,6,7,8,9,10,J,Q,K, o en este caso del 1 al 13
    int contadores[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

    int indice;
    for(int i=0;i<NUM_CARTAS_MANO;i++){
        /*
        Ya que las cartes están representadas del 1 al 13 para acceder a su respectivo 
        campo en el array de contadores es el valor que representa menos uno.
        */
        indice=array_mano[i].numero;
        contadores[indice-1]++;

        //Despues de sumarle 1 al indice de la carta verifica si tiene 4
        if(contadores[indice-1]==4) return 1;
    }
    //Si sale del ciclo for significa que no hay un poker
    return 0;
}

int validar_escalerareal(carta array_mano[]){
    /*  Para esta validación se utilizará un array de 5 elementos que sirve como contador y
        una variable que sirve para verificar que todas sean el mismo tipo (palo).
    */

    // Contadores para los valores: A,10,J,Q,K. Más adelante se indica como se manejará los indices
    int contadores[5]={0,0,0,0,0};
    //Obtiene el tipo de la primera carta para verificar que las demás sean del mismo
    char tipo=array_mano[0].palo;

    int indice;
    for(int i=0;i<NUM_CARTAS_MANO;i++){
        indice=array_mano[i].numero;
        if(indice<10 && indice>1) return 0;//Si el valor de la carta no pertene a A,10,J,Q,K no es escalera real
        /*
        En este caso el manejo del indice varia en 2 casos:
        1. Indice = 1:   Ya que el AS es represanto con un 1, para acceder a su indice solamente debemos restarle 1.
        2. Indice >= 10: Para el resto de cartes (10,J,Q,K) para poder acceder a sus indices debemos restarles 9,
                        ya que en el array sus indices van del 1 al 4.          
        */
        if(indice==1)indice--;
        else indice=indice-9;

        if(array_mano[i].palo==tipo)contadores[indice]++;
        else return 0;//SI no es del mismo tipo del resto de cartas no es escalera real
    }
    //Si sale del ciclo for significa que sí hay escalera real
    return 1;
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


