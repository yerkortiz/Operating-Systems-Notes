#include <stdio.h>
#include <unistd.h>

int main(void)
{
    execl("./hola", "NULL");
    return 0;
}