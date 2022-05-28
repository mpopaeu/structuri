#include <stdio.h>
#include <malloc.h>
#include <string.h>

void main()
{
	FILE* f;

	f = fopen("Graf.txt", "r+");
	unsigned char** mat_adiacenta, nr_varfuri, vs, vd;

	fscanf(f, "%hhu", &nr_varfuri);
	// alocare matrice de adiacente (patratica); dimensiune: nr varfuri graf
	mat_adiacenta = (unsigned char**)malloc(nr_varfuri * sizeof(unsigned char*));
	for (unsigned char i = 0; i < nr_varfuri; i++)
		mat_adiacenta[i] = (unsigned char*)malloc(nr_varfuri * sizeof(unsigned char));

	// initializare elemente matrice de adiacenta
	for (unsigned char i = 0; i < nr_varfuri; i++)
		for (unsigned char j = 0; j < nr_varfuri; j++)
			mat_adiacenta[i][j] = 0;

	fscanf(f, "%hhu", &vs);
	while (!feof(f))
	{
		fscanf(f, "%hhu", &vd);
		mat_adiacenta[vs - 1][vd - 1] = 1;
		mat_adiacenta[vd - 1][vs - 1] = 1;

		fscanf(f, "%hhu", &vs);
	}
	fclose(f);


	printf("\nGraf reprezentat prin matrice de adiacenta:");
	for (unsigned char i = 0; i < nr_varfuri; i++)
	{
		printf("\n");
		for (unsigned char j = 0; j < nr_varfuri; j++)
			printf(" %hhu", mat_adiacenta[i][j]);
	}

	// traversare BF si DF 

	// dezalocare structuri dinamice
}