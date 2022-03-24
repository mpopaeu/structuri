#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef char boolean;

#define VECTOR_SIZE 10

void main()
{
	// variabile/constante
	const signed char c = 60;
	// c = 'X';
	signed char a = 'X';
	// tipuri de date
		// 1. primare (standard/fundamentale):
			// 1.1 intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
			// 1.2 reale:   float (4 bytes), [long] double (8 bytes / 10 bytes / 16 bytes) ---> (-1)^s * 1,01011100111 * 2^exp
		// 2. derivate: masive, pointeri
		// 3. "user"-defined: struct, union (C++ class)
	
	unsigned long int i = 0x121314CA; // 0x12 ---> 0001 0010

	a = (signed char)i;

	float f = (float)i;
	boolean vb = 1;


	unsigned char v[VECTOR_SIZE];	// VECTOR_SIZE elem * sizeof(unsigned char) = VECTOR_SIZE bytes
									// v[i] --> i offset (nr de elem) pentru elementul curent (pozitia i + 1 in vector) 
									// v --> adresa de inceput a vectorului (zona de memorie alocata pentru cele VECTOR_SIZE elem)

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		v[i] = i + 1;
	}


	unsigned char* pv; // pv variabila pointer, variabila locala
	pv = &a; // adresa variabila "a" scrisa in variabila "pv"

	printf("Adrese si continuturi initiale pentru variabilele pv si a:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);
	*(pv) = a + 1; // a utilizat direct prin var "a", a utilizat indirect prin var "pv"
	printf("Adrese si continuturi dupa modificare pentru variabilele pv si a:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);


	pv = v;
	pv = &v;

	printf("Adrese si continuturi initiale pentru variabilele pv si v:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		pv[i] = v[i] + 1;
	}
	printf("Adrese si continuturi initiale pentru variabilele pv si v:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);

	// v = &a; // eroare de compilare --> adresele de stack seg nu pot fi modificate

	pv = (unsigned char*)malloc(VECTOR_SIZE * sizeof(unsigned char));

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		pv[i] = v[i] + 1;
	}

	free(pv);

	pv = NULL;
	// pv[0] = 1; // eroare la run-time; acces la pointer null

	unsigned char mat[2][3], ** pmat;

	pmat = (unsigned char**)malloc(2 * sizeof(unsigned char*));
	for (unsigned char i = 0; i < 2; i++)
		pmat[i] = (unsigned char*)malloc(3 * sizeof(unsigned char));

	for (unsigned char i = 0; i < 2; i++)
	{
		for (unsigned char j = 0; j < 3; j++)
		{
			pmat[i][j] = i * 10 + j;
		}
	}

	// dezalocare matrice heap seg
	for (unsigned char i = 0; i < 2; i++)
		free(pmat[i]);
	free(pmat);
	pmat = NULL;

	unsigned char str[] = "Structuri";
	printf("\nString = %s", str);
	str[strlen(str)] = 'Z';
	printf("\nString = %s", str);
}