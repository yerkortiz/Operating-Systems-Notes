/*
 * PRODUCTOR CONSUMIDOR
 * SEMAFOROS
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define EXIT_PROGRAM return 0
#define BUFFER_SIZE (1 << 4)

pthread_mutex_t mutex; //declarar mutex
sem_t *empty, *full; // declarar semaforos
int produced, consumed;//producido y consumido, contador
int buffer[BUFFER_SIZE];//arreglo
int front, size, tail;//auxiliar, para usar el arreglo como cola
void *consumer(void *arg) // funcion del thread consumidor
{
    while(1) { //vaciar buffer
        sem_wait(full);
        pthread_mutex_lock(&mutex);
        if(size > 0) {
            sleep(1);
            consumed += buffer[front++];
            front %= BUFFER_SIZE;
            --size;
            printf("CONSUMIENDO %d\n", consumed);
        } else {
            printf("BUFFER VACIO\n");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(empty);
    }
    pthread_exit(NULL);
}
void *producer(void *arg)//productor
{
    while(1) {
        sem_wait(empty);
        pthread_mutex_lock(&mutex);
        if(size < BUFFER_SIZE){ 
            sleep(1);
            buffer[tail++] = ++produced;
            tail %= BUFFER_SIZE;
            ++size;
            printf("PRODUCIENDO %d \n", produced);
        } else {
            printf("BUFFER LLENO\n");
        }
        pthread_mutex_unlock(&mutex);
        sem_post(full);
    }
    pthread_exit(NULL);
}
int main(void) {
    sem_unlink("empty"); sem_unlink("full");
    empty = sem_open("empty", O_CREAT, 0644, BUFFER_SIZE);
    full = sem_open("full", O_CREAT, 0644, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_t pid, cid;
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    sleep(1);
    pthread_join(cid, NULL);
    sem_unlink("empty"); sem_unlink("full");
    EXIT_PROGRAM;
}