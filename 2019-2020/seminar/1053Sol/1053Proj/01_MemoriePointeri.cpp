#include <stdio.h>
#include <malloc.h>


void main() {

	char c, *pc, v[10];

	c = 65;
	pc = &c;

	printf("%d %c\n", c, c);

	*pc = 'C';

	printf("%d %c\n", c, c);
	printf("%d %c\n", *pc, *pc);

	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v) = %X \n", &c, &pc, &v);

	printf("Adr(pc) = %X, Cont(pc) = %X, Adr(v) = %X \n", &pc, pc, &v);
	pc = &v[4]; //  pc = &v + 4
	printf("Adr(c) = %X, Adr(pc) = %X, Adr(v) = %X \n", &c, &pc, &v);
	printf("Adr(pc) = %X, Cont(pc) = %X, Adr(v) = %X \n", &pc, pc, &v);

	pc = (char*)malloc(c * sizeof(char));

	pc[4] = 'Y';
	printf("Adr(pc) = %X, Cont(pc) = %X, Adr(v) = %X \n", &pc, pc, &v);

	char * pv[10];

	for (int i = 0; i < 10; i++)
		pv[i] = &v[i];

	for (int i = 0; i < 10; i++)
		printf("Adr(pv) = %X, Adr(pv[i]) = %X, Cont(pv[i]) = %X\n", &pv, &pv[i], pv[i]);

	free(pc);

}