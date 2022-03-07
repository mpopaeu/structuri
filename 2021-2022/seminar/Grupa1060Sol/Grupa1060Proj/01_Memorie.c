#include <stdio.h>


typedef char boolean;
#define TRUE 1
#define FALSE 0

#define DIMENSIUNE_VECTOR 10

void main()
{

	// constante/variabile
	const signed char x = 88;
	// x = 'A';
	signed char a = 'A';

	// tipuri de date:
		// 1. primare (standard/predefinite): 
				// intregi:  [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
				// reali:    float (4 bytes), [long] double (8 bytes/10 bytes/16 bytes)  (-1)^s * 1,0101101011011 * 2^exp
		// 2. derivate: masive, pointeri
		// 3. "user"-defined: struct, union (C++ class), "typedef" - definire tip echivalent
	boolean b = TRUE;

	long int y = 0x112233AA; // 4 bytes ; 0x11 = 0001 0001

	a = (signed char)y; // trunchiere la 1 byte
	float f = (float)y; // conversie int-to-float, schimbarea modului de reprezentare (CD -> VM)

	unsigned char v[DIMENSIUNE_VECTOR]; // vector alocat la compilare; DIMENSIUNE_VECTOR elem * sizeof(unsigned char)
										// v[i] --> acces la un element din vector; i --> offset elemente pt elem curent
										// v --> variabila vector, adresa de inceput a zonei alocate pt vector

	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	{
		v[i] = i + 1;
	}

	unsigned char* pv; // variabila pointer, variabila locala (alocata in stack seg la compilare), stocheaza adrese FAR pe 4 bytes
	pv = (unsigned char*)&a; // scriere in pv adresa stack seg a var "a"

	printf("Adrese si continuturi variabile pv si a dupa initializare:\n");
	printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_a = 0x%p, Continut_a = %d\n", &pv, pv, &a, a);
	*(pv) = a + 1; // acces direct din a la var "a", acces indirect din pv la var "a"

	printf("Adrese si continuturi variabile pv si a dupa modificare:\n");
	printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_a = 0x%p, Continut_a = %d\n", &pv, pv, &a, a);


	pv = v; // re-scriere in pv adresa stack seg a inceputului de zona de memorie alocata elementelor vectorului
	printf("///////////////////////////////////////////////////////////////\n");
	printf("Adrese si continuturi variabile pv si v dupa initializare:\n");
	printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_v = 0x%p\n", &pv, pv, &v);
	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	{
		printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, v + i, v[i]); // v[i] ---> *(v + i)
	}

	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	{
		pv[i] = v[i] + 1; // modificare elemente vector
	}

	printf("Adrese si continuturi variabile pv si v dupa modificare:\n");
	printf("Adresa_stack_pv = 0x%p, Adresa_continut_pv = 0x%p, Adresa_stack_v = 0x%p\n", &pv, pv, &v);
	for (unsigned char i = 0; i < DIMENSIUNE_VECTOR; i++)
	{
		printf("Element %u: Adresa_element = 0x%p, Continut_element = %u\n", i, v + i, v[i]); // v[i] ---> *(v + i)
	}

	// v = (unsigned char*)&a; // adresele de stack seg nu pot fi modificate!!!! eroare de compilare

	// alocare memorie la run-time
}