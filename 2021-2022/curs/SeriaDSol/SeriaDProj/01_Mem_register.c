#include <stdio.h>


void main()
{
	register int vreg;
	int d;

	d = 8;
	vreg = d;

	printf("vreg inainte de __asm = %d\n", vreg);

	__asm
	{
		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
		add eax, vreg;
		add eax, 1;
		mov vreg, eax;
	};

	printf("vreg dupa de __asm = %d\n", vreg);
}