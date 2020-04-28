#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define EXIT_PROGRAM return 0
#define N 8 // cantidad inicial de oxigenos
#define M 8 // cantidad inicial de hidrogenos

sem_t *oxy_s, *hyd_s;
pthread_mutex_t mutex;
int oxy, hyd; // contador de oxigeno e hidrogeno 

void *oxygen(void *arg) // thread oxigeno
{
    pthread_mutex_lock(&mutex);
    ++oxy;
    if (hyd >= 2){ // craftear molecula
        sem_post(hyd_s);
        sem_post(hyd_s);
        hyd -= 2;
        sem_post(oxy_s);
        --oxy;
        printf("MOLECULA CRAFTEADA\n");
    } else { 
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    sem_wait(oxy_s);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
void *hydrogen(void *arg) //thread de hidrogeno
{
    pthread_mutex_lock(&mutex);
    ++hyd;
    if (hyd >= 2 && oxy>= 1) { //craftear una molecula
        sem_post(hyd_s);
        sem_post(hyd_s);
        hyd -= 2;
        sem_post(oxy_s);
        --oxy;
        printf("MOLECULA CRAFTEADA\n");
    } else {
        pthread_mutex_unlock(&mutex);
        pthread_exit(NULL);
    }
    sem_wait(hyd_s);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
int main(void)
{
    int i;
    pthread_mutex_init(&mutex, NULL);
    sem_unlink("oxy_s"); sem_unlink("hyd_s"); // dar nombre al semaforo
    oxy_s = sem_open("oxy_s", O_CREAT, 0644, 0); // inicializar semaforo
    hyd_s = sem_open("hyd_s", O_CREAT, 0644, 0); //inicializar semaforo
    pthread_t ox[N], hy[M]; //
    for(i = 0; i < N; ++i)
        pthread_create(&ox[i], NULL, oxygen, NULL);
    for(i = 0; i < M; ++i)
        pthread_create(&hy[i], NULL, hydrogen, NULL);
    for(i = 0; i < N; ++i)
        pthread_join(ox[i], NULL);
    for(i = 0; i < M;++ i)
        pthread_join(hy[i], NULL);
    sem_unlink("oxy_s"); sem_unlink("hyd_s");
    EXIT_PROGRAM;
}
