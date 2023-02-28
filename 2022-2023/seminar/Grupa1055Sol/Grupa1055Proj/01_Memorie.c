#include <stdio.h>

#define VECTOR_SIZE 10

int main()
{
	char c, v[VECTOR_SIZE], *pc;

	c = 10; // c = 0x0A;

	pc = v; 

	unsigned char i;
	for (i = 0; i < VECTOR_SIZE / 2; i++)
		v[i] = i + 1;

	for (; i < VECTOR_SIZE; i++)
		pc[i] = i + 1;

	printf("c=%d, c=%c, c=%02X\n", c, c, c);
	printf("v[11]=%d, v[-3]=%d\n", v[11], v[-3]);
	printf("pc[11]=%d, pc[-3]=%d\n", pc[11], pc[-3]);

	short int* pi;

	pi = (short int *)v;

	for (i = 0; i < VECTOR_SIZE / 2; i++)
		printf("pi[%d]=%d ", i + 1, pi[i]);
}