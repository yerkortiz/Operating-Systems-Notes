#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 3
void child(int i)
{
    int pid;
    printf("HIJO %d (pid %d) DEL PADRE (pid %d) \n", i,  getpid(), getppid());
    if (i == MAX)
        return;
    pid = fork();
    if (pid < 0)
        printf("ERROR\n");
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);
    exit(0);
}

int main() {
    printf("SOY EL PROCESO MAIN (PID %d) \n", getpid());
    int i = 0;  
    int pid = fork();
    if (pid < 0){
        printf("ERROR\n");
        return 1;
    }
    else if (pid == 0)
        child(++i);
    else
        waitpid(pid, NULL, 0);
    return 0;
}