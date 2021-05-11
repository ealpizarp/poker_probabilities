/*
=======================================================================================================================================================================================================
                                                                            Tecnológico de Costa Rica
                                                                Proyecto Programado Lenguajes de programacion (IC4700)
Autores:Eric Alpizar.
        Jacob Picado.
        Natalia Vargas.
        Patrick Vindas..

Fecha de ultima modificación: 08/05/2021.
=======================================================================================================================================================================================================
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CARTAS 52
#define NUM_CARTAS_PALO 13
#define NUM_CARTAS_MANO 5
#define NUM_PALOS 4
//#define N 649739
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
  
    for (int i=0; i < NUM_CARTAS; i++)
    {
        int r = i + (rand() % (NUM_CARTAS -i));

        carta temp = array_cartas[i];
        array_cartas[i] = array_cartas[r];
        array_cartas[r] = temp;
    }
}

void mostrar_informacion_general () {

/*
 * Rutina: Imprime en consola la informacion general del programa
 * --------------------------------------------------
 * 
 * Se imprime el nombre de la insitucion para la que se realiza el proyecto asi como
 * el nombre del proyecto en ASCII Art.
 *
*/

printf("============================================================================================\n");
printf("                             Instituto tecnologico de Costa Rica                            \n");
printf("============================================================================================\n\n");





printf("  ____       _                               _           _     _ _ _ _   _           \n");
printf(" |  _ \\ ___ | | _____ _ __   _ __  _ __ ___ | |__   __ _| |__ (_) (_) |_(_) ___  ___ \n");
printf(" | |_) / _ \\| |/ / _ \\ '__| | '_ \\| '__/ _ \\| '_ \\ / _` | '_ \\| | | | __| |/ _ \\/ __|\n");
printf(" |  __/ (_) |   <  __/ |    | |_) | | | (_) | |_) | (_| | |_) | | | | |_| |  __/\\__ \\\n");
printf(" |_|   \\___/|_|\\_\\___|_|    | .__/|_|  \\___/|_.__/ \\__,_|_.__/|_|_|_|\\__|_|\\___||___/\n");
printf("                            |_|                                                      \n\n");

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

void calculate_theorical_probabilities(){

/*
 * Rutina: Calcula e imprime las probabilidades teoricas de cada mano
 * --------------------------------------------------
 *  
 * Calcula las probabilidades teoricas siguiendo los resultados de una analisis del
 * espacio muestral previamente hecho y utiliza coeficientes binomiales para calcularlo
 *
*/

float pRoyalFlush = CoeficienteBinomial(4,1) / (float) CoeficienteBinomial(52,5);
double pDosPares = (CoeficienteBinomial(13, 2) * pow(CoeficienteBinomial(4,2), 2) * 11 * 4 ) / (float) CoeficienteBinomial(52, 5);
double pFullHouse = (CoeficienteBinomial(13, 1) * CoeficienteBinomial(4, 3) * 12 * CoeficienteBinomial(4,2)) / (float) CoeficienteBinomial(52, 5);
float pQuad = (13 * 12 * 4) / (float) CoeficienteBinomial(52, 5);
float pTotal = pRoyalFlush + pDosPares + pFullHouse + pFullHouse + pQuad;

printf("[TEORICA] P(Doble Par) = %f\n", pDosPares);
printf("[TEORICA] P(Full House) = %f\n", pFullHouse);
printf("[TEORICA] P(Quad) = %f\n", pQuad);
printf("[TEORICA] P(Royal Flush) = %f\n", pRoyalFlush);
printf("[TEORICA] P(Total) = %f\n", pTotal);

}


int main () {

srand(time(NULL));

/* 
    Se calculan las probabilidades de cada uno de los eventos haciendo un conteo de casos que verifican el el evento conjunto
    con el total de casos de un evento, para luego aplicar LaPlace. Esto lo hacemos con el uso de coeficientes binomiales.
*/
mostrar_informacion_general();

printf("Las manos que analizaremos en ese programa son las siguientes:\n\n");
printf("* Doble Par (Double Pair)\n");
printf("* Cuatro iguales (Quad)\n");
printf("* Full House\n");
printf("* Escalera Real (Royal Flush)\n\n");

printf("Sus probabilidades teoricas son:\n\n");

calculate_theorical_probabilities();

printf("\nPresione ENTER para continuar con las pruebas empiricas");
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

// Se inicializa variable para contabilizar la cantidad de exitos

int total_succeses = 0;
int royal_flush_succeses = 0;
int quad_succeses = 0;
int double_pair_succeses = 0;


for (int i = 0; i < M; i++){

    for (int j = 0; j < N; j++) {

        // Se mezcla el mazo para cada vez que se saca una mano

        mezclar_mazo(array_cartas);


        for (int i = 0; i < NUM_CARTAS_MANO; i++) {

        // Se leen los primeros cinco valores del array de cartas y se toman como una mano

            cartas_mano[i] = array_cartas[i]; 
        }

        /*
        //Para realizar pruebas para verificar masos
        cartas_mano[0].numero=1;
        cartas_mano[1].numero=10;
        cartas_mano[2].numero=11;
        cartas_mano[3].numero=12;
        cartas_mano[4].numero=13;
        */

        // Al contador lineal se le asigna el numero de iteraciones totales hasta el momento

        linear_count = j + (m_iteration_value - 1) * N;

        // Condicionante que pregunta si el valor lineal ha llegado al porcentaje siguiente de las iteraciones totales

        if (linear_count == round( ((division_porcentage) / (float) 100 ) * (M * N) ) )  {

            // Se incrementa el porcentaje que buscaremos para la proxima iteracion

            division_porcentage += 1;
            

            mostrar_barra_progreso((j + (m_iteration_value - 1) * N), M * N, division_porcentage);

        }

        if(validar_escalerareal(cartas_mano)){
            royal_flush_succeses +=1;
        }else {

            if(validar_poker(cartas_mano)){
                quad_succeses += 1;
            }
            else{

                if(validar_dospares(cartas_mano)){
                    double_pair_succeses += 1;
                }
            }
        }
    }
    // El valor de la iteracion de muestra es actualizado

    m_iteration_value += 1;
    
}

total_succeses = double_pair_succeses + quad_succeses + royal_flush_succeses;

printf("\n\n");

printf("Las probabilidades empiricas y teoricas son las siguientes:\n\n");
printf("[Empirica] P(Doble Par) = %f\n", double_pair_succeses / (float) linear_count);
printf("[Empirica] P(Quad) = %f\n", quad_succeses / (float) linear_count);
printf("[Empirica] P(Royal Flush) = %f\n", royal_flush_succeses / (float) linear_count);
printf("[Empirica] P(Total) = %f\n\n", total_succeses / (float) linear_count);

calculate_theorical_probabilities();

return 0;

}


