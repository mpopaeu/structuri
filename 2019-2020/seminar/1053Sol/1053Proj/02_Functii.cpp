
#include <stdio.h>
#include <malloc.h>

int calcul_1(int x, int y) {
	x += 1;
	int z = x + y;

	return z;
}

void calcul_2(int x, int y) {
	x += 1;
	int z = x + y;
}

void calcul_3(int x, int y, int z) {
	x += 1;
	z = x + y;
}

void calcul_4(int* x, int y, int* z) {
	*x += 1;
	*z = *x + y;
}

void calcul_5(int* x, int y, int* z) {
	*x += 1;
	z = (int*)malloc(sizeof(int) * 1); // alocare mem heap pentru 1 elem de tip int
	*z = *x + y;
}

void calcul_6(int* x, int y, int* *z) {
	*x += 1;
	*z = (int*)malloc(sizeof(int) * 1); // alocare mem heap pentru 1 elem de tip int
	(*z)[0] = *x + y;
}

int* calcul_7(int* x, int y) {
	*x += 1;
	int *z;
	z = (int*)malloc(sizeof(int) * 1); // alocare mem heap pentru 1 elem de tip int
	*z = *x + y;

	return z; // return adresa de heap in apelator; apelatorul decide ce face cu adresa intoarsa
}

void calcul_8(int* x, int y, int* &z) {
	*x += 1;
	z = (int*)malloc(sizeof(int) * 1); // alocare mem heap pentru 1 elem de tip int
	*z = *x + y;
}


void main() {
	int a, b, c;
	a = 9;
	b = 0x02;

	c = calcul_1(a, b); // transfer prin valoare
	calcul_2(a, b); // transfer prin valoare
	calcul_3(a, b, c); // transfer prin valoare
	calcul_4(&a, b, &c); // transfer prin valaore b; transfer prin adresa a, c

	int *pa, *pc;
	a = 9;
	c = 0;
	pa = &a;
	pc = &c;
	calcul_4(pa, b, pc);
	printf("a = %d, b = %d, c = %d\n", a, b, c);

	a = 9;
	c = 0;
	calcul_5(pa, b, pc); // genereaza memory leak deoarece adresa alocata nu poate fi accesata din main()
	printf("a = %d, b = %d, *pc = %d\n", a, b, *pc);

	a = 9;
	c = 0;
	printf("pc = %X\n", pc);
	calcul_6(pa, b, &pc); // transfer prin valoare pa si b; transfer prin adresa pc
	printf("pc = %X\n", pc);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);

	free(pc);

	a = 9;
	c = 0;
	pc = calcul_7(pa, b);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);

	free(pc);

	a = 9;
	c = 0;
	calcul_8(pa, b, pc);
	printf("a = %d, b = %d, c = %d, *pc = %d\n", a, b, c, *pc);

	free(pc);
}