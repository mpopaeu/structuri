#include <stdio.h>


double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double *z) {
	*z = x + y;
}

double sumaPointerFunctie(float x, float y, double(*pf)(float, float)) {
	x = x + 1;
	y = y + 2.2;

	double suma = pf(x, y);
	return suma;
}

void main() {
	float a = 1.2f, b = 4.7f;
	double c;

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
}