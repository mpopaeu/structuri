
#include <stdio.h>
#include <malloc.h>

int calcul_v1(int x, int y) {
	x += 2;
	int z = x + y;

	return z;
}

void calcul_v2(int x, int y) {
	x += 2;
	int z = x + y;
}

void calcul_v3(int x, int y, int z) {
	x += 2;
	z = x + y;
}

void calcul_v4(int *x, int y, int *z) {
	*x += 2;
	*z = *x + y;
}

void calcul_v5(int *x, int y, int *z) {
	*x += 2;
	z = (int*)malloc(sizeof(int) * 1);
	*z = *x + y;
}

void calcul_v6(int *x, int y, int **z) {
	*x += 2;
	*z = (int*)malloc(sizeof(int) * 1);
	(*z)[0] = *x + y; // ** z = *x + y;
}

int* calcul_v7(int *x, int y) {
	*x += 2;
	int *z;
	z = (int*)malloc(sizeof(int) * 1);
	*z = *x + y; 

	return z;
}

void calcul_v8(int *x, int y, int * &z) {
	*x += 2;
	z = (int*)malloc(sizeof(int) * 1);
	*z = *x + y;
}

int* calcul_v9(int &x, int y) {
	x += 2;
	int *z;
	z = (int*)malloc(sizeof(int) * 1);
	*z = x + y;

	return z;
}

void main() {
	int a, b, c;
	a = 7;
	b = 4;

	c = calcul_v1(a, b); // transfer prin valoare
	calcul_v2(a, b);	 // transfer prin valoare
	calcul_v3(a, b, c);	 // transfer prin valoare

	c = 0;
	calcul_v4(&a, b, &c); // transfer prin adresa pentru a si c; transfer prin valoare pentru b
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	int *pa, *pc;
	pa = &a;
	pc = &c;

	a = 7;
	c = 0;
	calcul_v4(pa, b, pc);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	a = 7;
	c = 0;
	calcul_v5(pa, b, pc);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);

	a = 7;
	c = 0;
	printf("pc = %X\n", pc);
	calcul_v6(pa, b, &pc);
	printf("pc = %X\n", pc);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);

	free(pc);

	a = 7;
	c = 0;
	pc = calcul_v7(pa, b);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);
	free(pc);

	a = 7;
	c = 0;
	calcul_v8(pa, b, pc);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);
	free(pc);

	a = 7;
	c = 0;
	pc = calcul_v9(a, b);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);
	free(pc);
}