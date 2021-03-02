#include <stdio.h>

int i = 2;

extern void f();

//void f() {
//	//.... 
//}

void g() {
	f();
	printf("i = %d\n", i);
}


int main() {
	i = 5;
	g();

	return 0;
}