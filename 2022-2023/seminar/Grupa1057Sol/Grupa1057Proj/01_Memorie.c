#include <stdio.h>

#define VECTOR_SIZE 8

int main()
{
	char c, v[VECTOR_SIZE], * pc;

	c = 10; // c = 0x0A;

	pc = v; // adresa segment de stack unde se afla alocat vectorul v

	unsigned char i;
	for (i = 0; i < VECTOR_SIZE / 2; i++)
		v[i] = i + 1;

	for (; i < VECTOR_SIZE; i++)
		pc[i] = i + 1;

	printf("c = %d\n", c);
	printf("c = %02X\n", c);
	printf("Adr(c) = %p\n", &c);

	printf("Adrese variabila pointer pc: Adr(pc) = %p, Cont(pc) = %p\n", &pc, pc);

	printf("Acces la elemente in afara zonei alocate pentru vectorul v: v[10] = %d, v[-3] = %d\n", v[10], v[-3]);

	short int* pi;

	pi = (short int *)v;

	printf("Mapare pointer int peste vectorul v si acces la elemente de tip short int: \n")
	for (i = 0; i < VECTOR_SIZE / 2; i++)
		printf("pi[%d]=%d ", i + 1, pi[i]);
	printf("\n\n");

	return 0; 
}