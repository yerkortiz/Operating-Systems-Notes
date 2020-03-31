#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <errno.h>
#define DEPTH 4

int main (int argv, char **argc)
{
    pid_t pid;
    int i;
    for (i = 0; i < DEPTH; i++) {
        pid = fork();
        if (pid) break;  
    }
    wait(NULL);      
    return 0;
}