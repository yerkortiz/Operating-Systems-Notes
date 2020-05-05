/*
 * SOLUCION A LOS FILOSOFOS COMENSALES
*/
#include <semaphore.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define EXIT_PROGRAM return 0
#define N 5
#define LEFT (phnum - 1  + N) % N // arreglo circular
#define RIGHT (phnum + 1) % N //arreglo circular
#define AND &&

enum {THINKING, HUNGRY, EATING} state[N];  
sem_t *phil[N];
sem_t *mutex;

void cat(char str[], int i) {
    int end = strlen(str);
    str[end++] = (char) i + '0';
    str[end] = '\0';
}
void test(int phnum) { 
    if (state[phnum] == HUNGRY  && state[LEFT] != EATING && state[RIGHT] != EATING) { //puede comer
        state[phnum] = EATING; 
        sleep(2); 
        printf("FILOSOFO %d TOMA TENEDOR %d Y TENEDOR %d\n", phnum + 1, LEFT + 1, phnum + 1); 
        printf("FILOSOFO %d COME Y LUEGO EXISTE\n", phnum + 1);
        sem_post(phil[phnum]); //actualiza semaforo del filosofo phnum
    } 
}
void takeFork(int phnum) {
    sem_wait(mutex); //entra al mutex
    state[phnum] = HUNGRY; // cambia de estado a tiene hambre
    printf("FILOSOFO %d TIENE HAMBRE\n", phnum + 1); 
    test(phnum); // dado que tiene hambre, intentará tomar los tenedores
    sem_post(mutex); // sale del mutex
    sem_wait(phil[phnum]); //actualiza semaforo del filosofo phnum
    sleep(1); 
} 
void putFork(int phnum) { 
    sem_wait(mutex); // entra
    state[phnum] = THINKING; // deja tenedores en la mesa y vuelve al estado de pensar
    printf("FILOSOFO %d DEJA TENEDOR %d Y TENEDOR %d EN LA MESA\n", phnum + 1, LEFT + 1, phnum + 1); 
    printf("FILOSOFO %d PIENSA Y LUEGO EXISTE\n", phnum + 1); 
    test(LEFT); //decirle a los filosofos de al lado que los tenedores que el usaba están desocupados
    test(RIGHT);
    sem_post(mutex); //sale
} 
  
void *philospher(void *num) { 
    while (1) { 
        int i = *((int *) num); //castear un void * en un int
        sleep(1); 
        takeFork(i); 
        sleep(0); 
        putFork(i); 
    } 
}

int main(void) {
    int i;
    pthread_t ph[N];
    char str[8] = "phil";
    cat(str, 1);
    for(i = 0; i < N; ++ i)
        sem_unlink(str);
    for(i = 0; i < N; ++ i)
        sem_open(str, O_CREAT, 0644, 0);
    sem_unlink("mutex");
    sem_open("mutex", O_CREAT, 0644, 1);
    for(i = 0; i < N; ++ i)
        sem_unlink(str);
    for(i = 0; i < N; ++ i)
        sem_open(str, O_CREAT, 0644, 0);
    sem_unlink("mutex");
    for (i = 0; i < N; i++) { 
        int *arg = malloc(sizeof(*arg));
        *arg = i;
        pthread_create(&ph[i], NULL, philospher, arg); 
    } 
    for (i = 0; i < N; i++) 
        pthread_join(ph[i], NULL); 
    EXIT_PROGRAM;
}