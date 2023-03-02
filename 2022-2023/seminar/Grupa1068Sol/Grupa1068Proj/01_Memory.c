
#include <stdio.h>

#define VECTOR_SIZE 10

int main()
{
	char c; // c - local variable; 1 single byte; signed representation
	char v[VECTOR_SIZE]; // v - uni-dimensional array; access to items by using operator []
	char* pc; // pc - pointer to char
	unsigned char i;

	c = 11; // c = 0x0B;
	pc = v; // v - starting memory address of the byte array

	for (i = 0; i < VECTOR_SIZE; i++)
		v[i] = i + 1;

	short int* pi;
	pi = (short int*)v; // v shared by both pc and pi

	printf("Parse the array v as char items:\n");
	for (i = 0; i < VECTOR_SIZE; i++) // VECTOR_SIZE items as char
	{
		printf("pc[%d]=%d\n", i + 1, pc[i]);
	}

	printf("Parse the array v as short int items:\n");
	for (i = 0; i < VECTOR_SIZE / 2; i++) // VECTOR_SIZE / 2 as short int
	{
		printf("pi[%d]=%d\n", i + 1, pi[i]);
	}

	return 0;
}