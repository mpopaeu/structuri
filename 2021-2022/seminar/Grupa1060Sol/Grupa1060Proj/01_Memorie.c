#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef char boolean;
#define TRUE 1
#define FALSE 0

#define DIMENSIUNE_VECTOR 10

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct Angajat** clasificare_ang(struct Angajat** va_ang, unsigned char nr_angajati,
								float prag_salariu,
								unsigned char * linii_size, unsigned char* nr_linii)
{

}

void main()
{

	//// constante/variabile
	//const signed char x = 88;
	//// x = 'A';
	//signed char a = 'A';

	//// tipuri de date:
	//	// 1. primare (standard/predefinite): 
	//			// intregi:  [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
	//			// reali:    float (4 bytes), [long] double (8 bytes/10 bytes/16 bytes)  (-1)^s * 1,0101101011011 * 2^exp
	//	// 2. derivate: masive, pointeri
	//	// 3. "user"-defined: struct, union (C++ class), "typedef" - definire tip echivalent
	//boolean b = TRUE;

	//long int y = 0x112233AA; // 4 bytes ; 0x11 = 0001 0001

	//a = (signed char)y; // trunchiere la 1 byte
	//float f = (float)y; // conversie int-to-float, schimbarea modului de reprezentare (CD -> VM)

	//unsigned char v[DIMENSIUNE_VECTOR]; // vector alocat la compilare; DIMENSIUNE_VECTOR elem * sizeof(unsigned char)
	//									// v[i] --> acces la un element din vector; i --> offset elemente pt elem curent
	//									// v --> variabila vector, adresa de inceput a zonei alocate pt vector

	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	v[i] = i + 1;
	//}

	//unsigned char* pv; // variabila pointer, variabila locala (alocata in stack seg la compilare), stocheaza adrese FAR pe 4 bytes
	//pv = (unsigned char*)&a; // scriere in pv adresa stack seg a var "a"

	//printf("Adrese si continuturi variabile pv si a dupa initializare:\n");
	//printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_a = 0x%p, Continut_a = %d\n", &pv, pv, &a, a);
	//*(pv) = a + 1; // acces direct din a la var "a", acces indirect din pv la var "a"

	//printf("Adrese si continuturi variabile pv si a dupa modificare:\n");
	//printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_a = 0x%p, Continut_a = %d\n", &pv, pv, &a, a);


	//pv = v; // re-scriere in pv adresa stack seg a inceputului de zona de memorie alocata elementelor vectorului
	//printf("///////////////////////////////////////////////////////////////\n");
	//printf("Adrese si continuturi variabile pv si v dupa initializare:\n");
	//printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_v = 0x%p\n", &pv, pv, &v);
	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, v + i, v[i]); // v[i] ---> *(v + i)
	//}

	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	pv[i] = v[i] + 1; // modificare elemente vector
	//}

	//printf("Adrese si continuturi variabile pv si v dupa modificare:\n");
	//printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_v = 0x%p\n", &pv, pv, &v);
	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, v + i, v[i]); // v[i] ---> *(v + i)
	//}

	//// v = (unsigned char*)&a; // adresele de stack seg nu pot fi modificate!!!! eroare de compilare

	//// alocare memorie la run-time

	//pv = (unsigned char*)malloc(DIMENSIUNE_VECTOR * sizeof(unsigned char));

	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	pv[i] = v[i] + 1; // initializare elemente vector alocat in seg heap
	//}

	//printf("Elemente vector v: \n");
	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, v + i, v[i]); // v[i] ---> *(v + i)
	//}
	//printf("Elemente vector pv: \n");
	//for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	//{
	//	printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, pv + i, pv[i]); // pv[i] ---> *(pv + i)
	//}

	//free(pv);
	//// pv[0] = 1;

	//char mat[2][3], ** pmat;

	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	for (unsigned char j = 0; j < 3; j++)
	//	{
	//		mat[i][j] = i * 10 + j;
	//	}
	//}

	//// alocare matrice heap
	//pmat = (char**)malloc(sizeof(char*) * 2); // 2 este nr de linii matrice pmat
	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	pmat[i] = (char*)malloc(3 * sizeof(char));
	//}


	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	for (unsigned char j = 0; j < 3; j++)
	//	{
	//		pmat[i][j] = mat[i][j] + 1;
	//	}
	//}


	//// dezalocare matrice heap
	//for (unsigned char i = 0; i < 2; i++)
	//{
	//	free(pmat[i]);
	//}
	//free(pmat);
	//pmat = NULL; // rescriere explicita pmat cu valoare nula
	//// pmat[0][0] += 1; // eroare run-time; incercare acces la adresa 0xdddddddd pt pmat[i]

	//char str[] = "Structuri";
	////printf("\n String = %s\n", str);
	////str[strlen(str)] = 'X';
	////printf("\n String = %s\n", str);
	//char str2[] = "de";
	//char str3[] = "Date";

	//pmat = (char**)malloc(3 * sizeof(char*));
	//pmat[0] = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	//pmat[1] = (char*)malloc(sizeof(char) * (strlen(str2) + 1));
	//pmat[2] = (char*)malloc(sizeof(char) * (strlen(str3) + 1));

	//strcpy(pmat[0], str);
	//strcpy(pmat[1], str2);
	//strcpy(pmat[2], str3);

	//printf("\n");
	//for (unsigned char i = 0; i < 3; i++)
	//	printf("%s ", pmat[i]);
	//printf("\n");

	//// dezalocare matrice heap
	//for (unsigned char i = 0; i < 3; i++)
	//{
	//	free(pmat[i]);
	//}
	//free(pmat);
	//pmat = NULL;

	struct Angajat ang, *pang, vang[DIMENSIUNE_VECTOR], **mang;
	printf("\nDimensiune structura Angajat = %d", sizeof(struct Angajat));

	ang.cod = 0x348F;
	ang.nume = (char*)malloc(sizeof(char) * (strlen("Ionescu George") + 1));
	strcpy(ang.nume, "Ionescu George");
	ang.salariu = 4900.34f;

	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	{
		vang[i].cod = ang.cod + i * 10;
		vang[i].salariu = ang.salariu + i * 1.05f;
		vang[i].nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
		strcpy(vang[i].nume, ang.nume);
		vang[i].nume[0] += i + 1;
	}

	pang = (struct Angajat*)malloc(1 * sizeof(struct Angajat));
	pang->cod = ang.cod - 3;
	pang->salariu = ang.salariu * 0.96f;
	pang->nume = (char*)malloc(sizeof(char) * (strlen(ang.nume) + 1));
	strcpy(pang->nume, ang.nume);
	pang->nume[0] -= 1;

	printf("\n Angajat #1 = %u, %s, %.2f", ang.cod, ang.nume, ang.salariu);

	for(unsigned char i = 0; i<DIMENSIUNE_VECTOR; i++)
		printf("\n Angajat #%u = %u, %s, %.2f", i + 2, vang[i].cod, vang[i].nume, vang[i].salariu);

	printf("\n Angajat #12 = %u, %s, %.2f", pang->cod, pang->nume, pang->salariu);

	// construire vector de pointeri la Angajat
	struct Angajat** va_ang; // vector!!!
	unsigned char nr_amgajati = (sizeof(ang) + sizeof(vang) + sizeof(*pang)) / sizeof(struct Angajat);

	// alocare vector de adrese Angajat
	va_ang = (struct Angajat**)malloc(nr_amgajati * sizeof(struct Angajat*));

	unsigned char k = 0;
	va_ang[k++] = &ang;
	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
		va_ang[k++] = vang + i; // adresa element i din vang
	va_ang[k++] = pang;


}