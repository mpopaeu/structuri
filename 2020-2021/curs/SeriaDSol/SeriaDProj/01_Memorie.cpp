#include <stdio.h>

//unsigned char y = 0x3A; // 0x precizeaza format hexa

// Definire si utilizare variabile static
int f() {
	static int x = 0;
	x++;
	return x;
}
 
int main()
{
	//char x = 'A';

	//printf("%c\n", x);


	// Definire si utilizare variabile automatice
	int a = 8;
	auto b = 9.682;

	int c = a + b;

	printf("Suma = %d\n", c);


	// Definire si utilizare variabile register  

	register int vreg;
	int d;

	d = 8;
	vreg = d;

	printf("vreg = %d\n", vreg);

	__asm
	{
		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
		mov vreg, ecx;
	};

	printf("vreg = %d\n", vreg);

	// Definire si utilizare variabile static
	int j;
	for (j = 0; j < 10; j++) {
		printf("Rezultat functie f: %d\n", f());
	}

	return 0;
}