#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	printf("\n\n");

	int sum = 0;
	for (int i = 0; i < argc; i++)
		sum += atoi(argv[i]);

	printf("Sum  = %d\n", sum);

	return 0;
}