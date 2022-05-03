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
	struct NodD *next, *prev; // adrese structuri similare in abordare secventiala/liniara
};

struct ListaDubla
{
	struct NodD* first, * last;
};

struct ListaDubla inserare_sfarsit_LD(struct ListaDubla list, struct Angajat a) 
{
	struct NodD* nou = (struct NodD*)malloc(sizeof(struct NodD));

	nou->ang = a;
	nou->next = NULL;
	nou->prev = list.last;

	if (list.last)
	{
		// LD contine cel putin 1 nod
		list.last->next = nou;
	}
	else
	{
		// LD este empty (0 noduri)
		list.first = nou;
	}

	list.last = nou;

	return list;
}

struct ListaDubla dezalocare_LD(struct ListaDubla list)
{
	while(list.first)
	{
		struct NodD* tmp = list.first;
		list.first = list.first->next;

		free(tmp->ang.nume);
		free(tmp);
	}

	// first iese cu NULL din while anterior
	// last tb actualizat explicit cu NULL
	list.last = NULL;

	return list;
}

// interschimb noduri adiacente cu modificare adrese de legatura
// se interschimba nodurile (i, i+1)
struct ListaDubla interschimb_adiacente(struct ListaDubla list, unsigned char i)
{
	if (list.first && list.first->next)
	{
		// exista cel putin 2 noduri in LD
		struct NodD* tmp = list.first;
		unsigned char k = 1;
		while (tmp->next && k < i)
		{
			k += 1;
			tmp = tmp->next;
		}

		if (tmp->next)
		{
			// k == i; pozitionare pe primul nodul i (primul de interschimb)
			if ((tmp != list.first) && (tmp != list.last->prev))
			{
				// caz general de insterschimb
				struct NodD* p, * q, * r;
				p = tmp->prev;
				q = tmp->next;
				r = q->next;

				tmp->next = r;
				tmp->prev = q;
				q->next = tmp;
				q->prev = p;
				p->next = q;
				r->prev = tmp;
			}
			else
			{
				if (tmp == list.first)
				{
					// se interschimba (1, 2)
					// ?? LD are 2 noduri
					struct NodD* q, * r;
					q = tmp->next;
					r = q->next;
					
					tmp->next = r;
					tmp->prev = q;
					q->next = tmp;
					q->prev = NULL;
					list.first = q;
					if (list.first == list.last)
					{
						list.last = list.first->next;
					}
					else
						r->prev = tmp;
				}
				else
				{
					// se interschimba (n-1, n)
					struct NodD* p, * q;
					p = tmp->prev;
					q = tmp->next;

					tmp->next = NULL;
					tmp->prev = q;
					q->next = tmp;
					q->prev = p;
					p->next = q;
					list.last = tmp;
				}
			}
		}
	}
	return list;
}

// interschimb noduri oarecare (cu modificare adrese de legatura)

// LS/LD circularen

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct ListaDubla listD;
	listD.first = listD.last = NULL; // LD empty (0 noduri)

	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		listD = inserare_sfarsit_LD(listD, fang);

		fscanf(f, "%hu,", &fang.cod);
	}

	fang.nume = NULL;

	printf("\nLista dubla (first->last):");
	struct NodD* tmp = listD.first;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	tmp = listD.last;
	printf("\nLista dubla (last->first):");
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	listD = interschimb_adiacente(listD, 2);
	printf("\nLista dubla dupa interschimb (first->last):");
	tmp = listD.first;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	tmp = listD.last;
	printf("\nLista dubla dupa interschimb (last->first):");
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	listD = dezalocare_LD(listD);
	printf("\nLista dubla dupa dezalocare (first->last):");
	tmp = listD.first;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	tmp = listD.last;
	printf("\nLista dubla dupa dezalocare (last->first):");
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	fclose(f);
}