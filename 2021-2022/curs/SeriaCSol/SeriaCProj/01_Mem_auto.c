#include <stdio.h>

void main()
{
	int a = 8;
	auto float b = (float)9.12;

	int c = (int)(a + b);

	printf("Suma = %d\n", c);

	auto s = "Structuri";
	printf("S = %s\n", (char*)s);
}