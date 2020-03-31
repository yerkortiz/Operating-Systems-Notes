/*
 * ZOMBIE PROCESS
*/
#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
/* zombie */
int main(void) 
{ 
    char *const cmd[] = {"ps, -l"};
    pid_t child_pid = fork(); 
    if (child_pid > 0){ // padre
        //execvp("/bin/ps", cmd);
        sleep(1);
        system("ps -l");
        wait(NULL);//por eso es importante usar bien wait
        system("ps -l");
        //execvp("/bin/ps", cmd);
    } else { //hijo
        exit(0);
    }
    return 0; 
} 
