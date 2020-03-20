#include <stdio.h>
#include <stdarg.h>


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


void main() {
	float a = 1.2f, b = 4.7f;
	double c;

	// utilizare functie numar variabil de argumente
	c = sumaArgumenteVariabile(2, a, b);
	printf("\nSuma apel functie cu numar variabil de argumente: %lf\n", c);
	c = sumaArgumenteVariabile(4, a, b, a + 1, b + 2.2);
	printf("\nSuma apel functie cu numar variabil de argumente v.2: %lf\n", c);
}