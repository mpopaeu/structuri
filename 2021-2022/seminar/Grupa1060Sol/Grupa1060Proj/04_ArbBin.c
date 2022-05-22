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
	struct ArbBin* stanga, * dreapta;
};


struct ArbBin* inserare_arbore(struct ArbBin* r, struct Angajat a, unsigned char *inserat)
{
	if (r)
	{
		if (r->ang.cod > a.cod)
			r->stanga = inserare_arbore(r->stanga, a, inserat);
		else
			if (r->ang.cod < a.cod)
				r->dreapta = inserare_arbore(r->dreapta, a, inserat);
			else
				*inserat = 0; // inserarea nu are loc; cheie duplicat
		return r;
	}
	else
	{
		// r == NULL; pozitia pe care nodul nou o va ocupa in arbore
		struct ArbBin* nou = (struct ArbBin*)malloc(sizeof(struct ArbBin));
		nou->ang = a;
		nou->dreapta = NULL;
		nou->stanga = NULL;

		*inserat = 1; // succes inserare
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

// [in] r - nod curent (atins in cautare nod de sters) din arbore
// [in] cheie - cheia de cautare a nodului de sters
// [out] a - datele angajatului din nodul sters pe baza de cheie
// [return] adresa nodului curent, eventual modificata dupa dezalocare nodului de sters
struct ArbBin* stergere_nod_arbore(struct ArbBin* r, unsigned short int cheie, struct Angajat *a)
{
	a->nume = NULL;
	if (r)
	{
		if (r->ang.cod > cheie)
			r->stanga = stergere_nod_arbore(r->stanga, cheie, a);
		else
			if (r->ang.cod < cheie)
				r->dreapta = stergere_nod_arbore(r->dreapta, cheie, a);
			else
			{
				// exista nod de sters
				*a = r->ang;

				if (r->stanga == NULL && r->dreapta == NULL)
				{
					// nodul de sters este frunza					
					free(r); // nume angajat este partajat intre *a si r->ang

					r = NULL;
				}
				else
				{
					if (r->stanga != NULL && r->dreapta != NULL)
					{
						// nodul de sters are 2 descendenti

						// cautare cel mai din stanga nod din surbarborele dreapta
						struct ArbBin* temp = r->dreapta;
						while (temp->stanga)
							temp = temp->stanga;

						r->ang = temp->ang; // stergere logica prin rescrierea datelor in nodul de sters

						// stergere nod cu cheie duplicat in subarborele dreapta a nodului de sters
						struct Angajat ang_fake;
						r->dreapta = stergere_nod_arbore(r->dreapta, temp->ang.cod, &ang_fake); // stergere in subarbore dreapta
					}
					else
					{
						// nodul de sters are 1 descendent
						struct ArbBin* temp;
						if (r->stanga)
							temp = r->stanga;
						else
							temp = r->dreapta;

						free(r);
						r = temp; // se returneaza in apelul anterior adresa descendentului nodului dezalocat
					}
				}
			}		
	}
	
	return r;
}


struct NodList
{
	struct ArbBin* adresa_nod;
	struct NodList* next;
};

struct NodList* push(struct NodList* l, struct ArbBin* r)
{
	struct NodList* nou = (struct NodList*)malloc(sizeof(struct NodList));

	nou->adresa_nod = r;
	nou->next = l;

	return nou;
}

struct NodList* pop(struct NodList* l, struct ArbBin* *r)
{
	if (l)
	{
		*r = l->adresa_nod; // salvez adresa nod arbore in parametrul de iesire r

		struct NodList* temp = l;
		l = l->next;

		free(temp);
	}

	return l;
}

struct NodList* drum_invers_iterativ(struct ArbBin* r, unsigned short int cheie, unsigned char *gasit)
{
	struct NodList* list = NULL;
	struct ArbBin* temp = r;

	while (temp)
	{
		list = push(list, temp);
		if (cheie < temp->ang.cod)
		{
			temp = temp->stanga;
		}
		else
		{
			if (cheie > temp->ang.cod)
			{
				temp = temp->dreapta;
			}
			else
			{
				// nodul este identificat
				*gasit = 1;
				return list;
			}
		}
	}

	*gasit = 0;
	return list;
}

// determinare noduri de pe nivel specificat
// determinare niveluri pe care se afla plasate noduri frunza

void main()
{
	struct ArbBin* root = NULL;
	FILE* f;
	struct Angajat tmp;

	f = fopen("Angajati.txt", "r");
	fscanf(f, "%hu,", &tmp.cod);

	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		unsigned char inserat;
		root = inserare_arbore(root, tmp, &inserat);

		if (inserat)
		{
			printf("\nAngajatul %hu este inserat", tmp.cod);
		}
		else
		{
			printf("\nAngajatul %hu nu este inserat", tmp.cod);
			free(tmp.nume);
		}

		fscanf(f, "%hu,", &tmp.cod);
	}
	fclose(f);

	printf("\nArborele dupa creare:");
	inordine(root);

	struct NodList* stack = NULL;
	unsigned char gasit;
	stack = drum_invers_iterativ(root, 200, &gasit);
	if (gasit)
	{
		printf("\nNod identificat in arbore. Drumul invers este:");
		while (stack)
		{
			struct ArbBin* adresa_nod;
			stack = pop(stack, &adresa_nod);
			printf("\n%hu %s", adresa_nod->ang.cod, adresa_nod->ang.nume);
		}
	}
	else
	{
		printf("\nNU exista nod cautat in arbore.");
	}

	root = stergere_nod_arbore(root, 2009, &tmp);

	if (tmp.nume)
	{
		printf("\nAngajat extras: %hu %s", tmp.cod, tmp.nume);
		free(tmp.nume);
	}
	else
	{
		printf("\nAngajatul NU exista in arbore.");
		// dezalocare stiva cu noduri de pe drum
		while (stack)
		{
			stack = pop(stack, &tmp);
		}
	}

	printf("\nArborele dupa stergere angajat:");
	inordine(root);

	// dezalocare arbore
	while (root)
	{
		root = stergere_nod_arbore(root, root->ang.cod, &tmp);
		if (tmp.nume)
			free(tmp.nume);
	}
	printf("\nArborele dupa dezalocare:");
	inordine(root);
}