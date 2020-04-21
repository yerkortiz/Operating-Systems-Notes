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
#define EXIT_PROGRAM return 0
long long n = 5;
int numIters;
//pthread_mutex_t mutex;
void *plusOne(void *arg);
void *minusOne(void *arg);

int main(int argc, char *argv[])
{
    pthread_t pid, mid;
    numIters = atoi(argv[1]);
    //pthread_mutex_init(&mutex, NULL);
    printf("MAIN STARTED\n");
    pthread_create(&pid, NULL, &plusOne, NULL);
    pthread_create(&mid, NULL, &minusOne, NULL);
    pthread_join(pid, NULL);
    pthread_join(mid, NULL);
    printf("N = %lld", n);
    EXIT_PROGRAM;
}
void *plusOne(void *arg)
{
    for(int i = 0; i < numIters; ++i, ++n)
        ;
    printf("%lld\n", n);
    return &n;
}
void *minusOne(void *arg)
{
    for(int i = 0; i < numIters; ++i, --n)
        ;
    printf("%lld\n", n);
    return &n;
}