#include <stdio.h>

int i = 2;

extern void f();
void g() {
	f();
	printf("i = %d\n", i);
}


void main() {
	i = 5;
	g();
	g();
	g();
	g();
}