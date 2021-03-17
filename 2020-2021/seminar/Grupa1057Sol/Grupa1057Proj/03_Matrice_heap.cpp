#include <malloc.h>
#include <stdio.h>

#define INSERARE 1
#define STERGERE 2

unsigned char op_mat_elem(int ** &pMat, unsigned char * &dim_linii, unsigned char nr_linii, 
							int val_elem, unsigned char op_linie, char op_tip)
{
	// pMat - matricea cu date care are o evolutie dinamica la nivel de structura (linii/coloane)
	// dim_linii - vector cu dimensiuni efective de linii din matricea pMat
	// nr_linii - nr de linii al matricei; identic cu nr de elemenete din dim_linii
	// val_elem - valoare element care se insereaza in matrice; este ignorat in cazul operatiei de STERGERE
	// op_linie - nr de linie (NU offset) pe care se aplica operatia de INSERARE / STERGERE; 
	// op_tip - tipul operatiei: INSERARE / STERGERE
	// return:  - (nou) nr de linii pMat si elemente in dim_linii
	//			- pMat modificat la nivel de linii 
	//			- dim_linii modificat ca nr de elemente

	if (op_tip == INSERARE)
	{
		// inserare/adaugare element in matricea pMat pe ultima pozitie pe linia op_linie
		if (op_linie > 0 && op_linie <= (nr_linii + 1))
		{
			if (op_linie == (nr_linii + 1))
			{
				// se adauga linie la matrice pMat; val_elem va fi primul si unicul element de pe noua linie
				// realocarea vectorului cu adrese de linii pt linia aditionala inclusa in matrice
				// alocare vector cu elementul inserat pe ultima linie din matrice

				// realocare matrice de intregi (la nivel de structura intermediara - vector de pointeri la linii)
				int ** nAdreseLinii = (int **)malloc((nr_linii + 1) * sizeof(int*)); // alocare vector nou pt stocare adrese inceput linii
				for (unsigned char i = 0; i < nr_linii; i++)
					nAdreseLinii[i] = pMat[i]; // copiere adrese de linii din pMat in vectorul nou pt cele nr_linii existente in pMat
				nAdreseLinii[nr_linii] = (int*)malloc(1 * sizeof(int)); // alocare linie nr_linii + 1
				nAdreseLinii[nr_linii][0] = val_elem; // elementul se adauga pe ultima linie

				// dezalocare vector "vechi"/sursa adrese de linii 
				free(pMat);
				pMat = nAdreseLinii; // noua adresa stocata de pMat unde se afla nr_linii + 1 adrese inceput de linii

				// realocare vector cu nr elemente pe fiecare linie
				unsigned char* nVectorDimLinii = (unsigned char*)malloc((nr_linii + 1) * sizeof(unsigned char)); // alocare vector nou
				for (unsigned char i = 0; i < nr_linii; i++)
					nVectorDimLinii[i] = dim_linii[i]; // dim linie i copiata in noul vector
				nVectorDimLinii[nr_linii] = 1; // dimensiune noua linie adaugata la matrice

				// dealocare vector "vechi"/sursa cu nr elemente pe linii ale matrice pMat
				free(dim_linii);
				dim_linii = nVectorDimLinii; // actualizare pointer catre noul vector de dim de linii

				// actualizare nr de linii matrice
				nr_linii += 1;
			}
			else 
			{
				// se adauga element pe linia op_linie; creste nr de elemente de pe linia op_linie
				// val_elem se adauga la sfarsitul liniei op_linie
				// se realoca linia op_linie pt un elem suplimentar
				unsigned char offs_op_linie = op_linie - 1; 

				int* nVectorElemLinie = (int*)malloc((dim_linii[offs_op_linie] + 1) * sizeof(int)); // alocae vector nou pentru elemente dupa inserare lui val_elem
				for (unsigned char i = 0; i < dim_linii[offs_op_linie]; i++)
					nVectorElemLinie[i] = pMat[offs_op_linie][i]; // element din pMat (linia op_linie) copiat in noul vector de elemente
				nVectorElemLinie[dim_linii[offs_op_linie]] = val_elem; // adaugare nou element intreg pe linia op_linie

				free(pMat[offs_op_linie]); // dezalocare linie "veche"/sursa
				pMat[offs_op_linie] = nVectorElemLinie; // rescriere pointer la linia op_linie cu adresa vectorului de elemente extins cu val_elem

				// actualizare nr elemente de pe linia op_linie pe care s-a efectuat inserarea
				dim_linii[offs_op_linie] += 1;
			}
		}
	}
	else
	{
		if (op_tip == STERGERE)
		{
			// stergere ultim element de pe linia op_linie
			if (op_linie > 0 && op_linie <= nr_linii)
			{
				unsigned char offs_op_linie = op_linie - 1;
				if (dim_linii[offs_op_linie] >= 2)
				{
					// nu are loc modificare nr de linii in matricea pMat
					// realocare vector de elemente (linia cu elemente) pe dim_linii[offs_op_linie] - 1
					int* nVectorElemLinie = (int*)malloc((dim_linii[offs_op_linie] - 1) * sizeof(int)); // alocare nou vector de elemente pt linia op_linie

					// se copiaza primele dim_linii[offs_op_linie] - 1 in noua linie
					for (unsigned char i = 0; i < (dim_linii[offs_op_linie] - 1); i++)
						nVectorElemLinie[i] = pMat[offs_op_linie][i];

					// se dezaloca linia "veche"/sursa op_linie unde are loc stergerea
					free(pMat[offs_op_linie]);

					// se rescrie pointerul de linie pMat[offs_op_linie] cu adresa noului vector
					pMat[offs_op_linie] = nVectorElemLinie;

					// se actualizeaza valoare (nr elemente linie op_linie) in dim_linii[offs_op_linie]
					dim_linii[offs_op_linie] -= 1;
				}
				else
				{
					// eliminare linie op_linie din matricea pMat
					// realocare vectorul de pointeri pMat pe noua dimensiune: nr_linii - 1

					// se copiaza in noul vector adresele de linii cu exceptia adresei pMat[offs_op_linie]
					
					// dezalocare vector "vechi"/sursa cu pointeri la linie

					// actualizare pMat catre nou vector cu pointeri la linie

					// realocare dim_linii pe noua dimensiune: nr_linii - 1

					// se copiaza vechile dimensiuni in nou vector, cu exceptia dim_linii[offs_op_linie]

					// dezalocare vector "vechi"/sursa dim_linii

					// actualizare dim_linii pe vectorul nou de dimensiuni (nr elem pe fiecare linie din matrice)

					// actualizare nr_linii
					nr_linii -= 1;
				}
			}
		}
	}

	return nr_linii;
}

void afisare_matrice(int** pMat, unsigned char m, unsigned char* dim_linii)
{
	printf("\n");
	for (unsigned char i = 0; i < m; i++)
	{
		for (unsigned char j = 0; j < dim_linii[i]; j++)
			printf(" %d ", pMat[i][j]);
		printf("\n");
	}
}

int main()
{
	int ** pMat;
	unsigned char m = 3, n = 2; // m linii, n coloane

	// alocare matrice in mem heap
	pMat = (int**)malloc(m * sizeof(int*)); // alocare vector de adrese de inceput a liniilor
	for (unsigned char i = 0; i < m; i++)
		pMat[i] = (int*)malloc(n * sizeof(int)); // alocare vector cu valori ale liniei i

	// incarcare matrice cu valori
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			pMat[i][j] = i * 10 + (j + 1);

	/*
	pMat
		1   2
		11 12 13
		31
	*/
	unsigned char* dim_linii = (unsigned char*)malloc(m * sizeof(unsigned char)); // fiecare element i corespunde unei linii i din pMat
	for (unsigned char i = 0; i < m; i++)
		dim_linii[i] = n; // nr initial de elemente pe fiecare linie

	int Mat[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

	// TEMA - implementare operatii de INSERARE si STERGERE

	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 101, m + 1, INSERARE); // extindere la 4 linii
	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 102, m - 1, INSERARE); // adaugare pe linia 3
	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 103, m + 1, INSERARE); // extindere la 5 linii
	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 104, m + 4, INSERARE); // nu are loc inserare element 104 in matrice
	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 103, 1, STERGERE); // stergere (ultim element) pe linia 1 
	afisare_matrice(pMat, m, dim_linii);
	m = op_mat_elem(pMat, dim_linii, m, 103, 3, STERGERE); // stergere (ultim element) pe linia 1 
	afisare_matrice(pMat, m, dim_linii);



	// dezalocare matrice
	for (unsigned char i = 0; i < m; i++)
		free(pMat[i]);
	free(pMat);

}