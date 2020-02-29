#include <stdio.h>

// variabile statice
//int f() {
//	static int x = 0;
//	x++;
//	return x;
//}

// variabile externe
// #include "headers.h" // comentat pt exemplul 2

int i;

extern void f(); // declaratie obligatorie pt exemplul 2
void g() {
	f();
	printf("%d\n", i);
}

void main() {
	// variabile automatic
	//int a = 8;
	//auto b = 9;

	//int c = a + b;

	//printf("Suma = %d\n", c);

	// varianile register
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
	//}

	//// x += 19; // eroare de compilare

	// variabile externe -> exemplul 1

	//i = 3;

	//f();
	//printf("%d\n", i);

	// variabile externe -> exemplul 2

	i = 5;
	g();
}