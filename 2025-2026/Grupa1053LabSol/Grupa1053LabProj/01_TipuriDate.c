#include <stdio.h>
#include <malloc.h>


int main()
{
	char a = 13;  // reprezentare CD (intreg pozitiv)
	char b = -13; // char b = 0xf3; // echivalent reprezentare in hex-pair (CC2 - intreg negativ)

	printf("a = %d\n", a);
	printf("b = %d\n", b);

	printf("adresa(a) = 0x%p\n", &a);
	printf("adresa(b) = 0x%p\n", &b);

	char* p = NULL;

	// *p = b; // incercare de a scrie valoare la o adresa invalida -> crash app la runtime
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);
	
	p = &b;
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);

	// &b = &a; // adresele de stack seg sunt constante si nu pot fi modificate la run-time

	*p = b + 16;
	printf("p = 0x%p\n", p);
	printf("adresa(p) = 0x%p\n", &p);
	printf("b = %d\n", b);

	char v[] = {9, 8, 8, 9, 9, 5, 2};

	printf("Lungime v = %d bytes\n", sizeof(v));
	printf("Lungime p = %d bytes\n", sizeof(p));

	p = v;
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d ", p[i]);
	printf("\n\n");

	// alocare heap seg pentru vector de sizeof(v) bytes
	p = malloc(sizeof(v));

	for (unsigned char i = 0; i < sizeof(v) - 1; i++)
		p[i] = 'a' + i; // fiecare element/byte stocheaza un cod ASCII
	p[sizeof(v) - 1] = 0; // inserare terminator de string pe ultima pozitie din vectorul dinamic p

	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d->%c ", (unsigned char)p[i], (unsigned char)p[i]); // afisare fiecare byte in 2 moduri: intreg (cod ASCII), simbol din tabela ASCII
	printf("\n\n");

	printf(" %s \n\n", p);


	char m[][3] = { {1, 2, 3}, {9, 9, 9} };

	char** pm = malloc(sizeof(char*) * 2); // 2 linii; alocare structura intermediara cu adrese la linii in matrice
	for (unsigned char i = 0; i < 2; i++)
		// alocare linie i; adresa obtinuta se scrie in structura intermediara
		// + 1 pentru byte aditional de stocare a terminarului de string (byte 0x00 pe ultimul element din linia i)
		pm[i] = malloc((3 + 1) * sizeof(char)); 

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
			pm[i][j] = 'a' + m[i][j];
		pm[i][3] = 0; // scriere terminator de string pe linia i
	}

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
			printf(" %d->%c ", (unsigned char)pm[i][j], (unsigned char)pm[i][j]);
		printf("\n");
	}
	printf("\n\n");

	for (unsigned char i = 0; i < 2; i++)
	{
		printf(" %s\n", pm[i]);
	}
	printf("\n\n");


	// dezalocare heap seg pentru vector p
	free(p);
	// p = NULL;
	for (unsigned char i = 0; i < sizeof(v); i++)
		printf(" %d->%c ", (unsigned char)p[i], (unsigned char)p[i]); // vizualizare byte cu byte din zona dezalocata si rescrisa cu 0xdd
	printf("\n\n");

	// dezalocare matrice
	for (unsigned char i = 0; i < 2; i++)
		free(pm[i]); // dezalocare elemente de pe linia i

	free(pm); // dezalocare de stuctura intermediara

	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	printf(" %s\n", pm[i]); // eroare la run-time deoarece adresele 0xdddddddd nu sunt valide pt app mea
	//}
	//printf("\n\n");

	return 0;
}