#include<stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
typedef unsigned int uint32_t;
int main() 
{    
    int pid = fork(); 
    if (pid > 0) 
        printf("in parent process"); 
    else if (pid == 0) { 
        sleep(50); 
        printf("in child process"); 
    }
    return 0; 
} 