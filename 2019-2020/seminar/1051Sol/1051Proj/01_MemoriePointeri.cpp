#include <stdio.h>
#include <malloc.h>

void main() {

	char c, *pc, v[10];

	c = 68;
	printf(" %d %c \n", c, c);

	pc = &c;
	*pc += 3;
	printf(" %d %c \n", c, c);
	*pc = 'K';
	printf(" %d %c \n", c, c);

	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v) = %X \n", &c, &pc, &v);
	printf("Adr(c) = %X, Adr(pc) = %X, Cont(pc) = %X \n", &c, &pc, pc);

	pc = &v[2];
	*pc = 'Q';
	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v[2]) = %X, Cont(pc) = %X \n", &c, &pc, &v[2], pc);

	char* pv[10]; // vector de pointeri la char

	for (int i = 0; i < 10; i++)
		pv[i] = &v[i]; // initializare pointer i din vector

	for(int i =0; i<10; i++)
		printf("Adr(pv) = %X, Adr(pv[i]) = %X, Cont(pv[i]) = %X, Adr(v[i]) = %X \n", &pv, &pv[i], pv[i], &v[i]);

	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v[2]) = %X, Cont(pc) = %X \n", &c, &pc, &v[2], pc);
	pc = (char*)malloc(c * sizeof(char));
	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v[2]) = %X, Cont(pc) = %X \n", &c, &pc, &v[2], pc);

	free(pc);
}