#include <stdio.h>
#include <malloc.h>

#define NR_ELEMENTE 10

int main()
{
	char x = 65;
	char y = -2;

	float z = 65.64f;

	char* p_char = NULL;
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	//printf("Continut zona pointata de p_char = %d\n", *p_char); // eroare la run-time; adresa nu exista/incorecta

	p_char = &x; 
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char); // p_char[0] in loc de *p_char

	p_char = (char*)malloc(sizeof(char)); // alocare mem heap
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	p_char[0] = x; // *p_char = x;
	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	free(p_char); // dezalocare memorie heap

	printf("Adresa stack pointer p_char = %p\n", &p_char);
	printf("Continut pointer p_char = %p\n", p_char);
	printf("Continut zona pointata de p_char = %d\n", *p_char);

	p_char = (char*)malloc(NR_ELEMENTE * sizeof(char));
	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		p_char[i] = x + i;
	}
	for (unsigned char i = 0; i < NR_ELEMENTE; i++)
	{
		printf("%c --> %d\n", p_char[i], p_char[i]);
	}
	printf("\n");

	printf("%s\n", p_char);

	free(p_char);
	return 0;
}