#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

// operatii de baza cu liste simple

// inserare nod la inceput

// [in] pList - lista in care se face inserarea la inceput
// [in] ang - date Angajat care se insereaza in lista simpla
// [return] adresa noului nod inceput de lista
struct Nod* inserare_inceput(struct Nod* pList, struct Angajat new_ang)
{
	struct Nod* new_node;
	new_node = (struct Nod*)malloc(sizeof(struct Nod));

	new_node->ang = new_ang;
	new_node->next = pList;

	return new_node;
}

// inserare nod la sfarsit
// inserare nod interior

// stergere nod la inceput
// stergere nod la sfarsit
// stergere nod interior

// parsare lista simpla

// export angajati in vector

void main()
{

}