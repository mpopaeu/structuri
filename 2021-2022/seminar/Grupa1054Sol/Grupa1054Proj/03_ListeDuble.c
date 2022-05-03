
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