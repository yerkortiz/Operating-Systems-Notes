/*
 * EJEMPLO DE CONDICIÓN DE CARRERA,
 * EL RESULTADO DEBIESE SER 5, PERO A VECES
 * DA RESULTADOS ILOGICOS.
 * PARA VER RESULTADOS, EJECUTAR EL PROGRAMA
 * CON ARG >= 20000
 * compilar con gcc filename.c
 * ejecutar con ./a.out n(n = ingrese el numero de iteraciones)
*/
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long k = 5; // k + N - N
int numIters; // N
void *plusOne(void *arg); // sumar 1
void *minusOne(void *arg); // restar 1
int main(int argc, char *argv[])
{
    pthread_t pid, mid; // declaramos los threads
    numIters = atoi(argv[1]); // entrada via linea de comandos
    printf("MAIN STARTED\n");
    pthread_create(&pid, NULL, &plusOne, NULL); // crear thread
    pthread_create(&mid, NULL, &minusOne, NULL); // crear thread
    pthread_join(pid, NULL); // ejecutar thread
    pthread_join(mid, NULL); // ejecutar thread
    printf("N = %lld", k);
    return 0;
}
void *plusOne(void *arg)
{
    for(int i = 0; i < numIters; ++i)
        ++k;
    //printf("%lld\n", k);
    return NULL;
}
void *minusOne(void *arg)
{
    for(int i = 0; i < numIters; ++i)
        --k;
    //printf("%lld\n", k);
    return NULL;
}