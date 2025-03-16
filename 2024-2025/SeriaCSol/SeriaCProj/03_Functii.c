#include <stdio.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double* z) {
	*z = sumaValoare(x, y);
}

double sumaPointerFunctie(float x, float y, double (*pf)(float, float)) {
	x = x + 1;
	y = y + (float)2.2;

	double suma = pf(x, y);
	return suma;
}


int main()
{
	float a = (float)1.2, b = 4.7f;
	double c;

	sumaAdresa(a, b, &c);
	printf("\nSuma apel functie parametri transfer prin valoare si adresa: %lf\n", c);

	// exemplu utilizare pointer la functie
	double (*pSumaVal)(float, float);
	pSumaVal = sumaValoare;
	c = sumaPointerFunctie(a, b, pSumaVal);
	printf("\nSuma apel functie cu parametru pointer la functie: %lf\n", c);


	return 0;
}