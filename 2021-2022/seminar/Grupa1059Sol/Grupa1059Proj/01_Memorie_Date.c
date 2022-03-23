#include <stdio.h>
#include <malloc.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

void main()
{

	// constante si variabile (asigura legatura cu memoria la run-time)
	// tipuri de date:
		// primare: 
					// intregi (ex: [const] [unsigned/signed] char (1 byte), [const] [unsigned/signed] [short/long] int (2/4 bytes)), 
					// reale (ex: [const] float (4 bytes), [const] [long] double (8/10/16 bytes))
		// derivate: masive, pointeri
		// "user"-defined (by developer): struct, union (class C++)

	const char ca = 'X'; // signed by default
	// ca = 0x41;

	//char a = ca; // signed by default
	//short int b = 0x0244;
	//a = b;

	unsigned char a = ca; 
	short int b = 0x99;
	a = (unsigned char)b;

	long int c = 0x000102DC;
	a = (unsigned char)c;

	float f = 0;
	f = (float)c;


	char v[10]; // 10 elemente de tip char; v[i] --> acces la elementul cu offset i fata de inceputul zonei de memorie (inceput vector)
				// v ---> adresa de inceput a zonei de memorie unde sunt alocate elementele

	char* pc; // pointer la locatie de tip char; variabila locala care contine o adresa de memorie de tip char

	pc = &a; // adresa de stack seg scrisa in variabila pc
	a = a + 1; // modificare directa a var "a"
	*pc = a + 1; // modificare indirecta a var "a"

	printf("Utilizare pointer pc pentru variabila a:\n");
	printf("Adresa_stack_pc = %p, Adresa_cont_pc = %p, Acces_indirect_din_pc(var_a) = %u \n", &pc, pc, (unsigned char)*pc);

	pc = v; // adresa inceput vector "v" scrisa in var pointer "pc"
	*pc = 0; // modificare continul elem[1] din vectorul v

	for (unsigned char i = 0; i < 10; i++)
	{
		pc[i] = i + 1;
	}

	printf("Utilizare pointer pc pentru variabila v:\n");
	printf("Adresa_stack_pc = %p, Adresa_cont_pc = %p \n", &pc, pc);

	for (unsigned char i = 0; i < 10; i++)
	{
		printf("element[%u]: Adresa_stack_elem = %p, Valoare_elem = %d \n", (unsigned char)(i + 1), pc + i, pc[i]);
	}

	// v = &a; // eroare de compilare, adresa de stack seg nu poate fi modificata (constanta)

	pc = (char*)malloc(10 * sizeof(char)); // alocare 10 elem de tip char in heap seg
	for (unsigned char i = 0; i < 10; i++)
	{
		pc[i] = i + 1;
	}

	printf("Utilizare pointer pc pentru heap seg:\n");
	printf("Adresa_stack_pc = %p, Adresa_cont_pc = %p \n", &pc, pc);

	for (unsigned char i = 0; i < 10; i++)
	{
		printf("element[%u]: Adresa_heap_elem = %p, Valoare_elem = %d \n", (unsigned char)(i + 1), pc + i, pc[i]);
	}

	char mat[2][3]; // mat --> matrice, var locala (elem stack seg)
	char **ppc;

	for (unsigned char i = 0; i < 2; i++)
		for (unsigned char j = 0; j < 3; j++)
			mat[i][j] = i * 10 + j;

	ppc = (char**)malloc(2 * sizeof(char*)); // alocare vector de pointeri la linii (adrese de inceput linii)
	for (unsigned char i = 0; i < 2; i++)
		ppc[i] = (char*)malloc(3 * sizeof(char)); // ppc[i] --> adresa de inceput a liniei i; fiecare linie are 3 elemente

	for (unsigned char i = 0; i < 2; i++)
		for (unsigned char j = 0; j < 3; j++)
			ppc[i][j] = i * 10 + j;


	// dezalocare heap seg pt elementele vectorului pc
	free(pc);
	pc = NULL; // pc = 0;
	// pc[0] = pc[1] + 1; // eroare la run-time; pointer pc nul

	// dezalocare matrice in heap seg
	for (unsigned char i = 0; i < 2; i++)
		free(ppc[i]); // dezalocare linie i cu elemente de tip char
	free(ppc); // dezalocare vector intermediar cu elemente de tip char*
	ppc = NULL;

	char str1[] = "Structuri de";
	char str2[] = "Date";

	ppc = (char**)malloc(2 * sizeof(char*)); 
	ppc[0] = (char*)malloc((strlen(str1) + 1) * sizeof(char)); 
	strcpy(ppc[0], str1);
	ppc[1] = (char*)malloc((strlen(str2) + 1) * sizeof(char));
	strcpy(ppc[1], str2);

	for (unsigned char i = 0; i < 2; i++)
		printf("String #%u ---> %s\n", i + 1, ppc[i]);

	// rescriere terminator string pentru linia 2 ("Date")
	ppc[1][strlen(ppc[1])] = 'X';

	for (unsigned char i = 0; i < 2; i++)
		printf("String #%u ---> %s\n", i + 1, ppc[i]);

	// dezalocare matrice de string-uri in heap seg
	for (unsigned char i = 0; i < 2; i++)
		free(ppc[i]); 
	free(ppc); 
	ppc = NULL;

	struct Angajat ang, vang[10], *pang, **mang;
	char anume[] = "Popescu Maricel";

	ang.nume = (char*)malloc((strlen(anume) + 1) * sizeof(char));
	strcpy(ang.nume, anume);
	ang.cod = 0x1134;
	ang.salariu = 5500.00f;

	for (unsigned char i = 0; i < (sizeof(vang) / sizeof(struct Angajat)); i++)
	{
		vang[i].nume = (char*)malloc((strlen(ang.nume) + 1) * sizeof(char));
		strcpy(vang[i].nume, ang.nume);
		vang[i].cod = ang.cod + 1 * 10;
		vang[i].salariu = ang.salariu + i * 100;
	}

	pang = (struct Angajat *)malloc(sizeof(struct Angajat) * 1);
	pang->nume = (char*)malloc((strlen(ang.nume) + 1) * sizeof(char));
	strcpy(pang->nume, ang.nume);

	(*pang).cod = 0x1100;
	pang->salariu = ang.salariu + 500;

	// alocare si initilizare matrice de angajati
	// criteriu de organizare: cod angajat

	// dezalocare mem heap

}