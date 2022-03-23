#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	char* nume;
	unsigned short int cod;
	float salariu;

	struct Angajat *ang;
};

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
		vangs[i].salariu = ang.salariu;
	}

	pang = vangs;
	pang[1].cod += 10;
	(pang + 2)->cod += 11;

	pang = (struct Angajat*)malloc(1 * sizeof(struct Angajat));
	pang->nume = malloc((strlen(vangs[2].nume) + 1) * sizeof(char));
	strcpy(pang->nume, vangs[2].nume);
	pang->cod = vangs[2].cod;
	pang->salariu = vangs[2].salariu * 1.11f;

	// functie alocare si initializare matrice in heap pentru cei 12 Angajati de mai sus
	// criteriu de organizare: salariu
	// return functie: matrice + vector gestionare dimensiuni linii

	// dezalocare memorie heap pentru toatre structurile aferente Angajat

}