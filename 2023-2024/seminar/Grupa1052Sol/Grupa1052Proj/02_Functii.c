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

int* allocStack(unsigned char *size) // size - nr de bytes
{
	int v[] = {1, 2, 3, 4};
	*size = sizeof(v);

	return v;
}

int* allocStackCorect(unsigned char* size) // size - nr de bytes
{
	int v[] = { 1, 2, 3, 4 };
	*size = sizeof(v);

	int* pv = (int*)malloc(sizeof(v));
	for (unsigned char i = 0; i < sizeof(v) / sizeof(int); i++)
		pv[i] = v[i];

	return pv;
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
	pv = NULL;

	unsigned char nr_bytes = 0;
	pv = allocStack(&nr_bytes); // adresa temporara de vector (var locala) este returnata
	printf("Elemente vector v:");
	for (unsigned char i = 0; i < nr_bytes / sizeof(int); i++)
		printf(" %d", pv[i]);
	printf("\n");

	pv = allocStackCorect(&nr_bytes); // adresa de heap unde eleme v au fost copiata in functie
	printf("Elemente vector pv:");
	for (unsigned char i = 0; i < nr_bytes / sizeof(int); i++)
		printf(" %d", pv[i]);
	printf("\n");


	free(pv);
	return 0;
}

