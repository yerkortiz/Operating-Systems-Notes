#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
#include <sys/wait.h>
int main() 
{ 
    int N = 5;
    for(int i = 0; i < N; i++) { 
        int pid = fork();
        if(pid == 0) {
            printf(" HIJO (pid %d) DEL PADRE (pid %d)\n", getpid(), getppid()); 
            exit(0);
        } 
    }
    for(int i = 0; i < N; i++) wait(NULL);
    return 0;
} 