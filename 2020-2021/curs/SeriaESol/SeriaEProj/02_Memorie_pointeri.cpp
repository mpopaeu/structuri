#include <stdio.h>
#include <string.h>

void main() {
	int i = 7;
	int *pi;
	int *ap[10];

	//////////////////
	pi = &i; // adresa de stack seg i este scrisa in pi
	printf("\nAdresa(pi) = %p, Adresa(i) = %p, Continut(pi) = %p, Continut(i) = %d\n", &pi, &i, pi, i);

	//////////////////
	for (int j = 0; j < 10; j++) {
		ap[j] = &i;
	}
	printf("\nAdresa(ap) = %p, Adresa(i) = %p\n", &ap, &i);
	for (int j = 0; j < 10; j++) {
		printf("\nContinut(ap[%d]) = %p\n", j, ap[j]);
	}

	//////////////////
	ap[1] = ap[0] + 1; // aritmetica de pointeri aplicata pentru int (&i + 1)
	printf("\nContinut(ap[0]) = %p\n", ap[0]);
	printf("\nContinut(ap[1]) = %p, Valoare(ap[1]) = %d\n", ap[1], *ap[1]);

	//////////////////
	char str[] = "Aplicatie in C/C++";
	char *ppc;
	ppc = str;
	printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);
	str[strlen(str)] = 0x65; // rescriere terminator de sir de caractere
	printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);

	// pointer constant la int
	int j = 9;
	int * const pci = &i;
	printf("\nAdresa(pci) = %p, Continut(pci) = %p\n", &pci, pci);
	// pci = &j; // erorare de compilare; pointerul este constant (nu poate fi rescris cu alta adresa)

	// pointer la int constant
	int const *pint;
	pint = &i;
	printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	// *pint = i + 5; // eroare de compilare; continutul destinatie nu poate fi modificat
	printf("\nContinut(i) = %d\n", i);

	// pointer constant la int constant
	const int * const pint2 = &i; 	// obligatoriu initializare la definire pint2
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	// *pint2 = i + 5; // eroare de compilare; continutul destinatie nu poate fi modificat
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
}