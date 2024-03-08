#include <stdio.h>
#include <malloc.h>

int suma1(int x, int y)
{
	int z = 0;
	x += 1;
	y += x;

	z = x + y;
	return z;
}

int suma2(int x, int *y)
{
	int z = 0;
	x += 1;
	*y += x;

	z = x + *y;
	return z;
}

int allocHeap1(int* pi, char size)
{
	pi = (int*)malloc(size * sizeof(int));
	if (pi != NULL)
		return 1;
	else
		return 0;
}

int allocHeap2(int* *pi, char size)
{
	*pi = (int*)malloc(size * sizeof(int));
	if (*pi != NULL)
		return 1;
	else
		return 0;
}

int* allocStack()
{
	int v[] = {1, 2, 3, 4};
	return v;
}

int main()
{
	int a, b, c = 0;
	a = 10;
	b = 4;

	printf("a=%d , b=%d, c=%d\n", a, b, c);
	c = suma1(a, b);
	printf("a=%d , b=%d, c=%d\n", a, b, c);
	c = suma2(a, &b);
	printf("a=%d , b=%d, c=%d\n", a, b, c);

	int* pv = NULL, rez = -1;
	printf("pv=%p\n",pv);
	rez = allocHeap1(pv, a);
	printf("pv=%p, rezultat alocare=%d\n", pv, rez);
	rez = allocHeap2(&pv, a);
	printf("pv=%p, rezultat alocare=%d\n", pv, rez);


	free(pv);
	return 0;
}

