#include <stdio.h>
#include <stdarg.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

double sumaValoriDefault(float x = 1.1, float y = 2.21) {
	double s;
	s = x + y;
	return s;
}

double sumaArgumenteVariabile(int nr, ...)
{
	va_list ap; // va_list: tip definit in stdarg.h cu 4 macrodef: va_start, va_arg, va_copy, va_end
	int i;
	double suma = 0;

	va_start(ap, nr);	// initializeaza ap pentru utilzare
	for (i = 0; i < nr; i++) {
		suma += va_arg(ap, double);		// considerarea urmatorului argument de tipul double 
	}
	va_end(ap);		// clean-up pentru ap; poate pregati o noua parsare a argumentelor cu invocare ulterioara va_start

	return suma;
}

int main() {
	float a = 1.2f, b = 4.7f;
	double c;

	// utilizare functie cu parametri default
	c = sumaValoriDefault(a, b);
	printf("\nSuma apel functie cu parametri: %lf\n", c);
	c = sumaValoriDefault();
	printf("\nSuma apel functie cu parametri default: %lf\n", c);
	c = sumaValoriDefault(a); // valori default utilizate pt parametri de dupa lista de argumente la apel (dupa arg a)
	printf("\nSuma apel functie cu primul parametru default: %lf\n", c);
	c = sumaValoriDefault();
	printf("\nSuma apel functie cu primul parametru default: %lf\n", c);

	// utilizare functie numar variabil de argumente
	c = sumaArgumenteVariabile(2, a, b);
	printf("\nSuma apel functie cu numar variabil de argumente: %lf\n", c);
	c = sumaArgumenteVariabile(4, a, b, a + 1, b + 2.2);
	printf("\nSuma apel functie cu numar variabil de argumente v.2: %lf\n", c);

	return 0;
}