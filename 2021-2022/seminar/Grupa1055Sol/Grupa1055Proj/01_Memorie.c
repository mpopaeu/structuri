#include <stdio.h>

typedef char boolean;

#define VECTOR_SIZE 10

void main()
{
	// variabile/constante
	const signed char c = 60;
	// c = 'X';
	signed char a = 'X';
	// tipuri de date
		// 1. primare (standard/fundamentale):
			// 1.1 intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
			// 1.2 reale:   float (4 bytes), [long] double (8 bytes / 10 bytes / 16 bytes) ---> (-1)^s * 1,01011100111 * 2^exp
		// 2. derivate: masive, pointeri
		// 3. "user"-defined: struct, union (C++ class)
	
	unsigned long int i = 0x121314CA; // 0x12 ---> 0001 0010

	a = (signed char)i;

	float f = (float)i;
	boolean vb = 1;


	unsigned char v[VECTOR_SIZE];	// VECTOR_SIZE elem * sizeof(unsigned char) = VECTOR_SIZE bytes
									// v[i] --> i offset (nr de elem) pentru elementul curent (pozitia i + 1 in vector) 
									// v --> adresa de inceput a vectorului (zona de memorie alocata pentru cele VECTOR_SIZE elem)

	for (unsigned char i = 0; i < VECTOR_SIZE; i++)
	{
		v[i] = i + 1;
	}


	unsigned char* pv; // pv variabila pointer, variabila locala
	pv = &a; // adresa variabila "a" scrisa in variabila "pv"

	printf("Adrese si continuturi initiale pentru variabilele pv si a:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);
	*(pv) = a + 1; // a utilizat direct prin var "a", a utilizat indirect prin var "pv"
	printf("Adrese si continuturi dupa modificare pentru variabilele pv si a:\n");
	printf("Adresa_stack_pv = %p, Adresa_continuta_pv = %p, Adresa_stack_a = %p, Continut_a = %d\n", &pv, pv, &a, a);

}