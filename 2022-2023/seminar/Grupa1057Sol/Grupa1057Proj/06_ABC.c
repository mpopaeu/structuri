#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 30
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[25];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct NodABC
{
	unsigned int cheie;
	struct ContBancar cb;
	struct NodABC *st, *dr ;
};


struct NodABC* inserare_NodABC(struct NodABC* r, struct ContBancar cont_bancar, 
							   unsigned int key, unsigned char* er)
{
	if (r == NULL) {
		struct NodABC* nou = (struct NodABC*)malloc(sizeof(struct NodABC));
		nou->dr = NULL;
		nou->st = NULL;
		nou->cheie = key;
		nou->cb = cont_bancar;
		r = nou;
	}
	else if (r->cheie == key) *er = 1;
	else if (r->cheie > key)
		r->st = inserare_NodABC(r->st, cont_bancar, key, er);
	else
		r->dr = inserare_NodABC(r->dr, cont_bancar, key, er);
	return r;
}

void traversare_inordine(struct NodABC * r)
{
	if (r)
	{
		traversare_inordine(r->st);
		printf(" %u ", r->cheie);
		traversare_inordine(r->dr);
	}
}

void calcul_noduri_niveluri(struct NodABC *r, unsigned int nivel, unsigned int *nr)
{
	// traversare in preordine a nodurilor din ABC in vederea validarii pozitiei pe nivel
	// numerotare niveluri de la 1 (radacina ABC este pe nivelul 1)
	if (r)
	{
		if (nivel == 1) *nr += 1; // nr salturi in ABC mai mic cu 1 fata de nivel targetat
		else
		{
			calcul_noduri_niveluri(r->st, nivel - 1, nr);
			calcul_noduri_niveluri(r->dr, nivel - 1, nr);
		}
	}
}

// stergere nod in ABC
struct NodABC* stergere_nod_ABC(struct NodABC* r, unsigned int k, struct ContBancar* cont_bancar)
{
	if (r)
	{
		if (r->cheie == k)
		{
			// nodul de sters a fost identificat
			*cont_bancar = r->cb;
			if (r->st && r->dr)
			{
				// nod cu 2 descendenti
			}
			else
			{
				if (!r->st && !r->dr)
				{
					// nod frunza
				}
				else
				{
					// nod cu 1 descendent
				}
			}
		}
		else
		{
			// continui cautarea
			if (k < r->cheie)
				r->st = stergere_nod_ABC(r->st, k, cont_bancar);
			else
				r->dr = stergere_nod_ABC(r->dr, k, cont_bancar);
		}
	}
}

int main()
{

	struct ContBancar cb;
	FILE* f;

	f = fopen("Conturi_ABC.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

	struct NodABC* root = NULL; // variabila pentru gestionare arbore binar de cautare
	unsigned int k = 0; // variabila locala pentru stocare temporara a cheii

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token;


		token = strtok(buffer, seps);
		k = (unsigned int)atoi(token);
		
		token = strtok(NULL, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1); // +1 pentru terminat de string, adica byte 0x00
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		strcpy(cb.moneda, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		cb.nr_carduri = atoi(token);

		// inserare cont bancar cb in tabela hash cu chaining
		unsigned char err = 0;
		root = inserare_NodABC(root, cb, k, &err);
		if (err)
			printf("Nodul cu cheia %u nu a fost inserat\n", k);
	}
	fclose(f);

	printf("Arborele dupa creare: ");
	traversare_inordine(root);

	// determinare numar de noduri de pe nivel specificat in ABC
	unsigned int nr_niveluri = 0;
	calcul_noduri_niveluri(root, 2, &nr_niveluri);
	printf("\n\nNumar de noduri de pe nivel specificat = %u\n", nr_niveluri);

	// stergere nod in ABC

	// dezalocare ABC

	printf("\n\n");
}