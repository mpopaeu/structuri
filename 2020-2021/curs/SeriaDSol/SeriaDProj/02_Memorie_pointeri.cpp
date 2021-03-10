#include <stdio.h>
#include <string.h>

void main() {
	int i = 7;
	int *pi;
	int *ap[10]; // vector de pointeri la int

	//////////////////
	pi = &i;
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
	ap[1] = ap[0] + 1; // ap[1] cu 1 * sizeof(int) bytes mai mare
	printf("\nContinut(ap[0]) = %p\n", ap[0]);
	printf("\nContinut(ap[1]) = %p, Valoare(ap[1]) = %d\n", ap[1], *ap[1]); // *ap[1] continut arbitrar convertit la int conform %d

	//////////////////
	char str[] = "Aplicatie in C/C++"; // byte-ul 0 pus implicit ca terminator de sir de caractere; rol de flag pentru functiile
										// care prelucreaza siruri de caractere
	char *ppc;
	ppc = str;
	printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);
	// strcpy(str + strlen(str) - 3, "Stack"); // depasire zona de memorie alocata variabile str
	str[strlen(str)] = 'A'; // rescrierea terminatoruluide sir de caractere
	printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);

	// pointer constant la int
	int j = 9;
	int * const pci = &i; // obligatoriu, initializarea pci la momentul declararii
	printf("\nAdresa(pi) = %p, Continut(pi) = %p\n", &pci, pci);
	// pci = &j;

	// pointer la int constant
	int const *pint;
	pint = &i;
	printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	// *pint = i + 5;
	printf("\nContinut(i) = %d\n", i);

	// pointer constant la int constant
	const int * const pint2 = &i; 	
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	// *pint2 = i + 5;
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);

}
