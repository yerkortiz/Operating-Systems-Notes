#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <errno.h>

#define EXIT_PROGRAM return 0

int main(void)
{
    pid_t pid = fork();
    int status;
    int value = 1;
    if(pid < 0) {
        perror("FORK ERROR\n");
        exit(1);
    } else if(pid == 0) {
        value += value;
        printf("OWN ID %d | PARENT ID %d | OWN VALUE %d\n", getpid(), getppid(), value);
        exit(0);
    } else {
        printf("OWN ID %d | PARENT ID %d | OWN VALUE %d\n", getpid(), getppid(), value);
        wait(&status);
    }
    EXIT_PROGRAM;
}
