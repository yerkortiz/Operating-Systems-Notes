/*
 * ZOMBIE PROCESS
*/
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
int main(void) 
{ 
    char *const cmd[] = {"ps"};
    pid_t child_pid = fork(); 
    if (child_pid > 0){
        execvp("/bin/ps", cmd);
        sleep(1);
        wait(NULL);
        execvp("/bin/ps", cmd);
    } else {
        exit(0);
    }
    return 0; 
} 
