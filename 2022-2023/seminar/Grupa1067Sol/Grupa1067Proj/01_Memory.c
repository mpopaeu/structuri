#include <stdio.h>
#include <malloc.h>

#define VECTOR_SIZE 10

int main()
{
	char c;		// one single item location
	char v[VECTOR_SIZE];	// array with max 10 items; could be indexed up to offset 9
	char* pc;	// pointer to char location(s)

	c = 91; // c = 0x0b;

	unsigned char i;
	//for (i = 0; i < VECTOR_SIZE; i++)
	//	v[i] = i + 1;

	pc = &v;

	for (i = 0; i < VECTOR_SIZE / 2; i++)
		v[i] = i + 1;		// first half of the vector initialized by using variable v
	for (; i < VECTOR_SIZE; i++)
		pc[i] = i + 1;		// second half of the vector initialized by using variable pc

	printf("c=%d,\" c=%c\n", c, c);	// print out same location named c in different formats (integer, ASCII)

	short int* pi;
	pi = &v;

	printf("Array v parsed by pointer to char pc:\n");
	for (i = 0; i < VECTOR_SIZE; i++)
		printf("pc[%d]=%d\n", i + 1, pc[i]);

	printf("Array v parsed by pointer to short int pi:\n");
	for (i = 0; i < VECTOR_SIZE / 2; i++)
		printf("pi[%d]=%d\n", i + 1, pi[i]);

	pc = (char*)malloc(VECTOR_SIZE);
	for (i = 0; i < VECTOR_SIZE; i++)
		pc[i] = i + 1;

	pi = (short int*)malloc(VECTOR_SIZE * sizeof(short int));
	for (i = 0; i < VECTOR_SIZE; i++)
		pi[i] = i * 10 + 1;


	free(pc);
	free(pi);
	return 0;
}