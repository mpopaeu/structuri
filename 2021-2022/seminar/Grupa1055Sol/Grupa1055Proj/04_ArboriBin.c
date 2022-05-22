#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
};

struct NodABC
{
	struct Angajat ang;
	struct NodABC* stanga, * dreapta;
};

typedef struct Angajat Angajat;
typedef struct NodABC NodABC;

NodABC* insNodABC(NodABC* r, Angajat a, unsigned char* err) {
	if (r) {
		if (r->ang.id > a.id)
			r->stanga = insNodABC(r->stanga, a, err);
		else
			if (r->ang.id < a.id)
				r->dreapta = insNodABC(r->dreapta, a, err);
			else
				*err = 1; // nod existent cu aceeasi cheie la inserarea lui a
	}
	else {
		// locul de inserat nod in arbore AVL este identificat
		NodABC* nou;
		nou = (NodABC*)malloc(sizeof(NodABC));
		nou->ang = a;
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*err = 0;
		r = nou;
	}

	return r;
}

void inordine(NodABC* r)
{
	if (r)
	{
		inordine(r->stanga);
		printf("\n%hu %s", r->ang.id, r->ang.nume);
		inordine(r->dreapta);
	}
}

// [in] r - nod curent din arbore (radacaina arbore/subarbore)
// [in] cheie - cheia de cautare nodului de sters
// [out] a - datele angajatului din nodul sters in arbore; va avea nume pe NULL daca angajatul nu exista in arbore
// [return] adresa, eventual modificata, a nodului curent pentru a actualiza unul din descendentii nodului parinte
NodABC* stergere_nod(NodABC* r, unsigned short int cheie, Angajat* a)
{
	a->nume = NULL; // ipoteza: angajatul nu a fost identificat in arbore
	if (r) {
		if (r->ang.id > cheie)
			r->stanga = stergere_nod(r->stanga, cheie, a);
		else
			if (r->ang.id < cheie)
				r->dreapta = stergere_nod(r->dreapta, cheie, a);
			else
			{
				// nodul de sters este identificat in arbore

				// angajatul exista in arbore
				*a = r->ang; // salvare date angajat din nodul de sters r in parametrul de output (rezultat)

				if (r->stanga == NULL && r->dreapta == NULL)
				{
					// nodul de sters este frunza
					free(r); // dezalocare fizica nod frunza

					r = NULL;
				}
				else
				{
					if (r->stanga != NULL && r->dreapta != NULL)
					{
						// nodul de sters are 2 descendenti
						NodABC* temp = r->dreapta;

						while (temp->stanga)
							temp = temp->stanga;

						// temp este cel mai din stanga nod din subarbore dreapta; contine cheia minima din subarbore dreapta
						r->ang = temp->ang; // rescrierea angajatului din r cu datele angajatului din temp; stergere logica a nodului r

						// stergere fizica nod temp (cu date duplicate in arbore)
						Angajat angajat_duplicat;
						r->dreapta = stergere_nod(r->dreapta, temp->ang.id, &angajat_duplicat);
					}
					else
					{
						// nodul de sters are 1 descendent
						NodABC* temp;
						if (r->stanga)
							temp = r->stanga;
						else
							temp = r->dreapta;

						free(r); // dezalocare fizica nod cu 1 descendent

						r = temp; // descendenul lui r este trimis in parintele lui r de dinainte de stergere
					}
				}
			}
	}

	return r;
}

// nivelurile cu noduri avand 2 descendenti
// echilibrare arbore

void main()
{
	FILE* f;
	Angajat tmp;

	NodABC* root = NULL;

	f = fopen("Angajati.txt", "r");

	fscanf(f, "%hu,", &tmp.id);
	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = (char*)malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		// inserare tmp in arbore binar de cautare
		unsigned char err; // cod eroare la inserare cheie duplicat in arbore
		root = insNodABC(root, tmp, &err);
		if (err)
		{
			printf("\nAngajatul %hu NU a fost inserat (cheie duplicat).", tmp.id);
			free(tmp.nume);
		}
		else
		{
			printf("\nInserare cu succes angajat %hu %s", tmp.id, tmp.nume);
		}

		fscanf(f, "%hu,", &tmp.id);
	}

	printf("\n\nArborele dupa creare:");
	inordine(root);

	root = stergere_nod(root, 109, &tmp);
	if (tmp.nume)
	{
		printf("\nAngajatul sters: %hu %s", tmp.id, tmp.nume);
		free(tmp.nume);
	}
	else
	{
		printf("\nAngajatul NU a fost identificat in arbore.");
	}

	printf("\n\nArborele dupa stergere nod:");
	inordine(root);

	// dezalocare arbore
	while (root)
	{
		root = stergere_nod(root, root->ang.id, &tmp);
		if (tmp.nume)
			free(tmp.nume);
	}

	printf("\n\nArborele dupa dezalocare:");
	inordine(root);
}