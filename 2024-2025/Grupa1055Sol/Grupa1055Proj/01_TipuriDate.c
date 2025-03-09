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
	*pc = y; // pc[0] = y; *(pc+0) = y
	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	printf("Valoare la destinatie *pc = %d\n", *pc);

	free(pc);
	pc = (char*)malloc(NR_ELEMENTE_VECTOR * sizeof(char));
	for (unsigned char i = 0; i < NR_ELEMENTE_VECTOR; i++)
	{
		pc[i] = (char)(x + i);
	}
	printf("Adresa stack pc = %p\n", &pc);
	printf("Continut pc = %p\n", pc);
	for (unsigned int i = 0; i < NR_ELEMENTE_VECTOR; i++)
	{
		printf("%c --> %d\n", pc[i], pc[i]);
	}
	printf("\n");

	printf("%s\n", pc);

	free(pc);
	return 0;
}