#include <stdio.h>
#include <malloc.h>

void main() {

	char c;
	char *pc, v[15];

	c = 65;
	printf(" %d %c\n", c, c);

	pc = &c;
	*pc += 1;

	printf(" %d %c\n", c, c);
	printf(" %d %c\n", *pc, *pc);

	printf("Adrese variabile locale:\n");
	printf(" Adr(c) = %2X Adr(pc) = %2X Adr(v) = %2X\n", &c, &pc, &v);
	printf("Continut variabila pointer:\n");
	printf("Adr(pc) = %X, Cont(pc) = %X, Adr(c) = %X\n", &pc, pc, &c);

	pc = (char*)malloc(c * sizeof(char)); // alocare zona de memorie heap (la runtime)

	printf("Variabila pointer dupa alocare heap:\n");
	printf(" Adr(pc) = %X, Cont(pc) = %X\n", &pc, pc);

	char* pv[15]; // vector de 15 locatii de tip pointer
	for (int i = 0; i < 15; i++)
		pv[i] = &v[i]; // v + i


	free(pc); // dezalocare zona memorie heap
}