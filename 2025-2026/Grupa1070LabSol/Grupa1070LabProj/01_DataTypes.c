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

	char** pm;

	pm = malloc(2 * sizeof(char*)); // allocation of the intermediary structure (starting addresses of the rows)
	for (unsigned char i = 0; i < 2; i++)
		pm[i] = malloc((3 + 1) * sizeof(char)); // allocation of row i; +1 to make room for the null byte terminator

	for (unsigned int i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = 'A' + m[i][j];
		pm[i][3] = 0; // add null byte terminator on the last item of the row i
	}

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < (3 + 1); j++)
			printf(" %d->%c ", pm[i][j], pm[i][j]);
		printf("\n");
	}

	for (unsigned char i = 0; i < 2; i++)
		printf(" %s\n", pm[i]);

	// deallocation of bytearray p
	free(p);

	// deallocation of matrix pm
	for (unsigned char i = 0; i < 2; i++)
		free(pm[i]); // deallocation of the row i
	free(pm); // deallocate the intermediary structure (strating addresses of the rows)

	return 0;
}