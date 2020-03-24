/*
 * ZOMBIE PROCESS
*/
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
int main(void) 
{ 
    pid_t child_pid = fork(); 
    if (child_pid > 0){
        system("ps -l");
        wait(NULL);
        /* kill(pid, SIGKILL); */
        /* printf("ZOMBIE EXITERMINADO\n"); */
        system("ps -l");
    } else {
        printf("ZOMBIE ID %d\n", getpid());
        exit(0);
    }
    return 0; 
} 
