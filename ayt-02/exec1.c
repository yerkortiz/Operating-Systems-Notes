#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int arcv, char **argc)
{
    char *myargs[3];
    myargs[0] = strdup("cat"); 
    myargs[1] = strdup("fork1.c"); 
    myargs[2] = NULL; 
    printf("PROCESO MAIN (pid:%d)\n", (int) getpid());
    int child = fork();
    if (child < 0) { 
        printf("ERROR\n");
        exit(1);
    } else if (child == 0) { //
        printf("PROCESO HIJO (PID:%d)\n", (int) getpid());
        execvp(myargs[0], myargs); 
        printf("CAT DEL ARCHIVO %s\n", myargs[1]);
    } else { 
        wait(NULL);
        printf("PROGRAMA TERMINADO\n");
    }
    return 0;
}