#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef char boolean;

#define VECTOR_SIZE 10

struct Angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
};

// [in] va_ang - vector cu adrese Angajat care se clasifica in matrice
// [in] nr_ang - numarul de elemente din va_ang
// [out] linii_size - vector suport cu dimensiunile liniilor din matricea construita
// [out] nr_linii - numarul de linii al matricei construite
// [return] - matricea construita cu angajatii clasificati pe linii
struct Angajat** clasificare_angajati(struct Angajat ** va_ang, unsigned char nr_ang,
										unsigned char * linii_size, unsigned char * nr_linii)
{
	// 3 clase: cod %2, %3 si restul
}

void main()
{
	//// variabile/constante
	//const signed char c = 60;
	//// c = 'X';
	//signed char a = 'X';
	//// tipuri de date
	//	// 1. primare (standard/fundamentale):
	//		// 1.1 intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
	//		// 1.2 reale:   float (4 bytes), [long] double (8 bytes / 10 bytes / 16 bytes) ---> (-1)^s * 1,01011100111 * 2^exp
	//	// 2. derivate: masive, pointeri
	//	// 3. "user"-defined: struct, union (C++ class)
	//
	//unsigned long int i = 0x121314CA; // 0x12 ---> 0001 0010

	//a = (signed char)i;

	//float f = (float)i;
	//boolean vb = 1;


	//unsigned char v[VECTOR_SIZE];	// VECTOR_SIZE elem * sizeof(unsigned char) = VECTOR_SIZE bytes
	//								// v[i] --> i offset (nr de elem) pentru elementul curent (pozitia i + 1 in vector) 
	//								// v --> adresa de inceput a vectorului (zona de memorie alocata pentru cele VECTOR_SIZE elem)

	//for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	//{
	//	v[i] = i + 1;
	//}


	//unsigned char* pv; // pv variabila pointer, variabila locala
	//pv = &a; // adresa variabila "a" scrisa in variabila "pv"

	//printf("Adrese si continuturi initiale pentru variabilele pv si a:\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);
	//*(pv) = a + 1; // a utilizat direct prin var "a", a utilizat indirect prin var "pv"
	//printf("Adrese si continuturi dupa modificare pentru variabilele pv si a:\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);


	//pv = v;
	////pv = &v;

	//printf("Adrese si continuturi initiale pentru variabilele pv si v:\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	//for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	//{
	//	pv[i] = v[i] + 1;
	//}
	//printf("Adrese si continuturi initiale pentru variabilele pv si v:\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);

	//// v = &a; // eroare de compilare --> adresele de stack seg nu pot fi modificate

	//pv = (unsigned char*)malloc(VECTOR_SIZE * sizeof(unsigned char));

	//for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	//{
	//	pv[i] = v[i] + 1;
	//}

	//free(pv);

	//pv = NULL;
	//// pv[0] = 1; // eroare la run-time; acces la pointer null

	//unsigned char mat[2][3], ** pmat;

	//pmat = (unsigned char**)malloc(2 * sizeof(unsigned char*));
	//for (unsigned char i = 0; i < 2; i++)
	//	pmat[i] = (unsigned char*)malloc(3 * sizeof(unsigned char));

	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	for (unsigned char j = 0; j < 3; j++)
	//	{
	//		pmat[i][j] = i * 10 + j;
	//	}
	//}

	//// dezalocare matrice heap seg
	//for (unsigned char i = 0; i < 2; i++)
	//	free(pmat[i]);
	//free(pmat);
	//pmat = NULL;

	//unsigned char str[] = "Structuri";
	////printf("\nString = %s", str);
	////str[strlen(str)] = 'Z';
	////printf("\nString = %s", str);

	//unsigned char str2[] = "de";
	//unsigned char str3[] = "Date";

	//pmat = (unsigned char**)malloc(3 * sizeof(unsigned char*));
	//pmat[0] = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(str) + 1));
	//pmat[1] = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(str2) + 1));
	//pmat[2] = (unsigned char*)malloc(sizeof(unsigned char) * (strlen(str3) + 1));

	//strcpy(pmat[0], str);
	//strcpy(pmat[1], str2);
	//strcpy(pmat[2], str3);

	//printf("\nString-uri in matricea pmat = ");
	//for (unsigned char i = 0; i < 3; i++)
	//	printf("%s ", pmat[i]);
	//printf("\n");

	//// dezalocare matrice pmat (vector de string-uri)
	//for (unsigned char i = 0; i < 3; i++)
	//	free(pmat[i]);
	//free(pmat);
	//pmat = NULL;

	struct Angajat ang, vang[VECTOR_SIZE], *pang;
	printf("\n Dimensiune structura Angajat = %d bytes", sizeof(struct Angajat));


	ang.id = 0x770A;
	ang.nume = (char*)malloc(sizeof(char) * (strlen("Popescu Alex") + 1));
	strcpy(ang.nume, "Popescu Alex");
	ang.salariu = 3650.05f; 

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		vang[i].id = ang.id + i * 10 + i;
		vang[i].nume = malloc(sizeof(char) * (streln(ang.nume) + 1));
		strcpy(vang[i].nume, ang.nume);
		vang[i].nume[0] = ang.nume[0] + i + 1;

		vang[i].salariu = ang.salariu + i * 1.08f;
	}

	pang = (struct Angajat*)malloc(1 * sizeof(struct Angajat));
	pang->id = ang.id - 1;
	pang->nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
	strcpy(pang->nume, ang.nume);
	pang->nume[0] -= 1;
	pang->salariu = ang.salariu * 0.89f;

	struct Angajat** mang, **va_ang;
	unsigned char nr_angajati = (sizeof(ang) + sizeof(vang) + sizeof(*pang)) / sizeof(struct Angajat);

	va_ang = (struct Angajat**)malloc(nr_angajati * sizeof(struct Angajat*));
	unsigned char k = 0;

	va_ang[k++] = &ang;
	va_ang[k++] = pang;
	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
		va_ang[k++] = vang + i;
}