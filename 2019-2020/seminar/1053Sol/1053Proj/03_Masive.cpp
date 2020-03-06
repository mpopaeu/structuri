

#include <stdio.h>
#include <malloc.h>

void main() {
	int a, va[10], *pa;
	int m[10][20], **pm;

	// alocare matrice in heap
	pm = (int**)malloc(10 * sizeof(int*));
	for (int i = 0; i < 10; i++)
		pm[i] = (int*)malloc(20 * sizeof(int)); // pointer la int*

	// matrice in heap de string-uri (matrice zig-zag)
	// creare, afisare, dezalocare

	// dezalocare matrice (de int) in heap
}