#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct NodArb
{
	struct Angajat ang;
	struct NodArb * stanga, *dreapta;
};

struct NodArb* inserare_nod(struct NodArb* r, struct Angajat a, unsigned char *flag_inserare)
{
	if (r)
	{
		if (a.cod < r->ang.cod)
		{
			r->stanga = inserare_nod(r->stanga, a, flag_inserare);
		}
		else
		{
			if (a.cod > r->ang.cod)
			{
				r->dreapta = inserare_nod(r->dreapta, a, flag_inserare);
			}
			else
				*flag_inserare = 0;
		}
		return r;
	}
	else
	{
		struct NodArb* nou = (struct NodArb*)malloc(sizeof(struct NodArb));
		nou->ang = a;
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*flag_inserare = 1;
		return nou;
	}
}

void inordine(struct NodArb* r)
{
	if (r)
	{
		inordine(r->stanga);
		printf("\n\t%hu %s", r->ang.cod, r->ang.nume);
		inordine(r->dreapta);
	}
}

struct NodArb* stergere_nod(struct NodArb* r, unsigned short int cheie, struct Angajat *a)
{
	a->nume = NULL; // ipoteza: angajatul nu exista
	if (r)
	{
		if (cheie < r->ang.cod)
		{
			r->stanga = stergere_nod(r->stanga, cheie, a);
		}
		else
		{
			if (cheie > r->ang.cod)
			{
				r->dreapta = stergere_nod(r->dreapta, cheie, a);
			}
			else
			{
				// nodul de sters (r) a fost identificat
				*a = r->ang;
				if (r->stanga == NULL && r->dreapta == NULL)
				{
					// nodul r are 0 descendenti (frunza)
					// nodul r se dezaloca logic si fizic
					free(r);
					r = NULL;
				}
				else
				{
					if (r->stanga != NULL && r->dreapta != NULL)
					{
						// nodul de sters (r) are 2 descendenti
						struct NodArb* r_ss, * r_sd, * temp;
						// salvare adrese subarbori
						r_ss = r->stanga;
						r_sd = r->dreapta;

						// dezalocare nod curent
						// nodul r se dezaloca logic si fizic
						free(r);

						//identificare nod cu cheia minima (temp) din subarbore dreapta 
						temp = r_sd;
						while (temp->stanga)
							temp = temp->stanga;

						temp->stanga = r_ss; // subarbore stanga se adauga la subarbore dreapta

						r = r_sd;
					}
					else
					{
						// nodul r are 1 descendent
						struct NodArb* temp;
						if (r->stanga)
							temp = r->stanga;
						else
							temp = r->dreapta;

						// nodul r se dezaloca logic si fizic
						free(r);
						r = temp;
					}
				}
			}
		}
	}

	return r;
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct NodArb* root = NULL;


	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		unsigned char flag;
		root = inserare_nod(root, fang, &flag);

		if (flag)
			printf("\nAngajat %hu inserat in arbore binar de cautare.", fang.cod);
		else
		{
			printf("\nAngajatul %hu exista in arbore binar de cautare", fang.cod);
			free(fang.nume); // angajatul fang nu se insereaza in arbore
		}

		fscanf(f, "%hu,", &fang.cod);
	}

	printf("\nArborele dupa creare:");
	inordine(root);

	root = stergere_nod(root, 2, &fang);
	if (fang.nume != NULL)
	{
		printf("\n\nAngajat %hu %s eliminat din arbore", fang.cod, fang.nume);
		free(fang.nume);
	}
	else
	{
		printf("\n\nAngajatul NU a fost identificat in arbore.");
	}

	printf("\nArborele dupa stergere angajat:");
	inordine(root);

	// dezalocare arbore
	while (root)
	{
		root = stergere_nod(root, root->ang.cod, &fang);
		if (fang.nume)
			free(fang.nume);
	}

	printf("\n\nArborele dupa dezalocare:");
	inordine(root);

	// noduri plasate pe un nivel specificat
	// numarul de noduri frunza de pe fiecare nivel
	// determinare echilibru arbore
	// stergere noduri pe baza nume angajat

	fclose(f);
}