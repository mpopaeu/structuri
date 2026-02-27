#include <stdio.h>
#include <malloc.h>

int main()
{
	char a = 15;
	char b = -15;

	printf("a = %d\n", a);
	printf("b = %d\n", b);

	printf("adresa(a) = 0x%p\n", &a);
	printf("adresa(b) = 0x%p\n", &b);

	char* p = NULL;
	//*p = 7; // eroare de run-time pentru ca NULL este adresa invalida
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);

	p = &a;
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);

	// &a = &b; // nu este posibil; adresele de stack seg nu pot fi modificate (adrese constante)

	*p = a - 20;
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p); 
	printf("a = %d sau a = 0x%02X\n", a, (unsigned char)a);

	char v[] = {5, 8, 7, 4, 3, 2, 1, 0};
	printf("Dimensiune v = %d bytes\n", sizeof(v));

	p = v;
	printf("Dimensiune p = %d bytes\n", sizeof(p));
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);

	// alocare mem heap pentru vector p
	p = malloc(sizeof(v));
	printf("Dimensiune p = %d bytes\n", sizeof(p));
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);

	for (unsigned char i = 0; i < sizeof(v) - 1; i++)
		p[i] = 'a' + i;
	p[sizeof(v) - 1] = 0;

	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d->%c ", p[i], p[i]);
	printf("\n\n");

	printf(" %s \n\n", p);

	char m[][3] = { {1, 2, 3}, {4, 4, 4} };


	// alocare matrice in heap
	char** pm = malloc(2 * sizeof(char*)); // alocare structura intermediara pentru adrese inceput linii
	for (unsigned char i = 0; i < 2; i++)
		// alocare mem heap pentru linia i din matrice
		// +1 pentru a face loc terminatorului de string (byte 0x00)
		pm[i] = malloc((3 + 1) * sizeof(char)); 

	for (unsigned char i = 0; i < 2; i++) {
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = 'a' + m[i][j];
		pm[i][3] = 0; // scriere byte nul / terminator string pe ultima pozitie de pe linia i
	}

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 4; j++) // afisare inclusiv terminator de string
			printf(" %d->%c ", pm[i][j], pm[i][j]);
		printf("\n");
	}
	printf("\n\n");

	for (unsigned char i = 0; i < 2; i++)
		printf("%s\n", pm[i]);
	printf("\n\n");

	// dezalocare vector p
	free(p);
	//p = NULL;
	//printf("Continut mem heap dupa dezalocare pointer p:\n");
	//for (unsigned char i = 0; i < sizeof(v); i++)
	//	printf(" %d->%c ", p[i], p[i]);
	//printf("\n\n");

	//printf(" %s \n\n", p);

	//dezalocare matrice in heap
	for (unsigned char i = 0; i < 2; i++)
		free(pm[i]); // dezalocare linie i
	free(pm); // dezalocare structura intermediara cu adresele de inceput de linii

	return 0;
}