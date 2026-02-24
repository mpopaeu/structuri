#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	for (unsigned char i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	int suma = 0;
	for (unsigned char i = 1; i < argc; i++)
	{
		int valoare = atoi(argv[i]);
		suma += valoare;
	}

	printf("Suma este: %d\n\n", suma);

	return 0;
}