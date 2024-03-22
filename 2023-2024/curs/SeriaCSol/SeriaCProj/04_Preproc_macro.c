#include <stdio.h>

#define SUMA_GEN(NUME,TIP) TIP NUME(TIP vb1, TIP vb2) \
{ return vb1 + vb2; }

#define INTREG 1
#define REAL 2

#ifdef INTREG
SUMA_GEN(sumai, int)
#endif

#ifdef REAL
SUMA_GEN(sumaf, float)
#endif

int main()
{
#if defined(INTREG) && INTREG
	int x = 7, y = 9, z;
	z = sumai(x, y);
#endif


#if defined(REAL) && REAL
	float a = 7.8f, b = 9.5f, c;
	c = sumaf(a, b);
#endif


	//#undef REAL
	// #define REAL 0
#if defined(INTREG) && INTREG
	printf("\nz = %d", z);
#endif
#if defined(REAL) && REAL
	printf("\nc = %.2f", c);
#endif

	return 0;
}
