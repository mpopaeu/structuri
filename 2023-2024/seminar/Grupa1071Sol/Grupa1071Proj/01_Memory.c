#include <stdio.h>
#include <malloc.h>

int main()
{
	signed char a;
	a = -65;

	unsigned char b = 66;

	printf("\"%c\" = %d or 0x%02X @memory (in stack) 0x%p\n", a, a, (unsigned char)a, &a);
	printf("\"%c\" = %d or 0x%X @memory (in stack) 0x%p\n", b, b, b, &b);
	printf("\"%c\" = %d\n", a, (unsigned char)a);

	char* pa;
	pa = &a;
	printf("pa = 0x%p, Content(pa) = %d\n", pa, *pa);
	printf("String(pa) = %s\n", pa);

	pa = malloc(sizeof(a) + 1); // +1 byte for standard end of the string (last byte is 0x00)
	*pa = a;			// same like pa[0]
	*(pa + 1) = 0;		// same like pa[1]
	printf("String(pa) = %s\n", pa);

	free(pa);

	return 0;
}