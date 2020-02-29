#include "Headers.h"
#include <stdio.h>

//int f() {
//	static int x = 0;
//	x++;
//	return x;
//}

// variabile externe
// int i; // i variabila globala

int i = 2;

extern void f();
void g() {
	f();
	printf("%d\n", i);
}

void main() {
	// variabile automatice
	//int a = 8;
	//auto b = 9;

	//int c = a + b;

	//printf("Suma = %d\n", c);

	// variabile register

	//register int vreg;
	//int d;

	//d = 8;
	//vreg = d;

	//printf("Suma = %d\n", vreg);

	//__asm
	//{
	//	mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
	//};

	// variabile statice

	//int j;
	//for (j = 0; j < 10; j++) {
	//	printf("Rezultat functie f: %d\n", f());
	//	// x++; // identificator ne-declarat; x vizibil doar in functia f()
	//}

	// variabile externe - exemplul 1

	//i = 3;

	//f();
	//printf("%d\n", i);

	// exemplul 2

	i = 5;
	g();
}