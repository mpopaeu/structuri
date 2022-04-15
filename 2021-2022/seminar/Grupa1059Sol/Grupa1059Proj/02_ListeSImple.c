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
	struct Nod* next; // adresa structura similara in abordare secventiala/liniara
};

// [in] list - lista in care se insereaza nod la sfarsit
// [in] a - date angajat care se insereaza in lista list
// [return] - adresa primul nod din lista simpla; diferita atunci cand list este NULL
struct Nod* inserare_sfarsit(struct Nod* list, struct Angajat a)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = a;
	nou->next = NULL;

	if (list == NULL)
		return nou;
	else
	{
		struct Nod* t = list;

		while (t->next != NULL)
			t = t->next;
		t->next = nou;
	}
	return list;
}

// [in] list - lista simpla de angajati care se exporta
// [out] vang - vector de angajati alocat si populat in functie
// [out] dim_vector - nr elemente din vang
// [return] lista simpla empty (list == NULL); lista se dezaloca in functie
struct Nod* export_angajati(struct Nod* list, struct Angajat * *vang, unsigned char * dim_vector)
{
	*dim_vector = 0;
	struct Nod* t = list;
	while (t)
	{
		*dim_vector += 1;
		t = t->next;
	}

	*vang = (struct Angajat*)malloc(*dim_vector * sizeof(struct Angajat));
	unsigned char k = 0;
	t = list;
	while (t)
	{
		(*vang)[k++] = t->ang; // copiere angajat din nodul curent t in elementul k din vector
		t = t->next;
	}

	// dezalocare lista simpla
	while (list)
	{
		t = list;
		list = list->next;
		free(t);
	}

	return list;
}

// stergere nod interior; criteriu: cod angajat
// [in] list - lista simpla in care se sterge nod
// [in] cod_angajata - codul angajatului care se sterge
// [out] angajat_extras - date angajat extrase din nodul sters; daca stergere nu se realizeaza, angajat are nume NULL
// [return] posibil noua adresa de inceput a listei simple, daca nodul de sters este primul
struct Nod* stergere_nod(struct Nod* list, unsigned short int cod_angajat, struct Angajat *angajat_extras)
{
	angajat_extras->nume = NULL;
	if (list)
	{
		struct Nod* t;
		if (list->ang.cod == cod_angajat) // nosul sters este primul in lista
		{
			*angajat_extras = list->ang;
			t = list;
			list = list->next;
			free(t);
		}
		else
		{
			t = list;
			while (t->next && t->next->ang.cod != cod_angajat)
				t = t->next;

			if (t->next)
			{
				struct Nod* q = t->next;
				t->next = q->next;
				*angajat_extras = q->ang;
				free(q);
			}
		}
	}

	return list;
}

// liste duble (operatiile de mai sus)

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	struct Angajat fang;
	char nume[64];

	struct Nod* pList = NULL;

	fscanf(f, "%hu,", &fang.cod);
	while (!feof(f))
	{
		fscanf(f, "%[^,],%f\n", nume, &fang.salariu);

		fang.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		pList = inserare_sfarsit(pList, fang);

		fscanf(f, "%hu,", &fang.cod);
	}

	fang.nume = NULL;

	// testare continut lista simpla
	struct Nod* t;
	printf("\n Lista simpla dupa creare:\n");
	t = pList;
	while (t)
	{
		printf(" %s \n", t->ang.nume);
		t = t->next;
	}
	
	// inserare inceput/interior	

	// stergere inceput/sfarsit/interior

	pList = stergere_nod(pList, 1999, &fang);
	printf("\nAngajat extras: \n");
	if (fang.nume)
	{
		printf(" %s \n", fang.nume);
	}
	printf("\n Lista simpla dupa stergere nod interior:\n");
	t = pList;
	while (t)
	{
		printf(" %s \n", t->ang.nume);
		t = t->next;
	}


	// export angajati in vector
	struct Angajat* vector_angajati;
	unsigned char size_vector;
	pList = export_angajati(pList, &vector_angajati, &size_vector);

	printf("\n\n Continut vector angajati dupa export:\n");
	for (unsigned char i = 0; i < size_vector; i++)
	{
		printf(" %s \n", vector_angajati[i].nume);
	}
	printf("\n Lista simpla dupa export:\n");
	t = pList;
	while (t)
	{
		printf(" %s \n", t->ang.nume);
		t = t->next;
	}

	// dezalocare structura lista simpla

	// dezalocare vector angajati
	for (unsigned char i = 0; i < size_vector; i++)
		free(vector_angajati[i].nume);
	free(vector_angajati);
	vector_angajati = NULL;

	fclose(f);
}