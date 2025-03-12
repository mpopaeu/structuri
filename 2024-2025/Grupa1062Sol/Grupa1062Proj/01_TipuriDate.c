#include <stdio.h>
#include <malloc.h>

#define NR_ELEMENTE 10
#define NR_LINII 10
#define NR_COLOANE 10

int main()
{
	char x = 65;
	char y = -2;

	float z = (float)65.64;

	char* p_char = NULL;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	//printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = &x;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = (char*)malloc(sizeof(char));
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char[0] = x;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	free(p_char);
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = malloc((NR_ELEMENTE + 1) * sizeof(char));

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		p_char[i] = x + i;
	}
	p_char[NR_ELEMENTE] = 0; // terminatorul de string in C

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		printf("%d --> %c\n", p_char[i], p_char[i]);
	}

	printf("%s in memorie heap\n", p_char);

	free(p_char);

	char v[NR_ELEMENTE + 1]; // masiv uni0-dimensional alocat in stack seg
	p_char = v; 

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		v[i] = x + i;
	}
	v[NR_ELEMENTE] = 0;
	printf("%s in memorie stack\n", p_char);

	char** p_Mat = NULL;
	// alocare vector de adrese de linii nivel 1 de indirectare
	p_Mat = (char**)malloc(NR_LINII * sizeof(char*));
	for (unsigned char i = 0; i < NR_LINII; i++)
		p_Mat[i] = (char*)malloc(NR_COLOANE * sizeof(char)); // alocare vector de elemnte per linian i (nivel 2 matrice)

	// utilizare matrice p_Mat[i][j] --> acces la element linia i si coloana j

	// dezalocare matrice
	for (unsigned char i = 0; i < NR_LINII; i++)
		free(p_Mat[i]); // dezalocare elemente (vector nivel 2) linia i din matrice
	free(p_Mat); // dezalocare vector de adrese de linii de pe nivelul 1

	return 0;
}