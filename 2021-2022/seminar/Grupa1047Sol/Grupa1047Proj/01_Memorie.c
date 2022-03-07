#include <stdio.h>

#define DIM_VECTOR 10

void main()
{
	// variabile/constante
	signed char a = 73; // a = 0x49; a = 'I';
	const signed char b = 80;
	// b = a + 5;

	// tipuri de date:
		// 1. primare:	
			// 1.1 valori intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
			// 1.2 valori reale: float (4 bytes), [long] double (8/10/16 bytes) ----> VM (-1)^s * 1,01110011011 * 2^exp
		// 2. derivate:	masive, pointeri
		// 3. "user"-defined: struct, union (C++ class)

	long signed int x = 0x112233BB; // 0xcccccccc --> 11001100110011001100110011001100

	a = (signed char)x;

	float f;
	f = (float)x;

	///////////////////
	unsigned char v[DIM_VECTOR]; // v - vector, variabila locala, contine 10 elem * sizeof(unsigned char) = 10 bytes; 
						// v[i] --> acces la valoarea elem cu offset i in masiv/vector, i = 0, 1, ..., 9; 
						// v --> adresa de inceput a zonei alocate vectorului; v + i = Adr(v) + i * sizeof(tip_date)


	unsigned char* pv; // variabila pointer (stocheaza adresa), variabila locala (alocata la compilare in stack seg)

	pv = &a; // pv scris cu adresa de stack seg a locatiei "a"

	printf("/////////\n");
	printf("Adrese si continuturi la initializare ale locatiilor \"a\" si \"pv\"\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);
	a = a + 1; // modificare directa a locatiei "a"
	*pv = a + 1; // acces direct la locatie "a" pentru preluare continut, acces indirect la locatie "a" pentru salvare nou continut
	printf("Adrese si continuturi dupa modificare ale locatiilor \"a\" si \"pv\"\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);


	pv = v; // pv scris cu adresa stack seg unde incepe vectorul v
	printf("/////////\n");
	printf("Adrese si continuturi la initializare ale locatiilor \"v\" si \"pv\"\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	for (unsigned char i = 0; i < DIM_VECTOR; i++)
	{
		v[i] = i + 1;
		printf("Element %u --> Adresa_stack = %p, Continut = %u\n", i, v + i, v[i]);
	}

	// modificare elemente vector
	printf("Adrese si continuturi dupa modificare ale locatiilor \"v\" si \"pv\"\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_v = %p\n", &pv, pv, v);
	for (unsigned char i = 0; i < DIM_VECTOR; i++)
	{
		pv[i] = v[i] + 1; // acces cu v si pv la elementele vectorului; i offset -> nr elemente predecesoare pt elem curent
		printf("Element %u --> Adresa_stack = %p, Continut = %u\n", i, v + i, v[i]);
	}

	// v = &a; // eroare de compilare deoarece adresele de stack seg nu pot fi modificate (constante)

}