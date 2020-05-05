/*
 * LECTOR ESCRITOR USANDO SEMAFOROS
 * PD: sem_open LO USO SOLAMENTE PORQUE sem_init 
 * ESTA DEPRECADO EN OSX Y YA NO ESTA FUNCIONAL,
 * SI USAN LINUX PREFIERAN sem_init, TODO LES SALDRA
 * DE MANERA MAS SENCILLA.
*/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define EXIT_PROGRAM return 0
#define STR_SIZE (1 << 8) // 1 << 8 = 2 ^ 8 = 256
#define TRUE 1

char PERGAMINO[STR_SIZE]; // seccion de memoria, donde escribo
pthread_mutex_t mutex; 
sem_t *acc;
int rc, // número de lectores actualmente
    i;

void *reader(void *arg)
{
    while(TRUE)
    {
        pthread_mutex_lock(&mutex);
        ++rc;
        printf("LEYENDO EL PERGAMINO: %s\n", PERGAMINO);
        if(rc) sem_wait(acc);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        pthread_mutex_lock(&mutex);
        --rc;
        if(!rc) sem_post(acc);
        pthread_mutex_unlock(&mutex);
    }
}
void *writer(void *arg)
{
    while(TRUE)
    {
        sem_wait(acc);
        printf("ESCRIBIENDO EL PERGAMINO %d\n", i);
        sleep(1);
        PERGAMINO[i++] = 'A';
        PERGAMINO[i] = '\0';
        sem_post(acc);
    }
}
int main(void)
{
    pthread_t rd, wt;
    pthread_mutex_init(&mutex, NULL);
    sem_unlink("acc");
    acc = sem_open("acc", O_CREAT, 0644, 1);
    pthread_create(&rd, NULL, reader, NULL);
    sleep(0.1);
    pthread_create(&wt, NULL, writer, NULL);
    pthread_join(rd, NULL);
    sleep(0.1);
    pthread_join(wt, NULL);
    sem_unlink("acc");
    EXIT_PROGRAM;
}