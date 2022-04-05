#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	char* nume;
	unsigned short int cod;
	float salariu;
};

// [in] va_angajati - vector cu adrese de tip Angajat
// [in] va_size - numarul de elemente vector va_angajati
// [out] linii_size - vector cu nr de Angajat pe fiecare linie din matricea construita
// [out] nr_linii - numarul de linii pentru vectorul linii_size; este identic cu nr de linii din matricea construita
// [in] prag_salariu - criteriul de clasificare elemente Angajat din vectorul va_angajati in matricea construita
// return - matrice construita pentru elemente de tip Angajat clasificate pe baza prag_salariu
struct Angajat** imparte_angajati(struct Angajat* *va_angajati, unsigned char va_size, 
									unsigned char **linii_size, unsigned char *nr_linii, 
									float prag_salariu)
{
	struct Angajat** mat_angajati;
	*nr_linii = 2; // doua clase de Angajat pe baza de prag_salariu
	*linii_size = (unsigned char *)malloc(*nr_linii * sizeof(unsigned char)); // alocare 2 elem in vectorul de dimensiuni linii matrice

	// initializare elemente vector dimensiuni linii ale matricei
	for (unsigned char i = 0; i < *nr_linii; i++)
		(*linii_size)[i] = 0;


	for (unsigned char i = 0; i < va_size; i++)
	{
		if (va_angajati[i]->salariu <= prag_salariu)
			(*linii_size)[0]++; // prima linie din matrice cu elem Angajat sub prag
		else
			(*linii_size)[1]++; // a doua linie din matrice cu elem Angajat peste prag
	}

	// alocare matrice de Angajat
	mat_angajati = (struct Angajat**)malloc(*nr_linii * sizeof(struct Angajat*));
	for (unsigned char i = 0; i < *nr_linii; i++)
		mat_angajati[i] = (struct Angajat*)malloc((*linii_size)[i] * sizeof(struct Angajat));

	// populare matrice cu date Angajat; nu se partajeaza zone de heap cu structuri existente
	unsigned char k = 0, l = 0;
	for (unsigned char i = 0; i < va_size; i++)
	{
		if (va_angajati[i]->salariu <= prag_salariu)
		{
			mat_angajati[0][k].cod = va_angajati[i]->cod;
			mat_angajati[0][k].salariu = va_angajati[i]->salariu;
			mat_angajati[0][k].nume = (char*)malloc((strlen(va_angajati[i]->nume) + 1) * sizeof(char));
			strcpy(mat_angajati[0][k].nume, va_angajati[i]->nume);
			k += 1;
		}
		else
		{
			mat_angajati[1][l].cod = va_angajati[i]->cod;
			mat_angajati[1][l].salariu = va_angajati[i]->salariu;
			mat_angajati[1][l].nume = (char*)malloc((strlen(va_angajati[i]->nume) + 1) * sizeof(char));
			strcpy(mat_angajati[1][l].nume, va_angajati[i]->nume);
			l += 1;
		}
	}

	return mat_angajati;
}

void main()
{

	// constante si variabile
	// tip de date: 
		// primar (standard, fundamental)
				// intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
				// reali: float (4 bytes), double (8 bytes)), long double (8/10/16 bytes)
		// derivate (masiv (vector, matrice etc) ---> [], pointer ---> *)
		// "user"-defined: struct, union (class in C++)
	
	//signed char a = (signed char)256; // a este variabila -> poate fi rescrisa la run-time
	//a = a + 2; // modificarea lui a

	//int x = 0x0100; // x ---> 0x00000100
	//x = x + a + 2; // x ---> 0x00000104

	//a = (signed char)x;

	//float r = (float)x;

	//r = r + x + 1;
	//x = (int)r; // x ---> 0x00000209

	//char vc[10]; // vector alocat la compilare; contine 10 locatii de tip char; dim vector = 10 * sizeof(char) = 10 bytes
	//char* pc; // var pointer: adresa locatie existenta / vector alocat la run-time/compile-time; contine nr locatii necunoscut la compilare; 
	//		  // variabila pointer locala alocata la compilare in stack seg.

	//// pc scris cu adresa de locatie existenta
	//pc = &a; // pc contine adresa de stack seg a variabilei a

	//printf("Continut variabila a accesat prin intermediul pointerului pc:\n");
	//printf("Adresa_stack(%p), Adresa_cont(%p), Valoare(a)_acces_indirect(%d) \n", &pc, pc, *pc);

	//for (unsigned char i = 0; i < 10; i++)
	//{
	//	vc[i] = i * 10 + 1;
	//}

	//// pc scris cu adresa de inceput a vectorului vc
	//pc = vc;

	//printf("Continut vector vc accesat prin intermediul pointerului pc:\n");
	//printf("Adresa_stack(%p), Adresa_cont(%p) \n", &pc, pc);
	//for (unsigned char i = 0; i < 10; i++)
	//{
	//	printf("Adresa_stack_element_vector[%u]: %p, Valoare(element_vector[%u])_acces_indirect: %d \n", i + 1, pc + i, i + 1, pc[i]);
	//}

	//// vc = &a; // adresa de memorie stack seg este constanta; nu poate fi modificata locatia unei variabile
	//
	//pc = (char*)malloc(10 * sizeof(char));

	//if (pc)
	//{
	//	for (unsigned char i = 0; i < 10; i++)
	//	{
	//		pc[i] = i * 10 + 1;
	//	}
	//}

	//char** ppc; // alocare la run-time
	//char mat[2][3];
	//for (unsigned char i = 0; i < 2; i++)
	//	for (unsigned char j = 0; j < 3; j++)
	//		mat[i][j] = i * 10 + j;

	//// alocare vector de pointeri structura intermediara (adrese de inceput ale liniilor)
	//ppc = (char**)malloc(2 * sizeof(char*)); // 2 linii ale matricei
	//for (unsigned char i = 0; i < 2; i++)
	//	// alocare vector de elemente corespunzator liniei i
	//	ppc[i] = (char*)malloc(3 * sizeof(char));

	//for (unsigned char i = 0; i < 2; i++)
	//	for (unsigned char j = 0; j < 3; j++)
	//		ppc[i][j] = i * 10 + j;


	//// dezalocare vector pc
	//free(pc);
	//pc = NULL; // NULL = 0; pc = 0;
	//// pc[0] = pc[1] + 1;

	//// dezalocare matrice ppc
	//for (unsigned char i = 0; i < 2; i++)
	//	free(ppc[i]);
	//free(ppc);
	//ppc = 0;

	//unsigned char n = 2; // nr linii (string-uri/vectori de char)
	//ppc = (char**)malloc(n * sizeof(char*)); // n linii ale matricei
	//char s1[] = "Structuri";
	//char s2[] = "Date";
	//ppc[0] = (char*)malloc((strlen(s1) + 1) * sizeof(char)); // + 1 pentru a retine terminatorul de sir de caractere in C ---> byte-ul nul
	//strcpy(ppc[0], s1);
	//
	//ppc[1] = (char*)malloc((strlen(s2) + 1) * sizeof(char));
	//strcpy(ppc[1], s2);

	//for (unsigned char i = 0; i < 2; i++)
	//	printf("String #%u --> %s\n", i, ppc[i]);

	//ppc[0][strlen(ppc[0])] = 'A';
	//for (unsigned char i = 0; i < 2; i++)
	//	printf("String #%u --> %s\n", i, ppc[i]);

	//// dezalocare matrice ppc
	//for (unsigned char i = 0; i < 2; i++)
	//	free(ppc[i]);
	//free(ppc);
	//ppc = 0;

	struct Angajat ang, vangs[10], * pang, **mang;
	char snume[] = "Ionescu Gigel";

	ang.nume = (char*)malloc((strlen(snume) + 1) * sizeof(char)); // alocare spatiu mem heap pt nume angajat
	strcpy(ang.nume, snume);
	ang.cod = 0x4477;
	ang.salariu = 4500.00f;

	for (unsigned char i = 0; i < (sizeof(vangs) / sizeof(struct Angajat)); i++)
	{
		vangs[i].nume = (char*)malloc((strlen(ang.nume) + 1) * sizeof(char));
		strcpy(vangs[i].nume, ang.nume);
		vangs[i].cod = ang.cod;
		vangs[i].salariu = ang.salariu * (i*0.02 + i);
	}

	pang = vangs;
	pang[1].cod += 10;
	(pang + 2)->cod += 11;

	pang = (struct Angajat*)malloc(1 * sizeof(struct Angajat));
	pang->nume = malloc((strlen(vangs[2].nume) + 1) * sizeof(char));
	strcpy(pang->nume, vangs[2].nume);
	pang->cod = vangs[2].cod;
	// pang->salariu = vangs[2].salariu * 1.11f;
	pang->salariu = 3500.0f;

	// functie alocare si initializare matrice in heap pentru cei 12 Angajati de mai sus
	// criteriu de organizare: salariu
	// return functie: matrice + vector gestionare dimensiuni linii

	struct Angajati** v_angajati;
	unsigned char nr_angajati;

	// determinare numar de Angajat definiti si utilizati in app
	nr_angajati = (sizeof(ang) + sizeof(vangs) + sizeof(*pang)) / sizeof(struct Angajat);

	// alocare spatiu mem heap pentru stocare adrese de Angajat
	v_angajati = (struct Angajat**)malloc(nr_angajati * sizeof(struct Angajat*));

	// populare vectior cu adrese de Angajat in vederea construirii matricei
	unsigned char k = 0;
	v_angajati[k++] = &ang;
	v_angajati[k++] = pang;
	for (unsigned char i = 0; i < (sizeof(vangs) / sizeof(struct Angajat)); i++)
	{
		v_angajati[k++] = vangs + i; // adresa stack seg a elem i din vectorul vangs
	}

	// apel functie de clasificare elem Angajat
	struct Angajat** mat_clasificare;
	unsigned char* dim_linii = NULL, nr_linii = 0;
	mat_clasificare = imparte_angajati(v_angajati, nr_angajati, &dim_linii, &nr_linii, 4500.01f);

	// afisare continut matrice
	for (unsigned char i = 0; i < nr_linii; i++)
	{
		printf("\n Angajati linia %u (4500.01):", i);
		for (unsigned char j = 0; j < dim_linii[i]; j++)
			printf("\n       %u %.2f", mat_clasificare[i][j].cod, mat_clasificare[i][j].salariu);
	}

	// dezalocare memorie heap pentru toatre structurile aferente Angajat
	free(ang.nume);
	free(pang->nume);
	free(pang);
	pang = NULL;

	for (unsigned char i = 0; i < (sizeof(vangs) / sizeof(struct Angajat)); i++)
		free(vangs[i].nume);

	// dezalocare vector de pointeru la Angajat
	free(v_angajati);

	// dezalocare matrice de angajati
	for (unsigned char i = 0; i < nr_linii; i++)
	{
		for (unsigned char j = 0; j < dim_linii[i]; j++)
			free(mat_clasificare[i][j].nume); // dezalocare nume Angajat de pe pozitia i,j
		free(mat_clasificare[i]); // dezalocare linie i
	}
	free(mat_clasificare);
	mat_clasificare = NULL;

	// dezalocare vector de dimensiuni ale liniilor din matricea mang
	free(dim_linii);
	dim_linii = NULL;
}