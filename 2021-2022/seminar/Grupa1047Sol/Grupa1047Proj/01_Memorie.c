#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DIM_VECTOR 10

struct data
{
	unsigned char zi, luna;
	unsigned short int an;
};

struct angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
	struct data data_angajare;
};

// [in] vadr - vector cu adrese angajati care se clasifica
// [in] nr_angajati - numarul de angajati care se clasifica; dimensiune vector vadr
// [in] v_prag_salarii - vector cu praguri salarii
// [in] nr_praguri - dimensiune vector v_prag_salarii
// [out] nr_linii - nr de linii din matricea rezultat; nr de elemente vector linii_size
// [out] linii_size - vector cu dimensiuni ale liniilor din matricea rezultat
// [return] - adresa mem heap unde se afla matricea rezultat (vectorul de pointeri la linii)
struct angajat** clasificare_angajati(struct angajat** vadr, unsigned char nr_angajati,
									float* v_prag_salarii, unsigned char nr_praguri,
									unsigned char* nr_linii, unsigned char* linii_size)
{
	*nr_linii = nr_praguri + 1; // nr de clase de angajati; nr de linii din matrice
	linii_size = (unsigned char*)malloc(*nr_linii * sizeof(unsigned char));
	for (unsigned char i = 0; i < *nr_linii; i++)
		linii_size[i] = 0;

	// calcul numar de elemente de pe fiecare linie din matrice
	for (unsigned char i = 0; i < nr_angajati; i++)
	{
		unsigned char vb = 0; // nu s-a facut clasificare
		for (unsigned char j = 0; j < nr_praguri && vb == 0; j++)
		{
			if (vadr[i]->salariu < v_prag_salarii[j])
			{
				linii_size[j] += 1; // incrementez nr de angajati de pe linia j
				vb = 1;
			}
		}
		if (vb == 0)
		{
			linii_size[nr_praguri] += 1;
		}
	}

	// alocare matrice
	struct angajat** pmat = (struct angajat**)malloc(*nr_linii * sizeof(struct angajat*));
	for (unsigned char i = 0; i < *nr_linii; i++)
		pmat[i] = (struct angajat*)malloc(linii_size[i] * sizeof(struct angajat));

	unsigned char k = 0;
	for (unsigned char i = 0; i < *nr_linii; i++)
	{
		for (unsigned char j = 0; j < linii_size[i]; j++)
		{
			pmat[i][j].id = vadr[k]->id;
			//...
			k += 1;// acces la urmatorul angajat din vetorul vadr
		}
	}

	return pmat;
}

void main()
{
	//// variabile/constante
	//signed char a = 73; // a = 0x49; a = 'I';
	//const signed char b = 80;
	//// b = a + 5;

	//// tipuri de date:
	//	// 1. primare:	
	//		// 1.1 valori intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
	//		// 1.2 valori reale: float (4 bytes), [long] double (8/10/16 bytes) ----> VM (-1)^s * 1,01110011011 * 2^exp
	//	// 2. derivate:	masive, pointeri
	//	// 3. "user"-defined: struct, union (C++ class)

	//long signed int x = 0x112233BB; // 0xcccccccc --> 11001100110011001100110011001100

	//a = (signed char)x;

	//float f;
	//f = (float)x;

	/////////////////////
	//unsigned char v[DIM_VECTOR]; // v - vector, variabila locala, contine 10 elem * sizeof(unsigned char) = 10 bytes; 
	//					// v[i] --> acces la valoarea elem cu offset i in masiv/vector, i = 0, 1, ..., 9; 
	//					// v --> adresa de inceput a zonei alocate vectorului; v + i = Adr(v) + i * sizeof(tip_date)


	//unsigned char* pv; // variabila pointer (stocheaza adresa), variabila locala (alocata la compilare in stack seg)

	//pv = &a; // pv scris cu adresa de stack seg a locatiei "a"

	//printf("/////////\n");
	//printf("Adrese si continuturi la initializare ale locatiilor \"a\" si \"pv\"\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);
	//a = a + 1; // modificare directa a locatiei "a"
	//*pv = a + 1; // acces direct la locatie "a" pentru preluare continut, acces indirect la locatie "a" pentru salvare nou continut
	//printf("Adrese si continuturi dupa modificare ale locatiilor \"a\" si \"pv\"\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);


	//pv = v; // pv scris cu adresa stack seg unde incepe vectorul v
	//printf("/////////\n");
	//printf("Adrese si continuturi la initializare ale locatiilor \"v\" si \"pv\"\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	//for (unsigned char i = 0; i < DIM_VECTOR; i++)
	//{
	//	v[i] = i + 1;
	//	printf("Element %u --> Adresa_stack = %p, Continut = %u\n", i, v + i, v[i]);
	//}

	//// modificare elemente vector
	//printf("Adrese si continuturi dupa modificare ale locatiilor \"v\" si \"pv\"\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	//for (unsigned char i = 0; i < DIM_VECTOR; i++)
	//{
	//	pv[i] = v[i] + 1; // acces cu v si pv la elementele vectorului; i offset -> nr elemente predecesoare pt elem curent
	//	printf("Element %u --> Adresa_stack = %p, Continut = %u\n", i, v + i, v[i]);
	//}

	////v = &a; // eroare de compilare deoarece adresele de stack seg nu pot fi modificate (constante)

	//// alocare vector la run-time
	//pv = (unsigned char*)malloc(sizeof(v));

	//printf("/////////\n");
	//printf("Adrese si continuturi la alocare memorie dinamica \"pv\"\n");
	//printf("Adresa_stack_pv = %p, Adresa_continuta(heap)_pv = %p\n", &pv, pv);
	//for (unsigned char i = 0; i < DIM_VECTOR; i++)
	//{
	//	pv[i] = v[i] * 10;
	//	printf("Element pv[%u] --> Adresa_heap = %p, Continut = %u\n", i, pv + i, pv[i]);
	//}

	//free(pv);
	//pv = NULL;
	//// pv[0] = 1;

	//char str1[] = "Structuri";
	//
	//pv = (unsigned char*)malloc(sizeof(str1) * sizeof(unsigned char));
	//strcpy(pv, str1);

	//printf("\n String in pv in mem heap #1: %s\n", pv);
	//
	//pv[strlen(pv)] = 'A'; // rescriere terminator string cu valoare ne-nula

	//printf("\n String in pv in mem heap #2: %s\n", pv);

	//free(pv);
	//pv = NULL;

	//char str2[] = "de";
	//char str3[] = "Date";

	//char ** mstr;

	//mstr = (char**)malloc(sizeof(char*) * 3); // 3 string-uri
	//mstr[0] = (char*)malloc(sizeof(char) * (strlen(str1) + 1));
	//mstr[1] = (char*)malloc(sizeof(char) * (strlen(str2) + 1));
	//mstr[2] = (char*)malloc(sizeof(char) * (strlen(str3) + 1));

	//strcpy(mstr[0], str1);
	//strcpy(mstr[1], str2);
	//strcpy(mstr[2], str3);

	//printf("\n String-uri stocate in matrice:\n");
	//for (unsigned char i = 0; i < 3; i++)
	//	printf("\n String #%u = %s", i, mstr[i]);

	//// dezalocare matrice heap
	//for (unsigned char i = 0; i < 3; i++)
	//	free(mstr[i]); // dezalocare linie i
	//free(mstr); // dezalocare vector de adrese de linii
	////mstr = NULL; 
	//if(mstr)
	//	printf("\n String dupa dezalocare matrice = %s", mstr[0]);

	printf("\n Dimensiune structura angajat = %d Bytes\n", sizeof(struct angajat));

	struct angajat ang, vang[DIM_VECTOR], *pang,  **mang;

	// initializare date din ang
	ang.id = 1555;
	ang.nume = (char*)malloc(sizeof(char) * (strlen("Ionescu Vasile") + 1));
	strcpy(ang.nume, "Ionescu Vasile");
	ang.salariu = 4999.50f;
	ang.data_angajare.zi = 10;
	ang.data_angajare.luna = 7;
	ang.data_angajare.an = 2019;

	// initializare date din vector vang
	for (unsigned char i = 0; i < DIM_VECTOR; i++)
	{
		vang[i].id = ang.id + (i * 10 + 1);
		vang[i].nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
		strcpy(vang[i].nume, ang.nume);
		vang[i].nume[0] += i + 1;
		vang[i].salariu = ang.salariu * (i * 0.05f + 1);
		vang[i].data_angajare.zi = ang.data_angajare.zi + (i + 1);
		if ((ang.data_angajare.luna + (i + 1)) % 12 == 0)
			vang[i].data_angajare.luna = 1;
		else
			vang[i].data_angajare.luna = (ang.data_angajare.luna + (i + 1)) % 12;
		vang[i].data_angajare.an = ang.data_angajare.an - (i + 1);
	}

	// alocare si initializare date pointer
	pang = (struct angajat*)malloc(1 * sizeof(struct angajat));
	pang->id = ang.id - 1;
	pang->nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
	strcpy(pang->nume, ang.nume);
	pang->nume[0] -= 1;
	pang->salariu = ang.salariu * 0.96f;
	pang->data_angajare.zi = ang.data_angajare.zi - 1;
	pang->data_angajare.luna = ang.data_angajare.luna - 1;
	pang->data_angajare.an = ang.data_angajare.an + 1;

	// clasificare angajati pe baza de lista prag salarii
	// centralizare angajati de clasificat
	struct angajat** vadr_ang; // vector de adrese de tip angajat
	unsigned char nr_angajati; // nr de angajati care se clasifica; dimensiune vector vadr_ang
	nr_angajati = (sizeof(ang) + sizeof(vang) + (sizeof(*pang) *  1)) / sizeof(struct angajat);
	vadr_ang = (struct angajat**)malloc(nr_angajati * sizeof(struct angajat*));

	unsigned char k = 0;
	vadr_ang[k++] = &ang;
	for (unsigned char i = 0; i < DIM_VECTOR; i++)
	{
		vadr_ang[k++] = vang + i; // adresa elementului vang[i] se scrie pe pozitia k in vectorul de pointeri
	}
	vadr_ang[k++] = pang;

	// definire praguri de clasificare
	float* v_prag_salariu, nr_praguri;
	nr_praguri = 4;
	v_prag_salariu = (float*)malloc(nr_praguri * sizeof(float));
	for (unsigned char i = 0; i < nr_praguri; i++)
		v_prag_salariu[i] = (i + 1) * 1500.00f;

	mang = clasificare_angajati(...);

	// afisare continut matrice mang

	// dezalocare zone de memorie utilizate in app
}