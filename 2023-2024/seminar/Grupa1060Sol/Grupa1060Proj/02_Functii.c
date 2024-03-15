#include <stdio.h>
#include <malloc.h>

short int suma1(char x, char y)
{
	short int z = 0;

	x += 1;
	y += x;

	z = x + y;

	return z;
}

short int suma2(char x, char* y)
{
	short int z = 0;

	x += 1;
	*y += x;

	z = x + *y;

	return z;
}

int allocHeap1(char* p, char size)
{
	p = (char*)malloc(sizeof(size));
	if (p != NULL)
		return 1;
	return 0;
}

int allocHeap2(char* *p, char size)
{
	*p = (char*)malloc(sizeof(size));
	if (*p != NULL)
		return 1;
	return 0;
}

int main()
{
	char a = 2, b = 6;
	short int c = 0;

	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = suma1(a, b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	c = suma2(a, &b);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	char* p = NULL;
	char size = 10;
	printf("p = 0x%p\n", p);
	char rez = allocHeap1(p, size); // genereaza memory leak; alocare adresa heap vizibila doar in functie
	printf("p = 0x%p, alocare confirmata: %d\n", p, rez);
	rez = allocHeap2(&p, size);		// adresa de heap este salvata in p;
	printf("p = 0x%p, alocare confirmata: %d\n", p, rez); // confirmare adresa heap in p si efectuarea alocarii

	free(p); // dezalocare memorie heap a carei adresa a fost salvata in p din functia allocHeap2
	return 0;
}