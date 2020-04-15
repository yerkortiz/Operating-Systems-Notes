#include <stdio.h>
#include <unistd.h>

int main(int argv, char **argc)
{
    execl("./asdas", NULL);
    return 0;
}