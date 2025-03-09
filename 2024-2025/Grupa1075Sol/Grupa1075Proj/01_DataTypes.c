#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 65; // char x = 0x41; OR char x = 'A';
	unsigned char y = -2;

	float z = (float)65.64;

	char* p = NULL;
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	//printf("Content of pointed location p = %d \n", *p);

	p = &x;
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	p = (char*)malloc(1 * sizeof(char));
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	*p = x;
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	free(p);

	return 0;
}