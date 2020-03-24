#include <stdio.h>
#include <unistd.h>

int main(void)
{
	printf("L0\n");
 	fork();
 	printf("L1\n");
 	fork();
 	printf("Bye\n");
	wait(NULL);
	return 0;
}
