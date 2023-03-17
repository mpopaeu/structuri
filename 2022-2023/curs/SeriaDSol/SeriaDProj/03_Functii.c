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

void sumaAdresaPointer(float x, float y, double* *z) {
	*z = (double*)malloc(sizeof(double));
	**z = x + y;
}

double sumaPointerFunctie(float x, float y, double (*pf)(float, float)) {
	x = x + 1;
	y = y + 2.2;

	double suma = pf(x, y);
	return suma;
}

int main() {
	float a = 1.2, b = 4.7;
	double c;

	c = sumaValoare(a, b);
	printf("\nSuma apel functie parametri transfer prin valoare: %lf\n", c);

	sumaAdresa(a, b, &c);
	printf("\nSuma apel functie parametri transfer prin valoare si adresa: %lf\n", c);

	double* pc = NULL;
	//if (pc == NULL) return 1;
	//sumaAdresa(a, b, pc); // z va contine NULL; eroare de runtime

	pc = &c;
	a += 1;
	b += 2;
	sumaAdresa(a, b, pc); // z va contine &c; c va fi modificat prin pointer pc
	printf("\nSuma apel functie parametri transfer prin valoare, inclusiv pointer pc: %lf\n", c);

	pc = NULL;
	a += 1;
	b += 2;
	sumaAdresaPointer(a, b, &pc); // *pc va contine rezultat in memorie heap
	printf("\nSuma apel functie parametri transfer prin valoare si adresa pointer pc: %lf\n", *pc);

	free(pc);


	// definire si utilizare pointer la functie
	double (*pSumaVal)(float, float);
	pSumaVal = sumaValoare;
	c = pSumaVal((float)(a + 1), (float)(b + 2.2));
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	pSumaVal = &sumaValoare;
	c = pSumaVal(a + 1, b + 2.2);
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	c = sumaPointerFunctie(a, b, pSumaVal);
	printf("\nSuma apel functie cu parametru pointer la functie: %lf\n", c);

	return 0;
}