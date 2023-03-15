#include <stdio.h>
#include <malloc.h>

void add1(char x, char y, short int z) // transfer / pass parameters by values; 
									   // no change available outside the function
{
	x += 1;
	y -= 2;
	z = x + y + 1;
}

short int add2(char x, char y) // pass parameters by values; 
							   // result available through return
{
	x += 1;
	y -= 2;
	short int z = x + y + 1;

	return z;
}

void add3(char x, char y, short int* z)
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
}

int main()
{
	char a, b;
	short int c = 0;

	a = 11;
	b = 12;

	add1(a, b, c);
	printf("add1 c = %d\n", c); // c not changed

	c = add2(a, b);
	printf("add2 c = %d\n", c); // c overwritten by the value/result returned by the call to add2

	add3(a, b, &c);
	printf("add3 c = %d\n", c); // c changed from the function add3

	short int* pi = NULL;
	// add3(a, b, pi);
	// printf("add3 *pi = %d\n", *pi); // pi is sent as nullptr, then the computation cannot store result at nullptr
									   // pi is sent by value to the function add3

	add4(a, b, pi); // pi sent by value to add4; any change over pi will not be available outside the function add4
	// printf("add4 *pi = %d\n", *pi); // pi sent by value; runtime error because pi stays on nullptr
	
	pi = add5(a, b); // the heap memory address allocated inside add5 is returned back to the function main
					// and saved over location pi
	printf("add5 *pi = %d\n", *pi);
	free(pi);
	pi = NULL;

	add6(a, b, &pi); // pointer pi passed by address to the function; any change over *z (pi) will be seen here
	printf("add6 *pi = %d\n", *pi);

	free(pi);
	pi = NULL;

	return 0;
}