#include <stdio.h>
#include <malloc.h>

int main()
{
	//// pointer constant la int
	//int i = 7, j = 9;
	//int* const pi = &i;
	//printf("\nAdresa(pi) = %p, Continut(pi) = %p\n", &pi, pi);
	////pi = &j; // rescrierea zonei de memorie pi nu este posibila, fiind pointer constant

	int i = 7;
	//int const* pint;
	//pint = &i;
	//printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	////*pint = i + 5;
	//i += 5;
	//printf("\nContinut(i) = %d\n", i);


	//const int* const pint2 = &i; 	
	//printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	//// *pint2 = i + 5;
	//printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	//i += 5;
	//printf("\nContinut(i) = %d\n", i);
	//printf("\nContinut(*pint2) = %d\n", *pint2);

	int* pint3 = NULL;

	// alocare memorie la runtime
	pint3 = (int*)malloc((unsigned int)i); // dimensiune zona de heap in nr de bytes

	pint3[0] = 1; // este ok!
	pint3[1] = 2; // NU este ok!

	// dezalocare memorie heap
	free(pint3);

	return 0;
}