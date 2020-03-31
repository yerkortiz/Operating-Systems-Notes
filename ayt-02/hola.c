#include <stdio.h>
#include <unistd.h>
int main(int argv, char **argc)
{
    printf("%d ", getpid());
    char *const cmd[] = {"ps"};
    execvp("/bin/ps", cmd);
    printf("Hola\n");
    return 0;
}