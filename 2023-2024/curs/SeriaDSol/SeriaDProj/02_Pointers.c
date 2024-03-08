#include <stdio.h>
#include <string.h>

int main()
{
	//// pointer constant la int
	//int i = 7, j = 9;
	//int* const pi = &i;
	//printf("\nAdresa(pi) = %p, Continut(pi) = %p\n", &pi, pi);
	////pi = &j;


	//// Pointer la int constant
	//int const* pint, i = 7;
	//pint = &i;
	//printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	////*pint = i + 5;
	//printf("\nContinut(i) = %d\n", i);

	// Pointer constant la int constant
	int i = 7;
	const int* const pint2 = &i; 	
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	// *pint2 = i + 5;
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);


	return 0;
}