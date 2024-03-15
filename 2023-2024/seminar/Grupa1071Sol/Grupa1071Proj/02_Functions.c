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

char allocHeap1(char* p, unsigned char size_bytes)
{
	p = (char*)malloc(size_bytes);
	if (p != NULL)
		return 1;
	return 0;
}

char allocHeap2(char** p, unsigned char size_bytes)
{
	*p = (char*)malloc(size_bytes);
	if (*p != NULL)
		return 1;
	return 0;
}

int main()
{
	char a = 3, b = 6;
	short int c = 0;

	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add1(a, b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = add2(a, &b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	char* pc = NULL;
	printf("pc = 0x%p\n", pc);
	char res = allocHeap1(pc, 3);
	printf("pc = 0x%p, function result: %d\n", pc, res);
	res = allocHeap2(&pc, 3);
	printf("pc = 0x%p, function result: %d\n", pc, res);

	free(pc);
	return 0;
}