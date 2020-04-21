#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define EXIT_PROGRAM return 0
#define BUFFER_SIZE (1U << 10) // 1024

int buffer[BUFFER_SIZE];
int front, tail, size;
void enqueue(int n)
{
    if(size == BUFFER_SIZE - 1) return;
    else buffer[tail++] = n;
    tail %= BUFFER_SIZE;
    ++size;
}
void dequeue()
{   
    if(size == 0) return ;
    else buffer[front++] = 0;
    front %= BUFFER_SIZE;
    --size;
}
pthread_cond_t empty = PTHREAD_COND_INITIALIZER,
    full = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex;
int loops = 10;

void *producer (void * arg) 
{
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex);
        while (size == BUFFER_SIZE - 1) 
            pthread_cond_wait(&empty, &mutex);
        printf("PRODUCIENDO %d \n", i);
        enqueue(i) ;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex); 
    } 
    pthread_exit(NULL);
}
void *consumer (void * arg) {
    for (int i = 0; i < loops; i++) {
        pthread_mutex_lock(&mutex); 
        while (size == 0) 
            pthread_cond_wait(&full, &mutex); 
        int tmp = buffer[front];
        dequeue();
        pthread_cond_signal(&empty); 
        pthread_mutex_unlock(&mutex); 
        printf("CONSUMIENDO %d \n", tmp);
    }
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
    EXIT_PROGRAM;
}