#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Angajat
{
	unsigned short int id;
	char* nume;
	float salariu;
};

struct NodD
{
	struct Angajat ang;
	struct NodD* prev, * next;
};

struct ListaD
{
	struct NodD *prim, *ultim;
};

// inserare la inceput in lista dubla
// [in] list - lista dubla in care se insereaza angajat la inceput
// [in] a - datele unui angajat care se insereaza la inceputul listei list
// [return] - adrese inceput/sfarsit actualizate pentru lista dubla list
struct ListaD inserare_inceput(struct ListaD list, struct Angajat a)
{
	struct NodD* nou = (struct NodD*)malloc(sizeof(struct NodD));

	nou->ang = a;
	nou->prev = NULL; // inserare la inceput; obligatoriu predecesor nul
	nou->next = list.prim;

	if (list.prim == NULL)
	{
		// lista dubla empty
		list.prim = list.ultim = nou;
	}
	else
	{
		list.prim->prev = nou;
		list.prim = nou;
	}

	return list;
}

// export angajati in vector
// [in,out] list - lista dubla din care se exporta angajati; lista se dezaloca
// [out] vector_size - numarul de elemente din vectorul de angajati; egal cu nr de noduri din lista dubla
// [return] - adresa de inceput a vectorului de angajati exportati din lista dubla
struct Angajat* export_angajati(struct ListaD *list, unsigned char * vector_size)
{
	*vector_size = 0;
	struct NodD* t;
	t = list->prim;
	while (t)
	{
		*vector_size += 1;
		t = t->next;
	}

	//alocare mem heap vector de angajati
	struct Angajat* v_angajati = (struct Angajat*)malloc(*vector_size * sizeof(struct Angajat));
	// populare vector
	unsigned char k = 0;
	t = list->prim;
	while (t)
	{
		v_angajati[k++] = t->ang;

		t = t->next;
	}

	// dezalocare lista dubla
	while (list->prim)
	{
		t = list->prim;
		list->prim = list->prim->next;
		free(t);
	}
	list->ultim = NULL;

	return v_angajati;
}

// stergere noduri cu cod divizibil cu o valoare specificata
struct ListaD stergere_criteriu(struct ListaD list, unsigned char cod)
{

}

// completare cu implementari operatii de baza preluate de la liste simple
// operatii de baza cu liste circulare

void main()
{
	FILE* f;
	struct Angajat tmp;

	struct ListaD listDubla;

	// lista dubla cu 0 noduri (empty)
	listDubla.prim = NULL;
	listDubla.ultim = NULL;

	f = fopen("Angajati.txt", "r");

	fscanf(f, "%hu,", &tmp.id);
	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = (char*)malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		// inserare tmp in lista dubla
		listDubla = inserare_inceput(listDubla, tmp);

		fscanf(f, "%hu,", &tmp.id);
	}
	tmp.nume = NULL;


	struct Angajat* vang;
	unsigned char size;

	vang = export_angajati(&listDubla, &size);
	printf("\nContinut vector de angajati:\n");
	for (unsigned char i = 0; i < size; i++)
		printf("\t%s\n", vang[i].nume);

	printf("\nLista dubla dupa export angajati:\n");
	struct NodD* t;
	t = listDubla.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);

		t = t->next;
	}

	// dezalocare vector de angajati
	for (unsigned char i = 0; i < size; i++)
		free(vang[i].nume);
	free(vang);
	vang = NULL;
	
}