#include <stdio.h>
#include <malloc.h>

int main()
{
	signed char a;
	a = 65; // a = 'A';
	unsigned char b = 0x42;

	printf("%c = %d, %c = 0x%X\n", a, a, a, (unsigned char)a);
	printf("%c = %d, %c = 0x%X\n", b, b, b, b);

	printf("Adresa(a) = %p\n", &a);
	printf("Adresa(b) = %p\n", &b);

	signed char* pa = &a; // pa este variabila pointer; alocata in stack si initializata cu adresa de stack al lui a
	unsigned char* pb = &b; // pb este variabila pointer; alocata in stack si contine adresa de stack

	printf("Adresa(pa) = %p, Adresa(Continut(pa)) = %p\n", &pa, pa);
	printf("Adresa(pb) = %p, Adresa(Continut(pb)) = %p\n", &pb, pb);

	printf("String(pa) = %s\n", pa);

	pa = (signed char*)malloc(sizeof(a) + 1); // + 1 pentru terminator de string 0x00
	*pa = a;
	printf("String(pa) = %s\n", pa);
	pa[1] = 0;
	printf("String(pa) = %s\n", pa);

	free(pa);
	printf("String(pa) = %s\n", pa);

	pa = NULL;

	char v[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

	printf("Dimensiune vector v = %d\n", sizeof(v));
	pa = &v;

	printf("Elemente vector v = ");
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d", pa[i]);
	printf("\n");

	pa = (char*)malloc((sizeof(v) * 2) * sizeof(char));
	for (unsigned char i = 0; i < sizeof(v) * 2; i++)
	{
		unsigned char j = i % sizeof(v);
		pa[i] = i * v[j];
	}

	printf("Elemente vector pa din heap = ");
	for (unsigned char i = 0; i < sizeof(v) * 2; i++)
		printf(" %d", pa[i]);
	printf("\n");

	free(pa);
	pa = NULL;
	return 0;
}