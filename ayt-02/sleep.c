#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{    
    char *const cmd[] = {"ps, -l"};
    int pid = fork(); 
    if (pid > 0) {
        execvp("/bin/ps", cmd);
        printf("in parent process %d", getpid()); 
    } else if (pid == 0) { 
        sleep(2); 
        printf("in child process"); 
        printf("%d ", getpid());
        execvp("/bin/ps", cmd);
        kill(getpid(), SIGKILL);
    } 
    return 0; 
} 