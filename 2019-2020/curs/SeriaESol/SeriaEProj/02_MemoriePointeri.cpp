#include <stdio.h>


void main() {
	int i = 7;
	int *pi;
	int *ap[10];

	//////////////////
	pi = &i;
	printf("\nAdr(pi) = %p, Adresa(i) = %p, Cont(pi) = %p, Cont(i) = %d\n", &pi, &i, pi, i);

	//////////////////
	for (int j = 0; j < 10; j++) {
		ap[j] = &i;
	}
	printf("\nAdr(ap) = %p, Adr(i) = %p\n", &ap, &i);
	for (int j = 0; j < 10; j++) {
		printf("\nCont(ap[%d]) = %p\n", j + 1, ap[j]);
	}

	//////////////////
	ap[1] = ap[0] + 1;
	printf("\nCont(ap[1]) = %p\n", ap[0]);
	printf("\nCont(ap[2]) = %p\n", ap[1]);

	//////////////////
	char str[] = "Aplicatie in C/C++";
	char *ppc;
	ppc = str;
	printf("\nAdr(ppc) = %p, Adr(str) = %p, Cont(ppc) = %p, Cont(str) = %s\n", &ppc, str, ppc, str);

	// pointer constant la int
	int i2 = 7, j = 9;
	int * const pi2 = &i2;
	printf("\nAdr(pi2) = %p, Cont(pi2) = %p\n", &pi2, pi2);
	// pi2 = &j;

	int const *pint;
	pint = &i;
	printf("\nAdr(pint) = %p, Cont(pint) = %p\n", &pint, pint);
	// *pint = i + 5;
	printf("\nCont(i) = %d\n", i);

	const int * const pint2 = &i; 	
	printf("\nAdr(pint2) = %p, Cont(pint2) = %p\n", &pint2, pint2);
	//pint2 = &j;
	//*pint2 = i + 5;
	printf("\nAdr(pint2) = %p, Cont(pint2) = %p\n", &pint2, pint2);
}