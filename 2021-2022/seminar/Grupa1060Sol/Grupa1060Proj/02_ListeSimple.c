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

// inserare nod inceput/sfarsit/interior
// stergere nod inceput/sfarsit/interior

// parsare lista
// dezalocare lista simpla
struct Nod* dezalocare_lista(struct Nod* list)
{
	struct Nod* t;
	
	while (list)
	{
		t = list;
		list = list->next;

		free(t->ang.nume);
		free(t);
	}

	return list;
}

// copiere angajati in vector (vectorul si LS nu partajeaza zone heap)
// [in] list - adresa inceput lista simpla angajati
// [out] vector_size - dimensiune calculata a vectorului de angajati
// [return] - adresa heap inceput vector angajati
struct Angajat* copiere_angajati(struct Nod* list, unsigned char* vector_size)
{
	*vector_size = 0;
	// determinare numar de angajati == nr de noduri din lista simpla
	struct Nod* t = list;
	while (t) // parsare lista simpla
	{
		*vector_size += 1; // incrementare dimensiune vector de angajati
		t = t->next; // acces la nod succesor
	}

	struct Angajat* v_angajati = (struct Angajat*)malloc(*vector_size * sizeof(struct Angajat));
	t = list;
	unsigned char k = 0;
	while (t) // parsare lista simpla
	{
		v_angajati[k].cod = t->ang.cod;
		v_angajati[k].salariu = t->ang.salariu;

		// vectorul nu partajeaza memorie heap cu lista
		v_angajati[k].nume = malloc((strlen(t->ang.nume) + 1) * sizeof(char));
		strcpy(v_angajati[k].nume, t->ang.nume);

		k += 1; // acces la urmatorul element din vector
		t = t->next; // acces la nod succesor
	}

	return v_angajati;
}

// inserare nod la inceput
// [in] list - adresa inceput LS (adresa primului nod)
// [in] a - date angajat care se insereaza in LS
// [return] noua adresa de inceput a LS (a se insereaza la inceputul LS)
struct Nod* inserare_inceput(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->ang = a;
	nou->next = list;

	return nou;
}

void main()
{
	FILE* f;
	struct Angajat tmp;
	struct Nod* pList = NULL;

	f = fopen("Angajati.txt", "r");
	fscanf(f, "%hu,", &tmp.cod);

	while (!feof(f))
	{
		char nn[64];
		fscanf(f, "%[^,],%f\n", nn, &tmp.salariu);

		tmp.nume = malloc(sizeof(char) * (strlen(nn) + 1));
		strcpy(tmp.nume, nn);

		// inserare angajat in lista simpla
		pList = inserare_inceput(pList, tmp);

		fscanf(f, "%hu,", &tmp.cod);
	}

	tmp.nume = NULL;

	struct Nod* t;
	printf("\nLista Simpla dupa creare:\n");
	t = pList;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}

	struct Angajat* vang;
	unsigned char size;
	vang = copiere_angajati(pList, &size);

	// dezalocare lista simpla
	pList = dezalocare_lista(pList);
	printf("\nLista Simpla dupa dezalocare:\n");
	t = pList;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}

	// consultare continut vector de angajati
	printf("\nContinut vector de angajati:\n");
	for (unsigned char i = 0; i < size; i++)
		printf("\t%s\n", vang[i].nume);

	// dezalocare vector de angajati
	for (unsigned char i = 0; i < size; i++)
	{
		free(vang[i].nume);
	}
	free(vang);
	vang = NULL;

	fclose(f);
}