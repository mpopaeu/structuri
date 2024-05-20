#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define HTABLE_SIZE 200

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

struct NodABC
{
	unsigned short int cheie;
	struct ContBancar data;
	struct NodABC* st, *dr;
};


typedef struct ContBancar ContBancar;
typedef struct NodABC NodABC;

NodABC* inserare_nod_arbore(NodABC* r, ContBancar contB, 
						unsigned short int key, unsigned char* flag)
{
	if (r != NULL)
	{
		if (key < r->cheie)
		{
			r->st = inserare_nod_arbore(r->st, contB, key, flag);
		}
		else
		{
			if (key > r->cheie)
			{
				r->dr = inserare_nod_arbore(r->dr, contB, key, flag);
			}
			else
			{
				*flag = 0; // flag setat pe ESEC!
			}
		}
	}
	else
	{
		// locul unde nodul nou se insereaza
		NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
		nou->cheie = key;
		nou->data = contB;
		nou->st = NULL;
		nou->dr = NULL;

		*flag = 1; // flag setat pe SUCCES!
		r = nou;
	}

	return r;
}

void inordine(NodABC* r)
{
	if (r)
	{
		inordine(r->st);
		printf("%d ", r->cheie);
		inordine(r->dr);
	}
}

NodABC* dezalocareABC(NodABC* r)
{
	if (r != NULL)
	{
		r->st = dezalocareABC(r->st);
		r->dr = dezalocareABC(r->dr);

		free(r->data.titular); // dezalocare titular din nodul curent r
		free(r);			// dezalocare nod curent r

		r = NULL;
	}

	return r;
}

ContBancar* cauta_cb_cheie(NodABC *r, unsigned short int cheie_cautata)
{
	if (r)
	{
		if (r->cheie > cheie_cautata)
		{
			return cauta_cb_cheie(r->st, cheie_cautata);
		}
		else
		{
			if (r->cheie < cheie_cautata)
			{
				return cauta_cb_cheie(r->dr, cheie_cautata);
			}
			else
			{
				// cont bancar identificat in ABC
				return &(r->data);
			}
		}
	}
	return NULL;
}

unsigned short int nr_noduri_titular(NodABC* r, char* nume)
{
	unsigned short int count = 0;

	if (r != NULL)
	{
		if (strcmp(nume, r->data.titular) == 0)
		{
			count += 1;
		}
		count += nr_noduri_titular(r->st, nume);
		count += nr_noduri_titular(r->dr, nume);
	}

	return count;
}


void init_vector(NodABC* r, char* nume, unsigned short int v[], unsigned short int* offset)
{

	if (r != NULL)
	{
		if (strcmp(nume, r->data.titular) == 0)
		{
			v[*offset] = r->cheie;
			*offset += 1;
		}
		init_vector(r->st, nume, v, offset);
		init_vector(r->dr, nume, v, offset);
	}
}

unsigned short int* v_chei_titular(NodABC* r, char* nume, unsigned short int *vector_size)
{
	*vector_size = nr_noduri_titular(r, nume);
	if (*vector_size != 0)
	{
		unsigned short int* vector = (unsigned short int*)malloc((*vector_size) * sizeof(unsigned short int));
		unsigned short int offset = 0;
		init_vector(r, nume, vector, &offset);
		return vector;
	}
	else
	{
		return NULL;
	}
}

int main()
{
	FILE* f = fopen("ConturiABC.txt", "r");
	NodABC* root = NULL; // arbore binar de cautare empty
	unsigned short int key;
	char nume_buff[128];

	struct ContBancar contB;
	fscanf(f, "%hu", &key);
	while (key != 0)
	{
		fscanf(f, "%s\n", contB.iban);

		fscanf(f, "%[^\n]", nume_buff);
		contB.titular = (char*)malloc(strlen(nume_buff) + 1);
		strcpy(contB.titular, nume_buff);

		fscanf(f, "%s", contB.moneda);
		fscanf(f, "%f", &contB.sold);

		// inserare cont bancar in arbore binar de cautare
		unsigned char inserat = 0;
		root = inserare_nod_arbore(root, contB, key, &inserat);
		if (inserat != 0)
		{
			contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
			contB.iban[0] = 0;
		}
		else
		{
			// contul bancar nu a fost inserat in ABC
			free(contB.titular); // dezalocare mem heap pt titular
		}
		key = 0; // reinitializare cheie pentru a verifica existenta urmatorului cont bancar in fisier

		fscanf(f, "%hu", &key);
	}

	printf("Arbore dupa creare: ");
	inordine(root);
	printf("\n\n");

	// cautare cont bancar dupa cheie
	ContBancar* p_contB = NULL;
	p_contB = cauta_cb_cheie(root, 61);
	if (p_contB != NULL)
	{
		printf("Cont bancar identificat: %s %s\n", p_contB->iban, p_contB->titular);
	}
	else
	{
		printf("Contul bancar nu exista in ABC.\n");
	}

	// cautare cont bancar dupa titular
	unsigned short int nr_chei_titular = 0;
	unsigned short int* vector = v_chei_titular(root, "Popescu Iulian", &nr_chei_titular);
	if (vector != NULL)
	{
		printf("Lista de conturi bancare identificate cu titular cautat: ");
		for (unsigned short int i = 0; i < nr_chei_titular; i++)
		{
			printf("%u ", vector[i]);
		}
		printf("\n\n");
	}
	else
	{
		printf("Nu exista noduri cu titular cautat in ABC!\n\n");
	}

	// dezalocare ABC
	root = dezalocareABC(root);
	printf("Arbore dupa dezalocare: ");
	inordine(root);
	printf("\n\n");

	// dezalocare vector
	free(vector);

	fclose(f);
	return 0;
}