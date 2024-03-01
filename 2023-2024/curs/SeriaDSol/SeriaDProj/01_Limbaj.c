#include <stdio.h>

int f() {
	static int x = 0;
	x++;
	return x;
}

int main()
{
	//// exemplu variabile de tip auto
	//int a = 8;
	//auto b = 9;

	//int c = a + b;

	//{
	//	int d;
	//	d = c;
	//}

	//printf("Suma = %d\n", c);

	//// exemplu variabile de tip register
	//register int vreg;
	//int d;

	//d = 8;
	//vreg = d;

	//printf("vreg = %d\n", vreg);

	//__asm
	//{
	//	mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
	//};


	// exemplu variabile statice
	int j;
	
	for (j = 0; j < 10; j++) {
		printf("Rezultat functie f: %d\n", f());
	}

	return 0;
}