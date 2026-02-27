#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	for (int i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	int suma = 0;

	for (int i = 1; i < argc; i++)
		suma += atoi(argv[i]);

	printf("Suma este: %d\n", suma);

	return 0;
}