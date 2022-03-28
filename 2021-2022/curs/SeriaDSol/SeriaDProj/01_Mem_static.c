#include <stdio.h>

int f() {
	static int x = 0;
	x++;
	return x;
}

void main() {
	int j;
	for (j = 0; j < 10; j++) {
		printf("Rezultat functie f: %d\n", f());
	}
}