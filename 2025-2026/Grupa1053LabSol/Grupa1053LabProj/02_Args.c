#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	for (unsigned char i = 0; i < argc; i++)
		printf("%s\n", argv[i]);

	unsigned int suma = 0;

	for (unsigned char i = 0; i < argc; i++)
		suma += atoi(argv[i]);

	printf("Suma  = %d\n\n", suma);

	return 0;
}