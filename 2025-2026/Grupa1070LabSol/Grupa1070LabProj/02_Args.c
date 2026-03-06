#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("Argument count: %d\n", argc);

	for (int i = 0; i < argc; i++)
		printf("Argument #%d: %s\n", i + 1, argv[i]);

	int sum = 0;
	for (int i = 1; i < argc; i++)
		sum += atoi(argv[i]);

	printf("Sum is = %d\n", sum);

	return 0;
}