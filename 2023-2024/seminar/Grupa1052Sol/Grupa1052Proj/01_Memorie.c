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
	return 0;
}