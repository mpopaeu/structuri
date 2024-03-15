#include <stdio.h>
#include <malloc.h>

int suma1(char x, char y)
{
	int z = 0;
	x += 1;
	y += x;

	z = x + y;
	return z;
}


int suma2(char x, char* y)
{
	int z = 0;
	x += 1;
	*y += x;

	z = x + *y;
	return z;
}

char allocHeap1(char* pc, unsigned char size)
{
	pc = (char*)malloc(size * sizeof(char));
	if(pc != NULL)
		return 1;
	return 0;
}

char allocHeap2(char* *pc, unsigned char size)
{
	*pc = (char*)malloc(size * sizeof(char));
	if (*pc != NULL)
		return 1;
	return 0;
}

char* allocStack(unsigned char* size)
{
	char v[] = {1, 2, 3, 4, 5, 6};
	*size = sizeof(v) / sizeof(char);
	return v;
}

char* allocStack2(unsigned char* size)
{
	char v[] = { 1, 2, 3, 4, 5, 6 };
	*size = sizeof(v) / sizeof(char);
	char* pv = (char*)malloc(sizeof(v));

	for (unsigned char i = 0; i < sizeof(v) / sizeof(char); i++)
		pv[i] = v[i];

	return pv;
}

int main()
{
	char a = 3, b = 8;
	int c = 0;

	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = suma1(a, b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = suma2(a, &b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	char* p = NULL;
	printf("p = 0x%p\n", p);
	char rez = allocHeap1(p, (unsigned char)a); // genereaza mem leak
	printf("p = 0x%p, rezultate functie = %d\n", p, rez);
	rez = allocHeap2(&p, (unsigned char)a);
	printf("p = 0x%p, rezultate functie = %d\n", p, rez);

	free(p);
	p = NULL;


	unsigned char dim = 0;
	p = allocStack(&dim);
	printf("Vector alocat in stack seg in functie:");
	for (unsigned char i = 0; i < dim; i++)
		printf(" %d", p[i]);
	printf("\n");

	p = allocStack2(&dim);
	printf("Vector alocat in heap seg in functie:");
	for (unsigned char i = 0; i < dim; i++)
		printf(" %d", p[i]);
	printf("\n");

	free(p);
	return 0;
}