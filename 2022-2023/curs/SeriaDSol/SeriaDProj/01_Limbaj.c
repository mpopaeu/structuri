#include <stdio.h>

// variabile auto
//int main()
//{
//	int a = 8;
//	auto b = 9;
//
//	int c = a + b;
//
//	printf("Suma = %d\n", c);
//}

// variabile register
//int main()
//{
//	register int vreg;
//	int d;
//
//	d = 8;
//	vreg = d;
//
//	printf("vreg = %d,\" vreg = %02X\n", vreg, vreg);
//
//	__asm
//	{
//		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
//	};
//}

// variabile statice
//int f() {
//	static int x = 0;
//	x++;
//	return x;
//}
//
//void main() {
//	int j;
//	int x = 11;
//	for (j = 0; j < 10; j++) {
//		printf("Rezultat functie f: %d\n", f());
//	}
//}

// variabila clasa extern - ex.1 
//#include "headers.h"
//
//int i;
//
//void main() {
//	i = 3;
//
//	f();
//	printf("%d\n", i);
//}

// variabila clasa extern - ex.2

int i = 2;

extern void f();
void g() {
	f();
	printf("%d\n", i);
}


void main() {
	i = 5;
	g();
}