#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef char boolean;

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

// [in] v_angajati - vector de pointeri la angajati care se clasifica
// [in] nr_anagajati - dimensiune vector v_angajati
// [in] prag_salariu - pragul in functie de care se realizeaza clasificarea
// [out] nr_linii - nr de linii matrice rezultat
// [out] nr_col - vector de elemente cu dimensiuni ale liniilor pentru matricea rezultat
// [return] - matricea construita pentru clasificare angajati in functie de salariu
struct Angajat** clasificare_angajati(struct Angajat ** v_angajati, unsigned char nr_angajati,
										float prag_salariu, 
										unsigned char * nr_linii, unsigned char ** nr_col)
{
	*nr_linii = 2; // nr clase de angajati in funtie de prag_salariu
	*nr_col = (unsigned char*)malloc(*nr_linii * sizeof(unsigned char));
	for (unsigned char i = 0; i < *nr_linii; i++)
		(*nr_col)[i] = 0;

	for (unsigned char i = 0; i < nr_angajati; i++)
	{
		if (v_angajati[i]->salariu < prag_salariu)
			(*nr_col)[0] += 1;
		else
			(*nr_col)[1] += 1;
	}

	// alocare matrice
	struct Angajat** pmat;
	pmat = (struct Angajat**)malloc(*nr_linii * sizeof(struct Angajat*));
	for (unsigned char i = 0; i < *nr_linii; i++)
		pmat[i] = (struct Angajat*)malloc((*nr_col)[i] * sizeof(struct Angajat));

	unsigned char idxj1 = 0, idxj2 = 0;
	for (unsigned char i = 0; i < nr_angajati; i++)
	{
		struct Angajat tmp;
		tmp.cod = v_angajati[i]->cod;
		tmp.salariu = v_angajati[i]->salariu;
		tmp.nume = malloc(sizeof(char) * (strlen(v_angajati[i]->nume) + 1));
		strcpy(tmp.nume, v_angajati[i]->nume);

		if (v_angajati[i]->salariu < prag_salariu)
			pmat[0][idxj1++] = tmp;
		else
			pmat[1][idxj2++] = tmp;
	}

	return pmat;
}

void main()
{

	//// constante si variabile

	//const char c = 'X';
	//// c = 'A';
	//char a = -70;
	//a = a + 2;

	//// tipuri de date:
	//	// 1. primare (standard) - [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
	//	//						 - float (4 bytes), [long] double (8 bytes/10 bytes/16 bytes) ---> (-1)^s * 1,001110011 * 2^exp
	//	// 2. derivate - masive, pointeri
	//	// 3. "user"-defined - struct, union (C++ class)

	//unsigned long int i = 0x000102AA;
	//i = i + 1;

	//a = (char)i;

	//float f; // nr real reprezentat in Virgula Mobila -> 4 bytes
	//f = (float)i;

	//char v[10]; // vector de 10 elemente, fiecare element de tip char, 10 * sizeof(char) bytes = 10 bytes
	//			// v[i] --> acces la elementul cu offset i pe zona de memorie alocata vectorului; aritmetica de pointeri
	//			// v --> variabila vector; "pointer" la inceputul zonei alocate pentru vector

	//char* pv; // variabila pointer, variabila locala functiei main --> se aloca in stack seg
	//pv = &a; // adresa de stack seg pt locatia/var "a" este stocata in var pointer pv

	//a = a + 1; // acces direct la var "a"
	//*pv = *pv + 1; // acces indirect la var "a"

	//printf("Variabila pointer pv cu adresa stack seg variabila char a\n");
	//printf("Adresa_locatie_pointer = %p, Adresa_continuta_pointer = %p, Valoare_accesata_indirect = %d\n", &pv, pv, *pv);

	//pv = v; // adresa de stack seg de inceput vector v
	//for (unsigned char j = 0; j < 10; j++)
	//{
	//	v[j] = j + 1;
	//}

	//printf("Variabila pointer pv cu adresa stack seg variabila vector v\n");
	//printf("Adresa_locatie_pointer = %p, Adresa_continuta_pointer = %p\n", &pv, pv);
	//for (unsigned char j = 0; j < 10; j++)
	//{
	//	printf("elementul %u ---> Adresa_element = %p, Valoare_element = %d\n", (unsigned char)(j + 1), pv + j, pv[j]);
	//}


	//// alocare memorie la run-time
	//pv = (char*)malloc(10 * sizeof(char));

	//for (unsigned char j = 0; j < 10; j++)
	//{
	//	pv[j] = j*10 + 1;
	//}

	//free(pv); // nu rescrie pv cu NULL
	//pv = NULL;

	//// *pv = 1;

	//// &pv = &a; // adresele de stack segment sunt constante (nu pot fi modificate la run-time)


	//char mat[2][3], ** pmat;

	//for (unsigned char j = 0; j < 2; j++)
	//{
	//	for (unsigned char k = 0; k < 3; k++)
	//	{
	//		mat[j][k] = j * 10 + k;
	//	}		
	//}

	//for (unsigned char j = 0; j < 2; j++)
	//{
	//	for (unsigned char k = 0; k < 3; k++)
	//	{
	//		printf("mat[%u][%u] = %d ", j + 1, k + 1, mat[j][k]);
	//	}
	//	printf("\n");
	//}

	//pmat = (char**)malloc(sizeof(char*) * 2); // vector de pointeri la linii (2 linii)
	//for (unsigned char j = 0; j < 2; j++)
	//	pmat[j] = (char*)malloc(sizeof(char) * 3); // 3 nr de coloane ale matricei


	//for (unsigned char j = 0; j < 2; j++)
	//{
	//	for (unsigned char k = 0; k < 3; k++)
	//	{
	//		pmat[j][k] = j * 16 + k;
	//	}
	//}

	//for (unsigned char j = 0; j < 2; j++)
	//{
	//	for (unsigned char k = 0; k < 3; k++)
	//	{
	//		printf("pmat[%u][%u] = %d ", j + 1, k + 1, pmat[j][k]);
	//	}
	//	printf("\n");
	//}

	//// dezalocare matrice pmat
	//for (unsigned char j = 0; j < 2; j++)
	//	free(pmat[j]); // dezalocare linie j
	//free(pmat); // dezalocare structura intermediara (vector de pointeri la linii)
	//pmat = NULL;


	//char s1[] = "Structuri";
	//char s2[] = "de";
	//char s3[] = "Date";

	//pmat = (char**)malloc(sizeof(char*) * 3); // 3 linii, fiecare linie un string de lungime diferita
	//
	//pmat[0] = (char*)malloc(sizeof(char) * (strlen(s1) + 1)); // +1 pentru terminat de string 0x00
	//pmat[1] = (char*)malloc(sizeof(char) * (strlen(s2) + 1));
	//pmat[2] = (char*)malloc(sizeof(char) * (strlen(s3) + 1));

	//strcpy(pmat[0], s1);
	//strcpy(pmat[1], s2);
	//strcpy(pmat[2], s3);

	//printf("\n String inainte de modificare = %s", pmat[0]);
	//pmat[0][strlen(pmat[0])] = 'A';
	//printf("\n String dupa modificare = %s", pmat[0]);

	//// dezalocare matrice de string-uri
	//for (unsigned char j = 0; j < 3; j++)
	//	free(pmat[j]); // dezalocare linie j
	//free(pmat);
	//pmat = NULL;
	//if(pmat != NULL)
	//	printf("\n String dupa dezalocare = %s", pmat[0]);

	printf("\n Dimensiune structura Angajat = %d", sizeof(struct Angajat));
	struct Angajat ang, vang[10], * pang, ** mang;

	ang.cod = 0x34AB;
	ang.salariu = 4500.11f;
	ang.nume = (char*)malloc((strlen("Georgescu Marian") + 1) * sizeof(char));
	strcpy(ang.nume, "Georgescu Marian");

	// vector alocat compile-time
	for (unsigned char i = 0; i < (sizeof(vang) / sizeof(struct Angajat)); i++)
	{
		vang[i].cod = ang.cod + (i + 1);
		vang[i].salariu = ang.salariu * (i + 0.1f);
		vang[i].nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
		strcpy(vang[i].nume, ang.nume);
		vang[i].nume[0] += i + 1;
	}

	// angajat alocat run-time
	pang = (struct Angajat*)malloc(1 * sizeof(struct Angajat));
	pang->cod = vang[9].cod + 1;
	pang->salariu = vang[9].salariu * 1.1f;
	pang->nume = (char*)malloc(sizeof(char) * (strlen(vang[9].nume) + 1));
	strcpy(pang->nume, vang[9].nume);
	pang->nume[0] = vang[9].nume[0] + 1;

	struct Angajat** va_ang;
	unsigned char nr_angajati = (sizeof(ang) + sizeof(vang) + sizeof(*pang)) / sizeof(struct Angajat);
	va_ang = (struct Angajat**)malloc(nr_angajati * sizeof(struct Angajat*));

	// initializare elemente vector va_ang
	unsigned char k = 0;
	va_ang[k++] = &ang;
	for (unsigned char i = 0; i < sizeof(vang) / sizeof(struct Angajat); i++)
	{
		va_ang[k++] = vang + i;
	}
	va_ang[k++] = pang;

	unsigned char nr_linii, * linii_size = NULL;
	mang = clasificare_angajati(va_ang, nr_angajati, 27550.01f, &nr_linii, &linii_size);

	for (unsigned char i = 0; i < nr_linii; i++)
	{
		printf("\nLinia #%u\n", i);
		for (unsigned char j = 0; j < linii_size[i]; j++)
			printf("\n %s %f", mang[i][j].nume, mang[i][j].salariu);
	}

	//dezalocare memorie heap
	free(ang.nume);
	ang.nume = NULL;
	free(pang->nume);
	free(pang);
	pang = NULL;

	for (unsigned char i = 0; i < sizeof(vang) / sizeof(struct Angajat); i++)
	{
		free(vang[i].nume);
		vang[i].nume = NULL;
	}

	free(va_ang);

	for (unsigned char i = 0; i < nr_linii; i++)
	{
		for (unsigned char j = 0; j < linii_size[i]; j++)
			free(mang[i][j].nume); // dezalocare nume angajat elemente (i; j)
		free(mang[i]); // dezalocare linie i
	}
	free(mang); // dezalocare structura intermediara vector de pointeri la linii
	mang = NULL;

	free(linii_size); // dezalocare vector dimensiuni linii matrice
	linii_size = NULL;
}