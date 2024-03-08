#include <stdio.h>
#include <malloc.h>

double sumaValoare(float x, float y) {
	double s;
	x += 1;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double* z) {
	x += 1;
	*z = x + y;
}

char sumaValoarePointer(float x, float y, double* z) {
	z = (double*)malloc(sizeof(double));
	x += 1;
	*z = x + y;

	return 1;
}

char sumaAdresaPointer(float x, float y, double* *z) {
	*z = (double*)malloc(sizeof(double));
	x += 1;
	**z = x + y;

	return 1;
}

void main() {
	float a = 1.2, b = 4.7;
	double c;
	double* pc = &c;

	c = sumaValoare(a, b);
	printf("\na = %f, b = %f, c = %lf\n", a, b, c);

	sumaAdresa(a, b, pc);
	printf("\na = %f, b = %f, c = %lf\n", a, b, c);

	c = 0;
	printf("\na = %f, b = %f, pc = 0x%p, *pc = %lf\n", a, b, pc, *pc);
	sumaValoarePointer(a, b, pc);
	printf("\na = %f, b = %f, pc = 0x%p, *pc = %lf\n", a, b, pc, *pc);
	sumaAdresaPointer(a, b, &pc);
	printf("\na = %f, b = %f, pc = 0x%p, *pc = %lf\n", a, b, pc, *pc);

	free(pc);
}