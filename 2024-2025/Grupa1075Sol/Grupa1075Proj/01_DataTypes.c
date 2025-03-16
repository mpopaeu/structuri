#include <stdio.h>
#include <malloc.h>

#define BYTEARRAY_SIZE 10
#define LINE_SIZE 6
#define COLUMN_SIZE 9

int main()
{
	char x = 65; // char x = 0x41; OR char x = 'A';
	unsigned char y = -2;

	float z = (float)65.64;

	char* p = NULL;
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	//printf("Content of pointed location p = %d \n", *p);

	p = &x; // write p with the stack memory address of x
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	p = (char*)malloc(1 * sizeof(char)); // heap memory allocation for one single char location
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	*p = x; // write content of x (65) over the memory pointed by p
	printf("Memory Address of location p = %p \n", &p);
	printf("Content of location p = %p \n", p);
	printf("Content of pointed location p = %d \n", *p);

	free(p); // deallocation of heap memory pointer by p

	p = (char*)malloc((BYTEARRAY_SIZE + 1)* sizeof(char)); // allocate a byte array
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		p[i] = x + i; // p[i] points to heap mem for the item having the offset i(same like compile-time allocated array)
	}
	p[BYTEARRAY_SIZE] = 0; // save the null byte right after the last item in the bytearray
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		printf("%d --> %c\n", p[i], p[i]);
	}

	printf("%s\n", p);
	free(p);

	char v[BYTEARRAY_SIZE + 1];
	p = v; // p contains the starting point (mem address) of the array v
	for (unsigned char i = 0; i < BYTEARRAY_SIZE; i++)
	{
		v[i] = x + i; 
	}
	v[BYTEARRAY_SIZE] = 0; // null byte terminator is put on the last item in array v
	printf("%s\n", p); // array y is printed out by using the pointer p

	char** pM = NULL;
	// matrix allocation
	pM = (char**)malloc(LINE_SIZE * sizeof(char*)); // allocation of the 1st level of the matrix in heap
	for (unsigned char i = 0; i < LINE_SIZE; i++)
	{
		pM[i] = (char*)malloc(COLUMN_SIZE * sizeof(char)); // allocation of line #i; hep memory address stored on intermediary level (pM[i])
	}

	// store relevant content over each matrix item accessed by pM[i][j]


	// matrix deallocation
	// deallocate the farest heap locations (the lines with the actual values)
	for (unsigned char i = 0; i < LINE_SIZE; i++)
	{
		free(pM[i]); // deallocate line #i
	}
	// deallocate the nearest heap location
	free(pM); // deallocate the intermediary array of addresses to the lines

	return 0;
}