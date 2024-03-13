#include <stdio.h>
#include <malloc.h>

short int add1(char x, char y)
{
	short int z = 0;
	x += 1;
	y += x;

	z = x + y;
	return z;
}

short int add2(char x, char* y)
{
	short int z = 0;
	x += 1;
	*y += x;

	z = x + *y;
	return z;
}

char allocHeap1(char* p, unsigned char size)
{
	p = (char*)malloc(size * sizeof(char));
	if (p)
		return 1;
	return 0;
}

char allocHeap2(char* *p, unsigned char size)
{
	*p = (char*)malloc(size * sizeof(char));
	if (*p)
		return 1;
	return 0;
}

int main()
{
	char a = 2, b = 7;
	short int c = 0;

	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add1(a, b); // a & b passed by "value": changes over a and/or b not visible outside the function add1
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add2(a, &b); // a passed by "value", b passed by "address": 
					 // changes over b (by using *b) ARE visible outside the function add2
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	char* pc = NULL;
	printf("pc = 0x%p\n", pc);
	char result = allocHeap1(pc, a); // pc & a passed by "value": changes over pc are NOT visible outside the functin allocHeap1
									 // allocHeap1 generates memory leak because the heap address is not available in function main
	printf("pc = 0x%p, allocated = %d\n", pc, result);
	result = allocHeap2(&pc, a); // pc passed by "address": changes over pc ARE visible outside the function allocHeap2
	printf("pc = 0x%p, allocated = %d\n", pc, result);


	free(pc);
	return 0;
}