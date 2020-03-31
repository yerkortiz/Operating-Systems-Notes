#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(void)
{
	printf("L0\n");
 	fork();//creando un nuevo proceso
 	printf("L1\n");
	wait(NULL);//padre espera al hijo
	return 0;
}
