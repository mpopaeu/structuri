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

	struct angajat ang;

	ang.id
}