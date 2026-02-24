#include <stdio.h>
#include <malloc.h>

int main()
{
	char a = 11;
	char b = -11;

	printf("a = %d\n", a);
	printf("b = %d\n", b);

	printf("Adress(a) = 0x%p\n", &a);
	printf("Adress(b) = 0x%p\n", &b);

	char* p = NULL;

	printf("p = 0x%p\n", p);
	printf("Adress(p) = 0x%p\n", &p);

	p = &a; // stack seg mem address stored by pointer p
	printf("p = 0x%p\n", p);
	printf("Adress(p) = 0x%p\n", &p);

	// &a = &b;  // stack seg mem addresses cannot be changed

	*p = a - 14;
	printf("a = %d\n", a);
	printf("Adress(a) = 0x%p\n", &a);
	printf("Adress(p) = 0x%p\n", &p);

	char v[] = {9, 8, 7, 9, 9, 5, 3, 6};
	printf("Size of v = %d bytes\n", sizeof(v));
	printf("Adress(v) = 0x%p\n", &v);

	p = v;
	printf("Size of v = %d bytes\n", sizeof(v));
	printf("Size of p = %d bytes\n", sizeof(p));

	p = malloc(sizeof(v));

	for (unsigned char i = 0; i < sizeof(v); i++)
		p[i] = v[i] - 1;


	char m[][3] = { {1, 2, 3}, {4, 5, 6} };

	char** pm = NULL;

	pm = malloc(2 * sizeof(char*));
	for (unsigned char i = 0; i < 2; i++)
	{
		pm[i] = malloc(3 * sizeof(char));
	}

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = m[i][j] - 1;
	}

	free(p);
	return 0;
}