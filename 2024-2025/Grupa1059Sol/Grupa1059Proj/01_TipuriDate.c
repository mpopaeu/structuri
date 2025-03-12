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
	printf("pc = %p\n", pc); // adresa de heap alocata pe linia #22
	printf("*pc = %d\n", *pc);

	free(pc);

	pc = (char*)malloc((ARRAY_LENGTH + 1) * sizeof(char)); // +1 deoarece am nevoie de byte terminator string 0x00

	for (unsigned char i = 0; i < ARRAY_LENGTH; i++)
	{
		pc[i] = x + i;
	}
	pc[ARRAY_LENGTH] = 0;
	for (unsigned char i = 0; i < ARRAY_LENGTH; i++)
	{
		printf("%c", pc[i]); // elemente vector accesate din mem heap prin pointer pc 
							 // afisate ca simboluri ASCII cu descriptor %c
	}
	
	printf("\n%s\n", pc);
	free(pc);

	char v[ARRAY_LENGTH + 1];
	for (unsigned char i = 0; i < ARRAY_LENGTH; i++)
	{
		v[i] = x + i;
	}
	v[ARRAY_LENGTH] = 0;
	pc = v;
	printf("\nv = %s\n", pc);


	return 0;
}