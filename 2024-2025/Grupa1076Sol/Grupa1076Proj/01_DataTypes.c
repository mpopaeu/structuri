#include <stdio.h>
#include <malloc.h>

#define BYTEARRAY_SIZE 10
#define LINE_SIZE 8
#define COLUMN_SIZE 10

int main()
{
	char x = 65;
	char y = -2;

	float z = 65.64;

	char* p = NULL;
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	//printf("Content pointed by p = %d\n", *p);

	p = &x; // write stack seg address over variable p
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	p = (char*)malloc(1 * sizeof(char)); // get heap seg address to store it over variable p
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	*p = x; // write actual content of x to memory location pointed by p
	printf("Stack memory address where p is allocated = %p\n", &p);
	printf("Content of p = %p\n", p);
	printf("Content pointed by p = %d\n", *p);

	free(p); // deallocate heap memory

	p = (char*)malloc((BYTEARRAY_SIZE + 1) * sizeof(char));

	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		p[i] = x + i;
	}
	p[BYTEARRAY_SIZE] = 0; // store the null terminator byte at the last allocated byte in the bytearray
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		printf("%d --> %c\n", p[i], p[i]);
	}

	printf("%s\n", p);

	free(p);

	char v[BYTEARRAY_SIZE + 1];
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		v[i] = x + i;
	}
	v[BYTEARRAY_SIZE] = 0;

	p = v;
	printf("%s\n", p);

	char M[10][9];
	char** pM = NULL;

	// step1: allocate the intermediary array of heap addresses of the lines
	pM = (char**)malloc(LINE_SIZE * sizeof(char*));
	// step2: allocate heap memory for the lines
	for (unsigned char i = 0; i < LINE_SIZE; i++)
	{
		pM[i] = (char*)malloc(COLUMN_SIZE * sizeof(char)); // starting heap address of line #i
	}

	// store actual values over the items pM[i][j]


	// deallocate the matrix in heap memory
	// step1: deallocate the farest heap locations (the lines with actual values)
	for (unsigned char i = 0; i < LINE_SIZE; i++)
	{
		free(pM[i]); // deallocate the line #i
	}
	// step2: deallocate the nearest location
	free(pM); // intermediary arrays of pointers to lines is deallocated

	return 0; 
}