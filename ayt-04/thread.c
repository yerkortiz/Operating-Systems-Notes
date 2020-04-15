#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 
void *helloThread(void *vargp) 
{ 
    printf("Hola, mundo!\n");  
    sleep(1); 
    pthread_exit(NULL);
} 
int main(int argv, char** argc)
{ 
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, helloThread, NULL); 
    pthread_join(thread_id, NULL); 
    return 0;
}