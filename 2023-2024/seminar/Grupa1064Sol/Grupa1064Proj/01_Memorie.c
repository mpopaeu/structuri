#include <stdio.h>
#include <malloc.h>

int main()
{
	signed char a;
	a = -65; // a = 'A';
	unsigned char b = 0x42;

	printf("\'%c\' = %d, \'%c\' = 0x%X\n", a, a, a, (unsigned char)a);
	printf("\'%c\' = %d, \'%c\' = 0x%X\n", b, b, b, b);
	printf("\'%c\' = %d\n", a, (unsigned char)a);

	a += b;

	printf("\'%c\' = %d\n", a, a);

	printf("String(a) = %s\n", &a);
	char* pa;
	pa = &a;
	printf("String(a) = %s\n", pa);
	*pa = b;

	pa = (char*)malloc(sizeof(a) + 1);
	*pa = a;
	*(pa + 1) = 0; // pa[1] = 0;
	printf("String(a) = %s\n", pa);

	free(pa);
	pa = NULL;

	char v[] = {0x0a, 0x0b, 0x0c, 0x0d, 0x0e};
	pa = v;
	printf("Elemente vector:");
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d", pa[i]);
	printf("\n");
	
	pa = (char*)malloc((sizeof(v) * 2) * sizeof(char));
	for (unsigned char i = 0; i < sizeof(v) * 2; i++)
	{
		unsigned char j = i % sizeof(v);
		pa[i] = v[j] * 10 + 1;
	}
	printf("Elemente vector din heap:");
	for (unsigned char i = 0; i < sizeof(v) * 2; i++)
		printf(" %d", pa[i]);
	printf("\n");

	free(pa);
	pa = NULL;
	return 0;
}