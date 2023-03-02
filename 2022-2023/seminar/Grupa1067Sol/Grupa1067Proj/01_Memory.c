#include <stdio.h>
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
		v[i] = i + 1;
	for (; i < VECTOR_SIZE; i++)
		pc[i] = i + 1;

	printf("c=%d,\" c=%c\n", c, c);

	short int* pi;
	pi = &v;


	return 0;
}