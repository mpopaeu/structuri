#include <stdio.h>

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

	// v = &a;

}