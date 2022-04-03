//#include <stdarg.h>
//#include <stdio.h>
//
//double sumaArgumenteVariabile(int nr, ...)
//{
//	va_list ap; // va_list: tip definit in stdarg.h cu 4 macrodef: va_start, va_arg, va_copy, va_end
//	int i;
//	double suma = 0;
//
//	va_start(ap, nr);	// initializeaza ap pentru utilzare
//	for (i = 0; i < nr; i++) {
//		suma += va_arg(ap, double);		// considerarea urmatorului argument de tipul double 
//	}
//	va_end(ap);		// clean-up pentru ap; poate pregati o noua parsare a argumentelor cu invocare ulterioara va_start
//
//	return suma;
//}
//
//
//int main() {
//	double a = 1.2, b = 4.7;
//	double c;
//
//	// utilizare functie numar variabil de argumente
//	c = sumaArgumenteVariabile(2, a, b);
//	printf("\nSuma apel functie cu numar variabil de argumente: %lf\n", c);
//	c = sumaArgumenteVariabile(4, a, b, a + 1, b + 2.2);
//	printf("\nSuma apel functie cu numar variabil de argumente v.2: %lf\n", c);
//
//	return 0;
//}

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void main(int argc, char* argv[]) {

	printf("\nNumarul de argumente al functiei main este: %d\n", argc);
	for (int i = 0; i < argc; i++)
		printf("\nArgumentul %d este: %s\n", i + 1, argv[i]);

	// Utilizare argumente pentru determinare suma 
	int* pArgs;
	// Alocare spatiu vector de valori (primul argument este numele fisierului exe)
	pArgs = (int*)malloc((argc - 1) * sizeof(int));

	// conversie argumente functie main din char* in int (ASCII-to-binary)
	for (int i = 0; i < argc - 1; i++)
		pArgs[i] = atoi(argv[i + 1]);

	int suma = 0;
	for (int i = 0; i < argc - 1; i++)
		suma += pArgs[i];

	printf("\nSuma este: %d\n", suma);

	free(pArgs);

}
