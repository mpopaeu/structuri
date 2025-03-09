#include <stdio.h>
#include <malloc.h>


int main()
{
	char x = 65;
	char y = -2;

	float z = 65.64;

	char* p = NULL;
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	//printf("Content pointed by p = %d\n", *p);

	p = &x;
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	p = (char*)malloc(1 * sizeof(char));
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	*p = x;
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	free(p);
	return 0; 
}