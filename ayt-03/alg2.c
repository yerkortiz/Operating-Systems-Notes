#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#define WAIT_TREE for( ; wait (NULL) > 0 ;)
int main()
{
    if(fork() || fork())// 1, 2, 3, 4, 5
        fork();
    printf("%d ", 1);
    WAIT_TREE;
    return 0;
}