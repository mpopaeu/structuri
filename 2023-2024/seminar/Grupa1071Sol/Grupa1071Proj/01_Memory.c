#include <stdio.h>
#include <malloc.h>
#include <string.h>

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
	pa = NULL;

	char v[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x00};
	pa = v;

	printf("String(v) = %s\n", pa);

	pa = (char*)malloc(sizeof(v));
	strcpy(pa, v);

	*pa = *pa + 1;
	printf("String(v) = %s\n", v);
	printf("String(pa) = %s\n", pa);

	printf("One item: %c\n", pa[3]);
	printf("Other item outside the boundaries: %c\n", pa[13]);
	printf("Second item outside the boundaries: %c\n", pa[-5]);

	free(pa);
	return 0;
}