#include <stdio.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

double sumaPointerFunctie(float x, float y, double(*pf)(float, float)) {
	x = x + 1;
	y = y + 2.2;

	double suma = pf(x, y);
	return suma;
}

int main()
{
	float a = 1.2f, b = 4.7f;
	double c;

	// definire si utilizare pointer la functie
	double(*pSumaVal)(float, float); // variabila locala lui main()
	pSumaVal = sumaValoare; // "incarcare" adresa functie sumaValoare (seg de cod) in var pointer
	c = pSumaVal((float)(a + 1), (float)(b + 2.2)); // apel indirect al functiei sumaValoare
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	pSumaVal = &sumaValoare; // "incarcare" adresa functie sumaValoare (seg de cod) in var pointer
	c = pSumaVal(a + 1, b + 2.2); // apel indirect al functiei sumaValoare
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	c = sumaPointerFunctie(a, b, pSumaVal);
	printf("\nSuma apel functie cu parametru pointer la functie: %lf\n", c);

	return 0;
}