#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <errno.h>
int main(void)
{
    pid_t pid = fork();
    int status;
    if(pid < 0) // aqui hubo un error
        return 0;
    else if(pid == 0) // aqui estamos en el hijo
        printf("OWN ID %d | PARENT ID %d\n", getpid(), getppid());
    else { //aqui estamos en el padre
        printf("OWN ID %d | PARENT ID %d\n", getpid(), getppid());
        wait(&status);
    }
    return 0;
}