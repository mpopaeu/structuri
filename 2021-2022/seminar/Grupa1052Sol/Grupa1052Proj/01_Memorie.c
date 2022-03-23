#include <stdio.h>
#include <malloc.h>

typedef char boolean;

void main()
{

	// constante si variabile

	const char c = 'X';
	// c = 'A';
	char a = -70;
	a = a + 2;

	// tipuri de date:
		// 1. primare (standard) - [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
		//						 - float (4 bytes), [long] double (8 bytes/10 bytes/16 bytes) ---> (-1)^s * 1,001110011 * 2^exp
		// 2. derivate - masive, pointeri
		// 3. "user"-defined - struct, union (C++ class)

	unsigned long int i = 0x000102AA;
	i = i + 1;

	a = (char)i;

	float f; // nr real reprezentat in Virgula Mobila -> 4 bytes
	f = (float)i;

	char v[10]; // vector de 10 elemente, fiecare element de tip char, 10 * sizeof(char) bytes = 10 bytes
				// v[i] --> acces la elementul cu offset i pe zona de memorie alocata vectorului; aritmetica de pointeri
				// v --> variabila vector; "pointer" la inceputul zonei alocate pentru vector

	char* pv; // variabila pointer, variabila locala functiei main --> se aloca in stack seg
	pv = &a; // adresa de stack seg pt locatia/var "a" este stocata in var pointer pv

	a = a + 1; // acces direct la var "a"
	*pv = *pv + 1; // acces indirect la var "a"

	printf("Variabila pointer pv cu adresa stack seg variabila char a\n");
	printf("Adresa_locatie_pointer = %p, Adresa_continuta_pointer = %p, Valoare_accesata_indirect = %d\n", &pv, pv, *pv);

	pv = v; // adresa de stack seg de inceput vector v
	for (unsigned char j = 0; j < 10; j++)
	{
		v[j] = j + 1;
	}

	printf("Variabila pointer pv cu adresa stack seg variabila vector v\n");
	printf("Adresa_locatie_pointer = %p, Adresa_continuta_pointer = %p\n", &pv, pv);
	for (unsigned char j = 0; j < 10; j++)
	{
		printf("elementul %u ---> Adresa_element = %p, Valoare_element = %d\n", (unsigned char)(j + 1), pv + j, pv[j]);
	}


	// alocare memorie la run-time
	pv = (char*)malloc(10 * sizeof(char));

	for (unsigned char j = 0; j < 10; j++)
	{
		pv[j] = j*10 + 1;
	}

	free(pv); // nu rescrie pv cu NULL
	pv = NULL;

	// *pv = 1;

	// &pv = &a; // adresele de stack segment sunt constante (nu pot fi modificate la run-time)


	char mat[2][3], ** pmat;

	for (unsigned char j = 0; j < 2; j++)
	{
		for (unsigned char k = 0; k < 3; k++)
		{
			mat[j][k] = j * 10 + k;
		}		
	}

	for (unsigned char j = 0; j < 2; j++)
	{
		for (unsigned char k = 0; k < 3; k++)
		{
			printf("mat[%u][%u] = %d ", j + 1, k + 1, mat[j][k]);
		}
		printf("\n");
	}

	pmat = (char**)malloc(sizeof(char*) * 2); // vector de pointeri la linii (2 linii)
	for (unsigned char j = 0; j < 2; j++)
		pmat[j] = (char*)malloc(sizeof(char) * 3); // 3 nr de coloane ale matricei


	for (unsigned char j = 0; j < 2; j++)
	{
		for (unsigned char k = 0; k < 3; k++)
		{
			pmat[j][k] = j * 16 + k;
		}
	}

	for (unsigned char j = 0; j < 2; j++)
	{
		for (unsigned char k = 0; k < 3; k++)
		{
			printf("pmat[%u][%u] = %d ", j + 1, k + 1, pmat[j][k]);
		}
		printf("\n");
	}

	// dezalocare matrice pmat
	for (unsigned char j = 0; j < 2; j++)
		free(pmat[j]); // dezalocare linie j
	free(pmat); // dezalocare structura intermediara (vector de pointeri la linii)
	pmat = NULL;


	char s1[] = "Structuri";
	char s2[] = "de";
	char s3[] = "Date";

	pmat = (char**)malloc(sizeof(char*) * 3); // 3 linii, fiecare linie un string de lungime diferita
	
	pmat[0] = (char*)malloc(sizeof(char) * (strlen(s1) + 1));
	pmat[1] = (char*)malloc(sizeof(char) * (strlen(s2) + 1));
	pmat[2] = (char*)malloc(sizeof(char) * (strlen(s3) + 1));

	strcpy(pmat[0], s1);
	strcpy(pmat[1], s2);
	strcpy(pmat[2], s3);


	// dezalocare matrice de string-uri
}