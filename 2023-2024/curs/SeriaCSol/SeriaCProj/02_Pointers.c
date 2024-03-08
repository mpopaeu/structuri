#include <stdio.h>

int main() {
	//int i = 7;
	//int* pi;
	//int* ap[10];

	////////////////////
	//pi = &i;
	//printf("\nAdresa(pi) = %p, Adresa(i) = %p, Continut(pi) = %p, Continut(i) = %d\n", &pi, &i, pi, i);

	////////////////////
	//for (int j = 0; j < 10; j++) {
	//	ap[j] = &i;
	//}
	//printf("\nAdresa(ap) = %p, Adresa(i) = %p\n", &ap, &i);
	//for (int j = 0; j < 10; j++) {
	//	printf("\nContinut(ap[%d]) = %p\n", j, ap[j]);
	//}

	////////////////////
	//ap[1] = ap[0] + 1;
	//printf("\nContinut(ap[0]) = %p, Valoare(ap[0]) = %d\n", ap[0], *ap[0]);
	//printf("\nContinut(ap[1]) = %p, Valoare(ap[1]) = %d\n", ap[1], *ap[1]);

	////////////////////
	//char str[] = "Aplicatie in C/C++";
	//char* ppc;
	//ppc = str;
	//printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);

	//// pointer constant la int
	//int i = 7, j = 9;
	//int* const pi = &i;
	//printf("\nAdresa(pi) = %p, Continut(pi) = %p\n", &pi, pi);
	////pi = &j;

	//// Pointer la int constant
	//int const* pint, i = 7;
	//pint = &i;
	//printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	//// *pint = i + 5;
	//printf("\nContinut(i) = %d\n", i);

	// Pointer constant la int constant

	int i = 8;
	const int* const pint2 = &i; 	
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	// *pint2 = i + 5;
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);

	return 0;
}