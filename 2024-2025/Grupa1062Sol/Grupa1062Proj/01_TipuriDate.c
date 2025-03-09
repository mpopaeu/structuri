#include <stdio.h>
#include <malloc.h>

#define NR_ELEMENTE 10

int main()
{
	char x = 65;
	char y = -2;

	float z = (float)65.64;

	char* p_char = NULL;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	//printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = &x;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = (char*)malloc(sizeof(char));
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char[0] = x;
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	free(p_char);
	printf("Adresa stack seg pentru p_char = %p\n", &p_char);
	printf("Continut pentru p_char = %p\n", p_char);
	printf("Valoare accesata prin pointer p_char = %d\n", *p_char);

	p_char = malloc(NR_ELEMENTE * sizeof(char));

	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		p_char[i] = x + i;
	}
	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		printf("%d --> %c\n", p_char[i], p_char[i]);
	}

	printf("%s\n", p_char);

	return 0;
}