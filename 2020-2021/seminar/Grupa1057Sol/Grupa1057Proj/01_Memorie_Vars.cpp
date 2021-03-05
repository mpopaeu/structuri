#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 'a'; // tipuri de date standard: [char, int,] [float, double, long double]
					// x variabila locala, de lungime 1 byte; se aloca in stack seg
	char vx[10]; // vector; vx variabila locala, se aloca la compilare in stack seg
	char *px = NULL; // px variabila locala, se aloca in stack seg; implicit este pointer FAR --> seg:off

	px = &x; // incarc adresa de stack seg al lui x in px
	*px = x + 3; // modificarea lui x in mod indirect din px;  *(px + 0) 

	px = vx; // incarc adresa de stack seg al lui vx in px
	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // px[i] <--> *(px + i) 

	// incarc adresa de mem heap in px
	char n = sizeof(vx) - 4;
	px = (char*)malloc(n * sizeof(char));

	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;

	// dezaloc mem heap
	free(px);
	px = NULL;

	if(px != NULL)
		px[0] = px[0] + 3;

	//////////////////////////////////////

	int z = 0x1122bacd;

	unsigned char *pz; // mapare pz peste z

	pz = (unsigned char *)&z;

	pz[2] = 0x33;

	for (char i = sizeof(int) - 1; i >= 0 ; i--)
		printf(" %02X ", pz[i]);
	printf("\n");

	return 0;
}