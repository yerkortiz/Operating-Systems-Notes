#include <stdio.h>
#include <unistd.h>
int main(void)
{
    fork();
    fork();
    fork();
    fork();
    fork();
    return 0;
}