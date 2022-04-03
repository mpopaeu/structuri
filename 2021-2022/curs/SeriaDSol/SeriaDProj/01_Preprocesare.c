//
//#include <stdio.h>
//
//#define SUMA_GEN(NUME,TIP) TIP NUME(TIP vb1, TIP vb2) \
//{ return vb1 + vb2; }
//
//#define INTREG
//// #define REAL
//
//#ifdef INTREG
//SUMA_GEN(sumai, int)
//#endif
//
//#define REAL
//#ifdef REAL
//SUMA_GEN(sumaf, float)
//#endif
//
//void main()
//{
//#ifdef INTREG
//	int x = 7, y = 9, z;
//	z = sumai(x, y);
//#endif
//
//
//#ifdef REAL
//	float a = 7.8f, b = 9.5f, c;
//	c = sumaf(a, b);
//#endif
//
//
//// #undef REAL
//#ifdef INTREG
//	printf("\nz = %d", z);
//#endif
//#ifdef REAL
//	printf("\nc = %.2f", c);
//#endif
//}


#include <stdio.h>

#define BRANCH 1

void main()
{

	int x = 7, y = 9, z;
	z = x + y;

#if BRANCH == 1
	float a = 7.8f, c;
	c = a + z;
#else
	int a = -9, c;
	c = a - z;
#endif

#if BRANCH == 1
	printf("\n c = %f", c);
#else
	printf("\n c = %d", c);
#endif
}