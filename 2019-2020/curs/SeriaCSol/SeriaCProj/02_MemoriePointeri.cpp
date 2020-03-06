#include <stdio.h>
#include <malloc.h>

void main() {
	//int i = 7;
	//int *pi;
	//int *ap[10];

	////////////////////
	//pi = &i;
	//printf("\nAdr(pi) = %p, Adresa(i) = %p, Cont(pi) = %p, Cont(i) = %d\n", &pi, &i, pi, i);

	////////////////////
	//for (int j = 0; j < 10; j++) {
	//	ap[j] = &i;
	//}
	//printf("\nAdr(ap) = %p, Adr(i) = %p\n", &ap, &i);
	//for (int j = 0; j < 10; j++) {
	//	printf("\nCont(ap[%d]) = %p\n", j + 1, ap[j]);
	//}

	////////////////////
	//ap[1] = ap[0] + 1;
	//printf("\nCont(ap[1]) = %p\n", ap[0]);
	//printf("\nCont(ap[2]) = %p\n", ap[1]);

	////////////////////
	//char str[] = "Aplicatie in C/C++";
	//char *ppc;
	//ppc = str;
	//printf("\nAdr(ppc) = %p, Adr(str) = %p, Cont(ppc) = %p, Cont(str) = %s\n", &ppc, str, ppc, str);

	//// pointer constant la int
	//int i = 7, j = 9;
	//int * const pi; // = &i;
	//printf("\nAdr(pi) = %p, Cont(pi) = %p\n", &pi, pi);
	//// pi = &j;

	//// pointer la int constant
	//int const *pint;
	//pint = &i;
	//printf("\nAdr(pint) = %p, Cont(pint) = %p\n", &pint, pint);
	//// *pint = i + 5;
	//pint = &j;
	//printf("\nCont(i) = %d\n", i);

	//// pointer constant la int constant
	//const int * const pint2 = &i; 	
	//printf("\nAdr(pint2) = %p, Cont(pint2) = %p\n", &pint2, pint2);
	//// *pint2 = i + 5;
	//printf("\nAdr(pint2) = %p, Cont(pint2) = %p\n", &pint2, pint2);

	int ** pMat;
	int m = 2; // numar de linii
	int n = 3; // numar de coloane

	pMat = (int**)malloc(m * sizeof(int*)); // alocare spatiu pentru m pointeri de linii

	for (int i = 0; i<m; i++) {
		pMat[i] = (int*)malloc(n * sizeof(int)); // alocare spatiu pentru n elemente pe linie		
	}

	printf("\nCont(pMat) = %p\n", pMat);
	for (int i = 0; i<m; i++)
		printf("Cont(pMat[%d]) = %p  ", i + 1, pMat[i]); // afisare adrese de inceput ale liniilor


	for (int i = 0; i<m; i++) {
		for (int j = 0; j<n; j++) {
			pMat[i][j] = i * 10 + j; // initializare valoare element matrice
		}
	}

	for (int i = 0; i<m; i++) {
		printf("\n\n");
		for (int j = 0; j<n; j++) {
			//printf("Adr(pMat[%d][%d]) = %p  ", i+1, j+1, &pMat[i][j]); // afisare adrese de inceput ale liniilor
			printf("Adr(pMat[%d][%d]) = %p  ", i + 1, j + 1, *(pMat + i) + j); // afisare adrese de inceput ale liniilor
		}
	}

	// operatii matrice
	int suma = 0;
	for (int i = 0; i<m; i++) {
		for (int j = 0; j<n; j++) {
			suma = suma + pMat[i][j];
		}
	}
	printf("\nSuma este = %d \n", suma);
}