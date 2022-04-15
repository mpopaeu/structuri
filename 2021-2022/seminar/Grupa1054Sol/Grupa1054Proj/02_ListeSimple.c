
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

struct Nod
{
	struct Angajat ang;
	struct Nod* next;
};

#define LINE_SIZE 128

// [in] list - adresa primului nod in care se efectueaza inserare la sfarsit
// [in] new_ang - date angajat care se insereaza la sfarsitul listei
// [return] - adresa (eventual noua la inserare nod in lista empty) primului nod din lista simpla
struct Nod* inserare(struct Nod* list, struct Angajat new_ang)
{
	struct Nod* nou;
	nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->ang = new_ang;
	nou->next = NULL; // nodul nou va fi ultimul din lista

	if (list == NULL) // lista contine 0 noduri
		return nou;
	else
	{
		struct Nod* t = list;
		while (t->next) // parsare lista simpla pana pe ultimul nod (t->next == NULL)
			t = t->next;
		t->next = nou; // "legarea" nodului nou la lista existenta
	}
	return list;
}

// inserare nod la inceput

// inserare nod in interior; criteriul: cod angajat
// [in] list -  adresa primului nod in care se efectueaza inserare la interior
// [in] new_ang - date angajat care se insereaza la interior dupa cod existent / sfarsitul listei
// [in] cod_cautat - codul dupa care se efectueaza inserare in lista
// [return] - adresa (eventual noua la inserare nod in lista empty) primului nod din lista simpla
struct Nod* inserare_interior_cod(struct Nod* list, struct Angajat new_ang, unsigned short int cod_cautat)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->ang = new_ang;

	if (!list)
	{
		nou->next = NULL;
		return nou; // nodul nou este primul si unicul din lista simpla
	}
	else
	{
		struct Nod* t = list;
		unsigned char inserat = 0;
		while (!inserat && t->ang.cod != cod_cautat)
		{
			if (t->next != NULL)
				t = t->next;
			else
				inserat = 1; // nu a fost gasit cod in lista simpla; inserare la sfarsit
		}

		// t este pe nodul care se leaga pe succesor cu nou
		nou->next = t->next;
		t->next = nou;
	}

	return list;
}


// stergere nod inceput/sfarsit/interior (definiti criteriul)
// [in] list - lista simpla de angajati
// [in] cod_cautat - cod angajat care se extrage din lista simpla list
// [out] ang_extras - structura Angajat care stocheaza datele unui angajat din nodul sters din lista simpla list
// [return] - posibil noua adresa de inceput a listei simple (daca nodul 1 este cel sters)
struct Nod* stergere_angajat(struct Nod* list, unsigned short int cod_cautat, struct Angajat * ang_extras)
{
	if (list) // exista cel putin 1 nod in lista simpla
	{
		struct Nod* t = list; // salvare nod 1 in t
		if (list->ang.cod == cod_cautat)
		{
			// angajatul de sters/extras se afla in primul nod
			*ang_extras = list->ang; // salvare date angajat din primul nod			
			list = list->next; // noul inceput de lista este actualizat pe nodul 2
			free(t); // dezalocare inceput de lista (nodul 1 la intrarea in functie)
		}
		else
		{
			// se cauta angajatul de extras incepand cu nodul 2
			while (t->next && t->next->ang.cod != cod_cautat)
				t = t->next;

			if (t->next)
			{
				// a fost identificat nodul de sters
				*ang_extras = t->next->ang; // salvare date angajat
				struct Nod* q = t->next;
				t->next = q->next;
				free(q);
			}

		}
	}

	return list;
}

// export angajati in vector


// de finalizat operatii pe lista simple
// de adaugat implementari pe lista duble

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r+");
	char buffer_linie[LINE_SIZE], nume[64];
	struct Angajat fang;
	struct Nod* pList = NULL;

	fscanf(f, "%[^,],", nume);
	while (!feof(f))
	{
		fscanf(f, "%hu,%f\n", &fang.cod, &fang.salariu);

		fang.nume = malloc(sizeof(char) * (strlen(nume) + 1));
		strcpy(fang.nume, nume);

		pList = inserare(pList, fang);
		fscanf(f, "%[^,],", nume);		
	}

	printf("\nContinut lista simpla de angajati:\n");
	struct Nod* tmp = pList;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	// inserare nod la interior in lista simpla
	fang.cod = 1500;
	fang.salariu = 4789.00;
	fang.nume = (char*)malloc((strlen("Vasilescu Marian") + 1) * sizeof(char));
	strcpy(fang.nume, "Vasilescu Marian");

	pList = inserare_interior_cod(pList, fang, 1000);

	printf("\nContinut lista simpla de angajati dupa inserare la interior in functie de cod:\n");
	tmp = pList;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	fang.nume = NULL;
	fang.cod = 0;
	fang.salariu = 0.0;

	pList = stergere_angajat(pList, 1789, &fang);
	printf("\n\nAngajat extras:");
	if (fang.nume)
	{
		printf(" %s\n", fang.nume);
	}

	printf("\n\nContinut lista simpla de angajati dupa stergere/extragere in functie de cod:\n");
	tmp = pList;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	
	// dezalocare nume angajat axtras
	free(fang.nume);
	fang.nume = NULL;

	// dezalocare lista simpla
	while (pList)
	{
		fang.nume = NULL;
		pList = stergere_angajat(pList, pList->ang.cod, &fang);
		free(fang.nume);
	}


	printf("\n\nContinut lista simpla de angajati dupa dezalocare:\n");
	tmp = pList;
	while (tmp)
	{
		printf("\n%s", tmp->ang.nume);
		tmp = tmp->next;
	}

	fclose(f);
}