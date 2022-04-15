#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Angajat
{
	unsigned short int cod;
	char* nume;
	float salariu;
};

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

// inserare nod in LS (inceput/sfarsit/interior)

// inserare nod in LS (inceput)
// [in] list - adresa primului nod in LS
// [in] fang - datele angajatului care se insereaza in LS
// [return] - noua adresa de inceput a LS
struct Nod* inserare_inceput(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = a;
	nou->next = list;

	return nou;
}

// stergere nod din LS (inceput/sfarsit/interior)

// dezalocare LS
// export angajati in vector (LS devine empty)
// [in] list - lista de angajati care se exporta
// [out] v_angajati - vector de angajati 
// [out] din_vector - nr de angajati din vectorul v_angajati
// [return] lista simpla empty
struct Nod* export_angajati(struct Nod* list, struct Angajat** v_angajati, unsigned char* dim_vector)
{
	*dim_vector = 0;
	struct Nod* t = list;
	while (t) // determinare dimensiune vector (nr angajati in lista simpla)
	{
		*dim_vector += 1;
		t = t->next;
	}

	*v_angajati = (struct Angajat*)malloc(*dim_vector * sizeof(struct Angajat));
	unsigned char k = 0;
	t = list;
	while (t) // copiere angajat din nodul curent t in elementul k din vector
	{
		(*v_angajati)[k++] = t->ang;
		t = t->next;
	}

	// dezalocare noduri lista simpla
	while (list)
	{
		t = list; 
		list = list->next; // mutare list pe nodul 2
		//dezalocare nod izolat t
		free(t);
	}

	return list;
}

// liste duble -> operatiile de mai sus

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r");
	struct Angajat fang;
	char buffer[128];

	struct Nod* pList = NULL;

	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #1
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		pList = inserare_inceput(pList, fang);

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
	}

	// parsare LS
	struct Nod* t;
	printf("\nLista simpla dupa creare:\n");
	t = pList;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}

	struct Angajat* vang;
	unsigned char vector_size;
	pList = export_angajati(pList, &vang, &vector_size);

	printf("\nVector cu angajati exportati:\n");
	for (unsigned char i = 0; i < vector_size; i++)
		printf("\t%s\n", vang[i].nume);

	printf("\nLista simpla dupa export angajati:\n");
	t = pList;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}

	// dezalocare vector cu angajati exportati
	for (unsigned char i = 0; i < vector_size; i++)
		free(vang[i].nume);
	free(vang);
	vang = NULL;

	fclose(f);
}