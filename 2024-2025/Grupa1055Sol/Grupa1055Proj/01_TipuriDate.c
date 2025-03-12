#include <stdio.h>
#include <malloc.h>

#define NR_ELEMENTE 1
#define NR_ELEMENTE_VECTOR 10

int main()
{
	char x = 65;
	char y = -2;
	float z = (float)65.64;

	printf("x = %d, y = %d, z = %f\n", x, y, z);
	printf("x = %c, y = %d, z = %f\n", x, y, z);

	char* pc = NULL; // pc = 0;
	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	//printf("Valoare la destinatie *pc = %d\n", *pc); // nu se acceseaza continut de la adresa nula

	pc = &x;
	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	printf("Valoare la destinatie *pc = %d\n", *pc); 
	printf("Valoare la destinatie *pc = %d\n", pc[0]); 

	pc = (char*) malloc(NR_ELEMENTE * sizeof(char));
	*pc = y; // pc[0] = y; *(pc + 0) = y
	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	printf("Valoare la destinatie *pc = %d\n", *pc);

	free(pc);
	pc = (char*)malloc((NR_ELEMENTE_VECTOR + 1) * sizeof(char));
	for (unsigned char i = 0; i < NR_ELEMENTE_VECTOR; i++)
	{
		pc[i] = (char)(x + i);
	}
	pc[NR_ELEMENTE_VECTOR] = 0; // scrierea terminatorului de string pe ultimul byte din vector = 0x00

	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	for (unsigned int i = 0; i < NR_ELEMENTE_VECTOR; i++)
	{
		printf("%c --> %d\n", pc[i], pc[i]); // asociere simbol ASCII --> cod ASCII
	}
	printf("\n");

	printf("%s in memorie heap\n", pc);

	free(pc);

	char v[NR_ELEMENTE_VECTOR + 1];
	pc = v;
	for (unsigned char i = 0; i < NR_ELEMENTE_VECTOR; i++)
	{
		v[i] = (char)(x + i);
	}
	v[NR_ELEMENTE_VECTOR] = 0;
	printf("v = %s in memorie stack\n", pc);
	
	return 0;
}