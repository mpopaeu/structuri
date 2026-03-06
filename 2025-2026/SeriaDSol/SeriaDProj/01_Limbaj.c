#include <stdio.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

int main()
{
	int i = 7;
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

	char* p_int = (char*)&i; // adresa de variabila i este stocata in p_int
	for (unsigned char i = 0; i < sizeof(int); i++)
	{
		printf("Adresa element %d din grupul de int al variabilei i = 0x%p\n", i + 1, p_int + i);
		printf("Valoare element %d din grupul de int al variabilei i = %d\n", i + 1, *(p_int + i)); // *(p_int + i) == p_int[i]
	}


	// POINTERI LA FUNCTII
	// definire si utilizare pointer la functie
	double (*pSumaVal)(float, float);
	pSumaVal = sumaValoare;
	double c = pSumaVal((float)(i + 1), (float)(i + 2.2));
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	pSumaVal = &sumaValoare;
	c = pSumaVal(i + 1, i + 2.2);
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);


	return 0;
}