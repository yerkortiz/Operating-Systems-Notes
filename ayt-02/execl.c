#include <stdio.h>
#include <unistd.h>

int main(void)
{
    execl("./hola", "NOMBRE");
    return 0;
}