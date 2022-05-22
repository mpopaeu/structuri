#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct ArbBin
{
	struct Angajat ang;
	struct ArbBin* stanga, *dreapta;
};

struct Nod
{
	struct Angajat* pang;
	struct Nod* next;
};

struct Nod* inserare_inceput(struct Nod* list, struct Angajat *a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->pang = a;
	nou->next = list;

	return nou;
}

struct ArbBin* inserare_arbore(struct ArbBin *r, struct Angajat a, unsigned char *flag_inserare)
{
	if (r)
	{
		// se continua cautarea locului de inserat
		if (r->ang.cod > a.cod)
			r->stanga = inserare_arbore(r->stanga, a, flag_inserare);
		else
			if (r->ang.cod < a.cod)
				r->dreapta = inserare_arbore(r->dreapta, a, flag_inserare);
			else
				*flag_inserare = 0; // se abandaoneaza operatia de inserare
		return r;
	}
	else
	{
		// am gasit locul de inserat
		struct ArbBin* nou = (struct ArbBin*)malloc(sizeof(struct ArbBin));
		nou->ang = a;
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*flag_inserare = 1;

		return nou;
	}
}

void inordine(struct ArbBin* r)
{
	if (r)
	{
		inordine(r->stanga);
		printf("\n\t%hu %s", r->ang.cod, r->ang.nume);
		inordine(r->dreapta);
	}
}

struct ArbBin* dezalocare_arbore(struct ArbBin* r)
{
	if (r)
	{
		r->stanga = dezalocare_arbore(r->stanga);
		r->dreapta = dezalocare_arbore(r->dreapta);

		free(r->ang.nume);
		free(r);			
	}
	return NULL;
}

// [in] r - nod (curent - pe care se efectueaza prelucrari) in arbore
// [in] nivel - nivelul pentru care se calculeaza nr noduri
// [out] nr_noduri - nr de noduri de pe nivelul nivel
void nr_noduri_nivel(struct ArbBin* r, unsigned char nivel, unsigned int *nr_noduri)
{
	if (r)
	{
		if (nivel == 1)
		{
			// r este plasat pe nivelul pentru care se calculeaza nr noduri
			*nr_noduri += 1;
		}
		else
		{
			nr_noduri_nivel(r->stanga, nivel - 1, nr_noduri);
			nr_noduri_nivel(r->dreapta, nivel - 1, nr_noduri);
		}
	}
}

// [in] r - nod (curent - pe care se efectueaza prelucrari) in arbore
// [in] nivel - nivelul pentru care se calculeaza nr noduri
// [out] list - lista simpla cu adrese (din arbore) angajati plasati pe acelasi nivel in arbore
void creare_lista_nivel(struct ArbBin* r, unsigned char nivel, struct Nod* *list)
{
	if (r)
	{
		if (nivel == 1)
		{
			// r este plasat pe nivelul pentru care se salveaza adresa angajat in lista
			*list = inserare_inceput(*list, &r->ang);
		}
		else
		{
			creare_lista_nivel(r->stanga, nivel - 1, list);
			creare_lista_nivel(r->dreapta, nivel - 1, list);
		}
	}
}

struct ArbBin* stergere_nod(struct ArbBin* r, unsigned short int key, struct Angajat *a)
{
	if (r)
	{
		if (key == r->ang.cod)
		{
			*a = r->ang; // datele angajatului se salveaza in parametrul a 

			// este identificat nodul de sters in arbore
			if (!r->stanga && !r->dreapta)
			{
				// nodul de sters este nod frunza				
				free(r);
				r = NULL;
			}
			else
			{
				if (r->stanga && r->dreapta)
				{
					// nodul de sters are 2 descendenti
					struct ArbBin* tmp = r->stanga; // se alege subarborele stanga
					while (tmp->dreapta)
						tmp = tmp->dreapta;

					// interschimbare nod de sters cu nodul cu cheia maxima din subarborele stanga
					struct Angajat aux = r->ang;
					r->ang = tmp->ang;
					tmp->ang = aux;

					r->stanga = stergere_nod(r->stanga, key, a);
				}
				else
				{
					// nodul de sters are 1 descendent
					struct ArbBin* tmp;
					if (r->stanga) tmp = r->stanga;
					else tmp = r->dreapta;

					free(r);
					return tmp;
				}
			}
		}
		if (r)
		{
			r->stanga = stergere_nod(r->stanga, key, a);
			r->dreapta = stergere_nod(r->dreapta, key, a);
		}
	}

	return r;
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r");
	struct Angajat fang;
	char buffer[128];

	struct ArbBin* root = NULL;

	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #1
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		unsigned char flag;
		root = inserare_arbore(root, fang, &flag);

		if (flag)
		{
			printf("\nAngajat %hu inserat in arbore.", fang.cod);
		}
		else
		{
			printf("\nEsec inserare angajat %hu in arbore.", fang.cod);
			free(fang.nume);
		}

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
	}
	fclose(f);

	printf("\nTraversare inordine arbore:");
	inordine(root);

	unsigned int nr_noduri = 0;
	nr_noduri_nivel(root, 4, &nr_noduri);
	printf("\nNumarul de noduri determinat pe nivel specificat: %hu", nr_noduri);

	struct Nod* lista = NULL;
	creare_lista_nivel(root, 4, &lista); // lista se transfera prin adresa
	printf("\nLista cu angajati plasati pe nivel specificat in arbore:");
	struct Nod* tmp = lista;
	while (tmp)
	{
		printf("\n\t%hu %s", tmp->pang->cod, tmp->pang->nume);

		tmp = tmp->next;
	}

	root = stergere_nod(root, 1333, &fang);
	printf("\nTraversare inordine arbore dupa stergere nod:");
	inordine(root);

	root = dezalocare_arbore(root);
	printf("\nTraversare inordine arbore dupa dezalocare:");
	inordine(root);

	// dezalocare lista de angajati de pe nivel specificat
	while (lista)
	{
		tmp = lista;
		lista = lista->next;

		free(tmp);
	}

	printf("\nLista cu angajati dupa dezalocare:");
	tmp = lista;
	while (tmp)
	{
		printf("\n\t%hu %s", tmp->pang->cod, tmp->pang->nume);

		tmp = tmp->next;
	}
}

