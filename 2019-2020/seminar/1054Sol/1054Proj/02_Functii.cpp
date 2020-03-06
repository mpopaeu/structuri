
#include <stdio.h>
#include <malloc.h>

int suma_v1(int x, int y) {
	x += 1;
	int z = x + y;

	return z;
}

void suma_v2(int x, int y) {
	x += 1;
	int z = x + y;
}

void suma_v3(int x, int y, int z) {
	x += 1;
	z = x + y;
}

void suma_v4(int* x, int y, int* z) {
	*x += 1;
	*z = *x + y;
}

void suma_v5(int* x, int y, int* z) {
	*x += 1;

	z = (int*)malloc(sizeof(int) * 1); // alocare locatie int in heap seg

	*z = *x + y;
}

void suma_v6(int* x, int y, int* *z) {
	*x += 1;

	*z = (int*)malloc(sizeof(int) * 1); // alocare locatie int in heap seg

	(*z)[0] = *x + y;
}

int* suma_v7(int* x, int y) {
	*x += 1;
	int *z;

	z = (int*)malloc(sizeof(int) * 1); // alocare locatie int in heap seg
	*z = *x + y;

	return z;
}

void suma_v8(int* x, int y, int& z) {
	*x += 1;	
	z = *x + y;
}

void main() {
	int a, b, c;
	int *pa, *pc;

	a = 5;
	b = 7;

	c = suma_v1(a, b); // transfer prin valoare
	suma_v2(a, b); // transfer prin valoare
	suma_v3(a, b, c); // transfer prin valoare
	suma_v4(&a, b, &c); // transfer prin adresa a args a si c
	printf("a = %d, b = %d, c = %d \n", a, b, c);

	a = 5;
	pa = &a;
	pc = &c;
	suma_v4(pa, b, pc);
	printf("*pa = %d, b = %d, *pc = %d \n", *pa, b, *pc);
	
	a = 5;
	c = 0;
	suma_v5(pa, b, pc); // transfer prin valoare a tuturor args
	printf("*pa = %d, b = %d, *pc = %d \n", *pa, b, *pc);

	a = 5;
	c = 0;
	printf("Cont(pc) = %X\n", pc);
	suma_v6(pa, b, &pc); // transfer prin valoare pa si b; transfer prin adresa arg pc

	printf("*pa = %d, b = %d, *pc = %d \n", *pa, b, *pc);
	printf("Cont(pc) = %X\n", pc);

	free(pc);
	pc = 0; // pc = NULL;

	a = 5;
	c = 0; 
	printf("Cont(pc) = %X\n", pc);
	pc =suma_v7(pa, b); // adresa heap intoarsa prin tip de return
	printf("*pa = %d, b = %d, *pc = %d \n", *pa, b, *pc);
	printf("Cont(pc) = %X\n", pc);

	free(pc);

	a = 5;
	c = 0;
	suma_v8(&a, b, c); // transfer arg c cu referinta &; c modificat in functie si vizil in afara functiei
	printf("*pa = %d, b = %d, c = %d \n", *pa, b, c);
}