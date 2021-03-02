#include <stdio.h>
#include <malloc.h>

int main()
{
	char x = 77; // var locala lui main(); alocat la compilare in stack seg; dimensiune = 1 byte = sizeof(char)
				// char x = 0x4D; char x = 'M';
				// [char, int], [float, double, long double]
	char vx[10]; // vector, alocat in stack seg la compilare (var locala); dimensiune = 10 * sizeof(char) = 10 bytes
				// elementele din vector au valori arbitrare (0xcc)
	char *px = NULL; // variabila locala, alocata la compilare in stack seg; dimensiune = sizeof(px) = sizeof(char*) = 4 bytes
					// variabila pointer, de tip FAR seg:off (alternativa: NEAR)

	// incarc px cu adresa de stack seg a lui x
	px = &x;
	*px = x + 4; // modificare indirecta a lui x

	// incarc adresa de inceput a vectorului vx in variabila pointer px
	px = vx;

	for (char i = 0; i < sizeof(vx); i++)
		px[i] = x + i; // acces indirect la elementul cu offset i in vectorul vx
						// px[i] <--> *(px + i)

	// alocare (incarc adresa) de memorie heap
	char n = sizeof(vx) - 3;

	px = (char*)malloc(n * sizeof(char));

	for (char i = 0; i < n; i++)
		px[i] = vx[i] + i;


	// dezalocare mem heap
	free(px);
	px = NULL;

	if(px)
		*px = x + 10;


	return 0;
}