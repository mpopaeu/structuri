#include <stdio.h>
#include <malloc.h>

double sumaValoare(float x, float y) {
	double s;
	s = x + y;
	return s;
}

void sumaAdresa(float x, float y, double* z) {
	*z = sumaValoare(x, y);
}

void sumaAdresaHeap(float x, float y, double* z)
{
	z = (double*)malloc(sizeof(double));
	*z = x + y;
}

void sumaAdresaHeap_v2(float x, float y, double* *z)
{
	*z = (double*)malloc(sizeof(double));
	**z = x + y;
}


double* sumaAdresaHeap_v3(float x, float y)
{
	double* z = NULL;
	z = (double*)malloc(sizeof(double));
	*z = x + y;

	return z;
}

int main() {
	float a = 1.2f, b = 4.7f;
	double c;

	sumaAdresa(a, b, &c);
	printf("\nSuma apel functie parametri transfer prin valoare si adresa: %lf = %f + %f\n", c, a, b);

	double* p_suma = NULL;
	//sumaAdresaHeap(a, b, p_suma);
	sumaAdresaHeap_v2(a, b, &p_suma);
	printf("\nSuma apel functie parametri transfer prin valoare si POINTER prin adresa: %lf = %f + %f\n", *p_suma, a, b);

	p_suma = sumaAdresaHeap_v3(a, b);
	printf("\nSuma apel functie parametri transfer prin valoare si POINTER obtinut prin return din functie: %lf = %f + %f\n", *p_suma, a, b);

	free(p_suma);


	// definire si utilizare pointer la functie
	double (*pSumaVal)(float, float);
	pSumaVal = sumaValoare; // scriere adresa functie (din seg de cod) in pSumaVal
	c = pSumaVal((float)(a + 1), (float)(b + 2.2)); // apel functie sumaValoare prin pointer pSumaVal
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	pSumaVal = &sumaValoare;
	c = pSumaVal(a + 1, b + 2.2);
	printf("\nSuma apel functie prin pointer la functie: %lf\n", c);

	return 0;
}
