#include <stdio.h>

int main()
{

	int v[10][20]; // v este pointer la zona de memorie contingua alocata pt elementele matricei

	char* p = NULL;

	v[0][1] = 0;
	//v[-2][-3] = 0;
	//v[11][2] = 0;

	char i = 65;
	p = &i;

	//p[-2] = 0;

	//// pointer constant la char
	//int j = 9;
	//char* const pi = &i;
	//printf("\nAdresa(pi) = %p, Continut(pi) = %p\n", &pi, pi);
	////pi = &j;

	//// pointer la char constant
	//char const* pint;
	//pint = &i;
	//printf("\nAdresa(pint) = %p, Continut(pint) = %p\n", &pint, pint);
	////*pint = i + 5;
	//printf("\nContinut(i) = %d\n", i);

	// pointer constant la char constant
	const char* const pint2 = &i; 	
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);
	//*pint2 = i + 5;
	printf("\nAdresa(pint2) = %p, Continut(pint2) = %p\n", &pint2, pint2);


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
