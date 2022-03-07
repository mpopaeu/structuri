#include <stdio.h>

void main()
{
	register int vreg;
	int d;

	d = 8;
	vreg = d;

	printf("vreg = %d\n", vreg);

	__asm
	{
		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
		add eax, vreg;
		mov vreg, eax;
	};

	printf("vreg = %d\n", vreg);
}