#include <stdio.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double* z) {
	*z = x + y;
}


void main() {
	int i = 3456;
	int* pi;
	int* ap[10];

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
	ap[1] = ap[0] + 1;
	printf("\nContinut(ap[0]) = %p\n", ap[0]);
	printf("\nContinut(ap[1]) = %p\n", ap[1]);

	//////////////////
	char str[] = "Aplicatie in C/C++";
	char* ppc;
	ppc = str;
	printf("\nAdresa(ppc) = %p, Adresa(str) = %p, Continut(ppc) = %p, Continut(str) = %s\n", &ppc, str, ppc, str);

	unsigned char* p_int = (unsigned char*)&i;
	printf("Traversare locatie (nivel fizic) i byte cu byte la nivel fizic: ");
	for (unsigned char j = 0; j < sizeof(int); j++)
	{
		printf("%02X ", p_int[j]);
	}
	printf("\n\n");

	printf("Traversare locatie (nivel logic) i byte cu byte la nivel fizic: ");
	for (char j = (sizeof(int) - 1); j >= 0 ; j--)
	{
		printf("%02X ", p_int[j]);
	}
	printf("\n\n");

	// definire si utilizare pointer la functie
	double (*pSumaVal)(float, float);
	pSumaVal = sumaValoare;
	double c = pSumaVal((float)(i + 1), (float)(i + 2.2));
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	pSumaVal = &sumaValoare;
	c = pSumaVal(i + 1, i + 2.2);
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	printf("\nAdresa(pSumaVal) = %p, Continut(pSumaVal) = %p\n", &pSumaVal, pSumaVal);

}
