#include <stdio.h>
#include <malloc.h>

#define ARRAY_LENGTH 10

int main()
{
	char x = 'A';
	char y = 1;
	char z = -1;
	float w = 65.64;

	char* pc = NULL; // pc = 0;

	printf("Adresa stack pc = %p\n", &pc);
	printf("pc = %p\n", pc);
	//printf("*pc = %d\n", *pc); // stop executie: eroare de runtime pentru pc == 0

	pc = &x;
	printf("Adresa stack pc = %p\n", &pc);
	printf("pc = %p\n", pc); // adresa de stack pt x 
	printf("*pc = %d\n", *pc); // acces la locatia x

	pc = (char*)malloc(sizeof(char)); // alocare mem heap pe dimensiune de 1 byte
	printf("Adresa stack pc = %p\n", &pc);
	printf("pc = %p\n", pc); // adresa de heap alocata pe #22
	printf("*pc = %d\n", *pc);

	*pc = z;
	printf("Adresa stack pc = %p\n", &pc);
	printf("pc = %p\n", pc); // adresa de heap alocata pe #22
	printf("*pc = %d\n", *pc);

	free(pc);

	pc = (char*)malloc(ARRAY_LENGTH * sizeof(char));

	for (unsigned char i = 0; i < ARRAY_LENGTH; i++)
	{
		pc[i] = x + i;
	}
	for (unsigned char i = 0; i < ARRAY_LENGTH; i++)
	{
		printf("%c", pc[i]); // elemente vector pc din mem heap afisate ca simboluri ASCII cu descriptor %c
	}


	free(pc);

	return 0;
}