double sumaValoriDefault(float x = 1.1, float y = 2.21) {
	double s;
	s = x + y;
	return s;
}

void main() {
	float a = 1.2f, b = 4.7f;
	double c;

	// utilizare functie cu parametri default
	c = sumaValoriDefault(a, b);
	printf("\nSuma apel functie cu parametri: %lf\n", c);
	c = sumaValoriDefault();
	printf("\nSuma apel functie cu parametri default: %lf\n", c);
	c = sumaValoriDefault(a);
	printf("\nSuma apel functie cu primul parametru default: %lf\n", c);
	c = sumaValoriDefault();
	printf("\nSuma apel functie cu primul parametru default: %lf\n", c);
}