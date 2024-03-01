#include <stdio.h>
#include <malloc.h>

int main()
{
	char a;
	a = -65; // a = 'A';
	char b = -66;

	printf("\"%c\" = %d OR 0x%02X\n\"%c\" = %d OR 0x%02X\n", a, (unsigned char)a, (unsigned char)a, 
		b, (unsigned char)b, (unsigned char)b);

	printf("String(a) = %s\n", &a);

	char* pa;
	pa = &a;

	printf("Content(a) = %d\n", *pa);

	pa = (char*)malloc(sizeof(a) + 1); // +1 for the end byte of the string 0x00
	*pa = a;
	pa[1] = 0;
	printf("String(a) = %s\n", pa);

	return 0;
}