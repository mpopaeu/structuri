#include <stdio.h>
#include <malloc.h>

void main()
{

	// constante si variabile
	// tip de date: 
		// primar (standard, fundamental)
				// intregi: [unsigned/signed] char (1 byte), [unsigned/signed] [short/long] int (2/4 bytes)
				// reali: float (4 bytes), double (8 bytes)), long double (8/10/16 bytes)
		// derivate (masiv (vector, matrice etc) ---> [], pointer ---> *)
		// "user"-defined: struct, union (class in C++)
	
	signed char a = (signed char)256; // a este variabila -> poate fi rescrisa la run-time
	a = a + 2; // modificarea lui a

	int x = 0x0100; // x ---> 0x00000100
	x = x + a + 2; // x ---> 0x00000104

	a = (signed char)x;

	float r = (float)x;

	r = r + x + 1;
	x = (int)r; // x ---> 0x00000209

	char vc[10]; // vector alocat la compilare; contine 10 locatii de tip char; dim vector = 10 * sizeof(char) = 10 bytes
	char* pc; // var pointer: adresa locatie existenta / vector alocat la run-time/compile-time; contine nr locatii necunoscut la compilare; 
			  // variabila pointer locala alocata la compilare in stack seg.

	// pc scris cu adresa de locatie existenta
	pc = &a; // pc contine adresa de stack seg a variabilei a

	printf("Continut variabila a accesat prin intermediul pointerului pc:\n");
	printf("Adresa_stack(%p), Adresa_cont(%p), Valoare(a)_acces_indirect(%d) \n", &pc, pc, *pc);

	for (unsigned char i = 0; i < 10; i++)
	{
		vc[i] = i * 10 + 1;
	}

	// pc scris cu adresa de inceput a vectorului vc
	pc = vc;

	printf("Continut vector vc accesat prin intermediul pointerului pc:\n");
	printf("Adresa_stack(%p), Adresa_cont(%p) \n", &pc, pc);
	for (unsigned char i = 0; i < 10; i++)
	{
		printf("Adresa_stack_element_vector[%d]: %p, Valoare(element_vector[%d])_acces_indirect: %d \n", i + 1, pc + i, i + 1, pc[i]);
	}

	// vc = &a; // adresa de memorie stack seg este constanta; nu poate fi modificata locatia unei variabile
	
	pc = (char*)malloc(10 * sizeof(char));

	if (pc)
	{
		for (unsigned char i = 0; i < 10; i++)
		{
			pc[i] = i * 10 + 1;
		}
	}

	free(pc);
}