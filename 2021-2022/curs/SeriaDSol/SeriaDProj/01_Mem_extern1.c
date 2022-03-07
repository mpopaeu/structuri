#include "defs.h"
#include <stdio.h>

int i;

void main() {
	i = 3;

	f();
	printf("i = %d\n", i);
	f();
	printf("i = %d\n", i);
}