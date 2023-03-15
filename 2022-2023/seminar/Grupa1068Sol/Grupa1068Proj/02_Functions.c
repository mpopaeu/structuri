#include <stdio.h>
#include <malloc.h>

void add1(char x, char y, short int z) // passing parameters by value
{
	x += 1;
	y -= 2;
	z = x + y + 1;
}

short int add2(char x, char y) // passing parameters by value
{
	x += 1;
	y -= 2;
	short z = x + y + 1;
	
	return z;
}

void add3(char x, char y, short int * z) // x, y passed by value, z passed by its memory address
{
	x += 1;
	y -= 2;

	*z = x + y + 1;
}


void add4(char x, char y, short int* z) 
{
	x += 1;
	y -= 2;
	z = (short int*)malloc(sizeof(short int));
	*z = x + y + 1;
}

short int* add5(char x, char y)
{
	x += 1;
	y -= 2;
	short int* z = (short int*)malloc(sizeof(short int));
	*z = x + y + 1;

	return z;
}

void add6(char x, char y, short int* *z)
{
	x += 1;
	y -= 2;
	*z = (short int*)malloc(sizeof(short int));
	**z = x + y + 1;

	return z;
}

int main()
{
	char a, b;
	short c = 0;

	a = 11;
	b = 12;

	add1(a, b, c);
	printf("add1 c = %d\n", c); // c keeps the content before the call to add1

	c = add2(a, b);
	printf("add2 c = %d\n", c); // right result expected

	c = 0;
	add3(a, b, &c);
	printf("add3 c = %d\n", c); // right result expected

	short int* pi = NULL;
	// add3(a, b, pi); // passing parameter pi by its value; cannot be called for pi == NULL

	add4(a, b, pi); // pi passed by value; change of pi within the function will not be available here
	if(pi) // check if pi is not NULL
		printf("add4 *pi = %d\n", *pi); // crash expected without previous if statement

	// &c = (short int*)malloc(sizeof(short int));

	pi = add5(a, b);
	printf("add5 *pi = %d\n", *pi); // right result expected
	free(pi);
	pi = NULL;

	add6(a, b, &pi);
	printf("add6 *pi = %d\n", *pi); // right result expected
	free(pi);
	pi = NULL;

	add6(a, b, &pi);
	printf("add6 *pi = %d\n", *pi); // right result expected
	free(pi);
	pi = NULL;
}