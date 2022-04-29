#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct NodD
{
	struct Angajat ang;
	struct NodD *prev, *next;
};

struct ListaDubla
{
	struct NodD* prim, * ultim;
};

// inserare nod la inceput in lista dubla
// [in] list - lista dubla in care se efectueaza inserarea angajatului a
// [in] a - angajatul care se insereaza la inceputul listei duble
// [return] - lista dubla actualizata (primul nod contine angajatul a)
struct ListaDubla inserare_inceput(struct ListaDubla list, struct Angajat a)
{
	struct NodD* nou = (struct NodD*)malloc(sizeof(struct NodD));
	nou->ang = a;
	nou->prev = NULL;
	nou->next = list.prim;

	if (list.prim == NULL)
	{
		list.ultim = nou;
	}
	else
	{
		list.prim->prev = nou;
	}
	list.prim = nou;

	return list;
}

// [in] list - lista dubla care se dezaloca
// [return] lista dubla empty (adrese de inceput si sfarsit nule)
struct ListaDubla dezalocare(struct ListaDubla list)
{
	struct NodD* tmp = list.prim;
	while (tmp)
	{
		list.prim = list.prim->next;
		free(tmp->ang.nume);
		free(tmp);

		tmp = list.prim;
	}

	list.ultim = NULL; // obligatoriu pentru acces corect la lista empty
	return list;
}

struct ListaDubla dezalocare_pozitie(struct ListaDubla list, unsigned short int poz)
{
	struct NodD* tmp = list.prim;
	if (tmp)
	{
		unsigned short int nr_noduri = 1;
		while (tmp)
		{
			nr_noduri += 1;
			tmp = tmp->next;
		}
		if (poz <= nr_noduri)
		{
			tmp = list.prim;
			unsigned short int i = 1;
			while (i <= poz)
			{
				i += 1;
				tmp = tmp->next;
			}
			if (tmp->next && tmp->prev)
			{
				// caz general
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;

				free(tmp->ang.nume);
				free(tmp);
			}
			else
			{
				if (!tmp->next && !tmp->prev)
				{
					// dezalocare nod pozitie 1; nodul este unic in LD
					free(tmp->ang.nume);
					free(tmp);

					list.prim = list.ultim = NULL; // LD devine empty
				}
				else
				{
					if (!tmp->prev)
					{
						// stergere nod la inceputul LD
						list.prim = list.prim->next;
						list.prim->prev = NULL;

						free(tmp->ang.nume);
						free(tmp);
					}
					else
					{
						// stergere nod la sfarsitul LD
						list.ultim = list.ultim->prev;
						list.ultim->next = NULL;

						free(tmp->ang.nume);
						free(tmp);
					}
				}
			}
		}
	}

	return list;
}

// interschimb noduri adiacente in LD (prin modificare adrese de legatura)

void main()
{
	struct ListaDubla listD;
	listD.prim = NULL; // adresa primului nod
	listD.ultim = NULL; // adresa ultimului nod

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

		// inserare angajat in lista simpla
		listD = inserare_inceput(listD, tmp);

		fscanf(f, "%hu,", &tmp.cod);
	}


	// lista dubla dupa creare
	printf("\nLista dubla dupa creare (inceput->sfarsit):\n");
	struct NodD* temp = listD.prim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->next;
	}
	printf("\nLista dubla dupa creare (sfarsit->inceput):\n");
	temp = listD.ultim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->prev;
	}

	listD = dezalocare_pozitie(listD, 1);
	// lista dubla dupa stergere nod de pe pozitie data
	printf("\nLista dubla dupa dezalocare (inceput->sfarsit):\n");
	temp = listD.prim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->next;
	}
	printf("\nLista dubla dupa dezalocare (sfarsit->inceput):\n");
	temp = listD.ultim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->prev;
	}

	listD = dezalocare(listD);

	// lista dubla dupa dezalocare
	printf("\nLista dubla dupa dezalocare (inceput->sfarsit):\n");
	temp = listD.prim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->next;
	}
	printf("\nLista dubla dupa dezalocare (sfarsit->inceput):\n");
	temp = listD.ultim;
	while (temp)
	{
		printf("\n\t%s", temp->ang.nume);
		temp = temp->prev;
	}

	// operatiile de la liste simple translatate pe liste duble

	fclose(f);
}