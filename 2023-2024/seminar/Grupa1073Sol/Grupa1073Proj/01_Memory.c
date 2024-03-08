#include <stdio.h>
#include <malloc.h>
#include <string.h>

int main()
{
	char a;
	a = -65; // a = 'A';
	char b = -66;

	printf("\"%c\" = %d OR 0x%02X\n\"%c\" = %d OR 0x%02X\n", a, (unsigned char)a, (unsigned char)a, 
		b, (unsigned char)b, (unsigned char)b);

	printf("String(a) = %s\n", &a);

	char* pa;	// pointer variable
	pa = &a;	// pa written by stack seg mem address of a

	printf("Content(a) = %d\n", *pa); // prints all bytes as ASCII symbols till first null byte

	pa = (char*)malloc(sizeof(a) + 1); // +1 for the end byte of the string 0x00
	*pa = a;	// pa[0] = a;
	pa[1] = 0;	// *(pa + 1) = 0;
	printf("String(a) = %s\n", pa);

	free(pa);
	pa = NULL; // to avoid the access to older heap seg mem address released by free(pa)

	char v[] = {0x0a, 0x1a, 0x2a, 0x3a, 0x4a};
	pa = v;

	printf("Vector content: ");
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d", pa[i]);
	printf("\n");

	char* my_string = "String in C";
	pa = (char*)malloc((strlen(my_string) + 1 )* sizeof(char)); // +1 for null byte as the phisical end of the string
	strcpy(pa, my_string);

	printf("The string copied into heap seg: %s\n", pa);

	free(pa);
	return 0;
}