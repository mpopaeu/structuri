#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 103; // [char, int,] [float, double, long double]
				  // echivalent cu char x = 0x67; char x = 'g';
				  // se aloca la compilare sizeof(char) bytes (1 byte) --> var locala lui main()
	char vx[10];	// vector de elemente de tip char; sunt alocate 10 elemente la compilare (10 * sizeof(char) bytes = 10 bytes)
					// var locala lui main()
	char *px = NULL; // variabila de tip pointer; var locala lui main(), se aloca la compilare (stack seg)
					// se aloca sizeof(px) bytes = 4 bytes: px este FAR seg:off
	
	px = &x; // incarc adresa de stack seg a lui x
	*px = x + 3; // modific locatia x in mod indirect

	px = vx; // incarc adresa de stack seg a lui vx
	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // px[i] <--> *(px + i)

	// alocarea la run-time
	char n = sizeof(vx) - 2;
	px = (char*)malloc(n * sizeof(char));

	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;

	// dezalocare mem heap
	free(px);
	px = NULL;

	if(px != NULL)
		*px = 0x11;

	////////////////////////////

	int z = 0xA511DD80;
	unsigned char *pz = NULL;

	pz = (unsigned char*)&z;

	// BIG ENDIAN
	for (char i = 0; i < sizeof(int); i++)
		printf(" %02X ", pz[i]);
	printf("\n");

	// LITTLE ENDIAN ***
	for (char i = sizeof(int) - 1; i >= 0; i--)
		printf(" %02X ", pz[i]);
	printf("\n");

	pz[2] = 0x89; // modific byte-ul cu offset 2 in 0x89 (continutul anterior este 0x11, byte-ul 2 din initializarea lui z)
				  // LITTLE ENDIAN ***
	for (char i = sizeof(int) - 1; i >= 0; i--)
		printf(" %02X ", pz[i]);
	printf("\n");

	return 0;
}