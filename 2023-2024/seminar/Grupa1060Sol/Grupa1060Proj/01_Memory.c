#include <stdio.h>
#include <malloc.h>

int main()
{
	char a;
	//a = 65;
	a = -65;
	unsigned char b = 66;

	printf("\"%c\" = %d | 0x%02X @adresa 0x%p\n", a, a, (unsigned char)a, &a);
	printf("\"%c\" = %d | 0x%02X @adresa 0x%p\n", b, b, b, &b);

	char* pa;
	pa = &a;
	printf("\"%c\" = %d\n", *pa, *pa);
	*pa = *pa + 1;
	printf("\"%c\" = %d\n", *pa, *pa);

	printf("StringStack(a) = %s\n", pa);

	pa = (char*)malloc(sizeof(b) + 1); // +1 pt byte cu rol de terminator de string (0x00)
	*pa = b;   // pa[0] = b;
	printf("StringHeap(a) Before = %s\n", pa);
	pa[1] = 0; // *(pa + 1) = 0; 
	printf("StringHeap(a) After = %s\n", pa);

	free(pa);
	printf("StringHeap(a) After free = %s\n", pa);
	pa = NULL;
	if(pa)
		printf("StringHeap(a) After NULL = %c\n", *pa);
	return 0;
}