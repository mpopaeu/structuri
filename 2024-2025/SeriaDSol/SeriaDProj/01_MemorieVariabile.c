#include <stdio.h>

int main()
{

	int v[10][20]; // v este pointer la zona de memorie contingua alocata pt elementele matricei

	char* p = NULL;

	v[-2][-6] = 0;
	v[16][28] = 0;

	char i = 65;
	p = &i;

	p[-29] = 0;

	return 0;
}


//int main()
//{
//	register int vreg;
//	int d;
//
//	d = 8;
//	vreg = d;
//
//	printf("vreg = %d\n", vreg);
//
//	__asm
//	{
//		mov eax, vreg; // incarca registrul EAX cu continutul lui vreg
//	};
//
//}
