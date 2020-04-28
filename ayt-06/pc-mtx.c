/*
 * PRODUCTOR CONSUMIDOR USANDO MUTEX
*/
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define EXIT_PROGRAM return 0
#define MAX_ITERATIONS 10
#define BUFFER_SIZE MAX_ITERATIONS + 1

int buffer[BUFFER_SIZE]; 
int front, tail, size, total; //implementar una cola con arreglos
pthread_mutex_t mutex; 
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;
void *consumer(void *arg) // consumidor
{
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&cond_var, &mutex); // este espera a cond_signal
    pthread_mutex_unlock(&mutex);
    for(; size > 0; --size) {
        printf("CONSUME %d\n", buffer[front]);
        total = total + buffer[front++];
        front %= BUFFER_SIZE;
    }
    printf("DESPUES DE %d ITERACIONES CONSUMIDOR CONSUME %d\n", MAX_ITERATIONS, total);
    pthread_exit(NULL);
}
void *producer(void *arg) //productor
{
    int produced;
    for(produced = 0; produced < MAX_ITERATIONS; ++produced){
        printf("PRODUCE %d\n", produced);
        buffer[tail++] = produced;
        tail %= BUFFER_SIZE;
        ++size;
    }
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&cond_var);//este tiene prioridad
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
int main(void)
{
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_mutex_destroy(&mutex);
    EXIT_PROGRAM;
}