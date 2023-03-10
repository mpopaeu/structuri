
#include <stdio.h>

// variabile din clasa auto
//int main()
//{
//	int a = 8;
//	auto b = 9;
//
//	int c = a + b;
//
//	printf("Suma = %d\n", c);
//}

// variabile din clasa register
//int main()
//{
//	register int vreg;
//	int d;
//
//	d = 8;
//	vreg = d;
//
//	printf("vreg = %d\n", vreg);
//
//	__asm
//	{
//		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
//	};
//}

// utilizare variabila din clasa static
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

// variabile din clasa extern - exemplu 1
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


// variabile din clasa extern - exemplu 2
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

