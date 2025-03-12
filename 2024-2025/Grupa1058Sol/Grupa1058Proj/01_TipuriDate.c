#include <stdio.h>
#include <malloc.h>

#define NR_ELEMENTE 10
#define NR_LINII 10
#define NR_COLOANE 9

int main()
{
	char x = 65;
	char y = -2;

	float z = 65.64f;

	char* p_char = NULL;
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	//printf("Continut zona pointata de p_char = %d\n", *p_char); // eroare la run-time; adresa nu exista/incorecta

	p_char = &x; 
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char); // p_char[0] in loc de *p_char

	p_char = (char*)malloc(sizeof(char)); // alocare mem heap
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	p_char[0] = x; // *p_char = x;
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	free(p_char); // dezalocare memorie heap

	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	p_char = (char*)malloc((NR_ELEMENTE + 1) * sizeof(char));
	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		p_char[i] = x + i;
	}
	p_char[NR_ELEMENTE] = 0; // scriere terminator string pe ultimul byte alocat

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		printf("%c --> %d\n", p_char[i], p_char[i]);
	}
	printf("\n");

	printf("%s in memorie heap\n", p_char);

	free(p_char);

	char v[NR_ELEMENTE + 1];
	p_char = v;

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		v[i] = x + i;
	}
	v[NR_ELEMENTE] = 0; // scriere terminator string pe ultimul byte din vector
	printf("%s in memorie stack\n", p_char); // afisare string din zona de mem stack alocata lui v

	char** M = NULL;
	// alocare nivel 1 al matricei (nr de linii)
	M = (char**)malloc(NR_LINII * sizeof(char*)); // alocare vector de pointeri la linii
	for (unsigned char i = 0; i < NR_LINII; i++)
		// alocare nivel 2 al matricei
		M[i] = (char*)malloc(NR_COLOANE * sizeof(char)); // alocare mem heap pentru linia i;
														 // adresa de inceput a liniei i este stocata in M[i]

	// initializare & utilizare elemente matrice

	// dezalocare matrice
	for (unsigned char i = 0; i < NR_LINII; i++)
		free(M[i]); // dezalocare vector de elemente char aferent liniei i (nivel 2 al matricei)
	free(M); // dezalocare vector de adrese de inceput de linii (nivel 1 al matricei)

	return 0;
}