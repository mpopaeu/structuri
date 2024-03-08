#include <stdio.h>

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
	c = add1(a, b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add2(a, &b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	char* pc = NULL;
	printf("pc = 0x%p\n", pc);
	char result = allocHeap1(pc, a);
	printf("pc = 0x%p, allocated = %d\n", pc, result);

	return 0;
}