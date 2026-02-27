#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 18;
	char y = -18;

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	char* p = NULL;
	printf("p = 0x%p\n", p);

	printf("adress(x) = 0x%p\n", &x);
	printf("adress(y) = 0x%p\n", &y);
	printf("adress(p) = 0x%p\n", &p);

	//*p = x - 5; // there is no null memory address where I can store or get content

	p = &y; 
	*p = x - 5;
	printf("y = %d\n", y);
	printf("p = 0x%p\n", p);
	printf("address(p) = 0x%p\n", &p);

	// &x = &y; // stack seg memory address cannot be changed once allocated

	char v[] = {1, 2, 3, 1, 1, 7, 8, 9};
	printf("address(v) = 0x%p\n", v);
	printf("size(v) = %d bytes\n", sizeof(v));

	p = v; 
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d ", p[i]);
	printf("\n\n");

	// allocation of bytearray p
	p = malloc(sizeof(v));

	printf("p = 0x%p\n", p);
	printf("address(p) = 0x%p\n", &p);
	printf("size(p) = %d bytes\n", sizeof(p));

	for (unsigned char i = 0; i < sizeof(v) - 1; i++)
		p[i] = 'A' + i;
	p[sizeof(v) - 1] = 0; // the null byte will be added at the end of the bytearray considered as string

	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d -> %c ", p[i], p[i]);
	printf("\n\n");

	printf("%s\n\n", p);


	char m[][3] = { {1, 1, 1}, {5, 6, 7} };

	// deallocation of bytearray p
	free(p);
	return 0;
}