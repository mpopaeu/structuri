#include <stdio.h>
#include <malloc.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double* z) {
	*z = x + y;
}

char allocValoare(float* px, char size) {
	px = (float*)malloc(size);
	if (px)
		return 1;
	return 0;
}

char allocAdresa(float* *px, char size) {
	*px = (float*)malloc(size);
	if (*px)
		return 1;
	return 0;
}


void main() {
	float a = 1.2, b = 4.7;
	double c;

	c = sumaValoare(a, b);
	printf("\nSuma apel functie parametri transfer prin valoare: %lf\n", c);

	sumaAdresa(a, b, &c);
	printf("\nSuma apel functie parametri transfer prin valoare si adresa: %lf\n", c);

	float* px = NULL;
	char rez = allocValoare(px, 10);
	printf("px = %p\n", px);
	rez = allocAdresa(&px, 10);
	printf("px = %p\n", px);
}