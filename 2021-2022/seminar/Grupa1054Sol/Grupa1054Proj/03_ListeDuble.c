
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// creare lista simpla cu angajati
// date preluate din fisier

struct Angajat
{
	char* nume;
	unsigned short int cod;
	float salariu;
};

struct NodD
{
	struct Angajat ang;
	struct NodD *next, *prev;
};

struct ListaDubla
{
	struct NodD* first, * last;
};

// #define LINE_SIZE 128

// [in] list - lista dubla in care se insereaza angajat la sfarsit
// [in] a - datele angajatului care se insereaza la sfarsit in LD list
// [return] LD dubla actualizata dpv adrese inceput, respectiv sfarsit
struct ListaDubla inserare_sfarsit(struct ListaDubla list, struct Angajat a)
{
	struct NodD* nouD = (struct NodD*)malloc(sizeof(struct NodD)); // alocare nod nou

	nouD->ang = a;
	nouD->next = NULL;
	nouD->prev = list.last; // daca LD este empty, atunci last este NULL

	if (list.last)
	{
		// exista cel putin 1 nod in LD
		list.last->next = nouD;
	}
	else
	{
		// LD este empty
		list.first = nouD;
	}

	list.last = nouD;

	return list;
}

struct ListaDubla dezalocare_lista_dubla(struct ListaDubla list)
{
	while (list.first)
	{
		// exista cel putin 1 nod in LD
		struct NodD* tmp = list.first;
		list.first = list.first->next;

		free(tmp->ang.nume);
		free(tmp);
	}

	list.last = NULL;

	return list;
}

// stergere nod din interior LD
// intreschimb noduri oarecare in LD (prin modificare adrese de legatura)
struct ListaDubla interschimb_oarecare(struct ListaDubla list, unsigned short int i, unsigned short int j)
{
	if (list.first && list.first->next)
	{
		if (i > j)
		{
			// interschimb pentru a avea situatie de tip i<j
			unsigned short int aux = i;
			i = j;
			j = aux;
		}

		struct NodD* tempi = list.first;
		unsigned short int k = 1;
		while (tempi->next && k < i)
		{
			k += 1;
			tempi = tempi->next;
		}
		if (tempi->next)
		{
			// exista cel putin 1 nod dupa tempi
			// tempi este nodul de pe pozitia i
			struct NodD* tempj = tempi;
			while (tempj->next && k < j)
			{
				k += 1;
				tempj = tempj->next;
			}

			if (k == j)
			{
				// exista nodurile i si j in LD
				struct NodD* p, * q, * r, * s;
				p = tempi->prev;
				r = tempi->next;
				s = tempj->prev;
				q = tempj->next;

				if (tempi == list.first && tempj == list.last)
				{					
					// se interschimba 1 cu n; se actualizeaza ambele capete
					// se trateaza diferit cazul 1 cu 2 si 2 noduri in LD (vezi caz general)
					;
				}
				else
				{
					if (tempi == list.first)
					{
						// se interschimba 1 cu j; se actualizeaza inceputul LD
						;
					}
					else
					{
						if (tempj == list.last)
						{
							// se interschimba i cu n; se actualizeaza sfarsitul LD
							;
						}
						else
						{
							// caz general, inclusiv j == i+1							
							if (tempj != tempi->next)
							{
								// tempi si tempj nu sunt adiacente
								p->next = tempj;
								tempi->next = q;
								tempj->prev = p;
								q->prev = tempi;

								tempi->prev = s;
								r->prev = tempj;
								tempj->next = r;
								s->next = tempi;
							}
							else
							{
								// noduri adiacente
								p->next = tempj;
								tempi->next = q;
								tempj->prev = p;
								q->prev = tempi;

								tempi->prev = tempj;
								tempj->next = tempi;
							}
							
						}
					}
				}
			}

		}
	}

	return list;
}

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	char nume[64];
	struct Angajat fang;
	struct ListaDubla listD;
	listD.first = listD.last = NULL; // initial, lista dubla este empty (0 noduri)

	fscanf(f, "%[^,],", nume);
	while (!feof(f))
	{
		fscanf(f, "%hu,%f\n", &fang.cod, &fang.salariu);

		fang.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		listD = inserare_sfarsit(listD, fang);
		fscanf(f, "%[^,],", nume);
	}

	printf("\nContinut lista dubla de angajati (first->last):");
	struct NodD* tmp = listD.first; // initializare tmp cu adresa primului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}
	printf("\n\nContinut lista dubla de angajati (last->first):");
	tmp = listD.last; // initializare tmp cu adresa ultimului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	// interschimb noduri oarecare
	listD = interschimb_oarecare(listD, 2, 4);
	printf("\n\nContinut lista dubla dupa interschimb (first->last):");
	tmp = listD.first; // initializare tmp cu adresa primului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}
	printf("\n\nContinut lista dubla dupa interschimb (last->first):");
	tmp = listD.last; // initializare tmp cu adresa ultimului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	listD = dezalocare_lista_dubla(listD);
	printf("\n\nContinut lista dubla dupa dezalocare (first->last):");
	tmp = listD.first; // initializare tmp cu adresa primului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}
	printf("\n\nContinut lista dubla dupa dezalocare  (last->first):");
	tmp = listD.last; // initializare tmp cu adresa ultimului nod din LD
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->prev;
	}

	fclose(f);
}