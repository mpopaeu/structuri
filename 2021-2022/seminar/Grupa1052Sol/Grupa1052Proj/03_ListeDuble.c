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

// [in] list - lista dubla (pereche adrese inceput/sfarsit lista dubla)
// [in] tang - angajatul care se insereaza in LD
// [in] poz - pozitie viitoare a angajatului tang in LD
// [return] - LD actualizata dpv adresa inceput / adresa sfarsit
struct ListaDubla inserare_pozitie(struct ListaDubla list, struct Angajat tang, unsigned short int poz)
{
	unsigned short int nr_noduri = 0;
	struct NodD* tmp = list.prim;
	while (tmp)
	{
		nr_noduri += 1;
		tmp = tmp->next;
	}

	struct NodD* nou = (struct NodD*)malloc(sizeof(struct NodD));
	nou->ang = tang;

	if (list.prim == NULL) // lista dubla cu 0 noduri
	{
		nou->next = NULL;
		nou->prev = NULL;
		list.prim = list.ultim = nou; // nodul inserat va fi primul si unicul din LD
	}
	else
	{
		if (poz > nr_noduri)
		{
			// inserare la sfarsit in LD
			nou->next = NULL;
			nou->prev = list.ultim;
			list.ultim->next = nou;
			list.ultim = nou;
		}
		else
		{
			if (poz == 1)
			{
				// inserare la inceput in LD
				nou->next = list.prim;
				nou->prev = NULL;
				list.prim->prev = nou;
				list.prim = nou;
			}
			else
			{
				// cazul general de inserare; poz este pozitie viitoare
				tmp = list.prim;
				unsigned short int i = 1;
				while (i < poz)
				{
					i += 1;
					tmp = tmp->next;
				}

				nou->next = tmp;
				nou->prev = tmp->prev;
				tmp->prev->next = nou;
				tmp->prev = nou;
			}
		}
	}

	return list;
}

// [in] list - lista dubla (pereche adrese inceput/sfarsit lista dubla)
// [in] poz - pozitie nodului care se dezaloca in LD
// [return] - LD actualizata dpv adresa inceput / adresa sfarsit
struct ListaDubla stergere_pozitie(struct ListaDubla list, unsigned short int poz)
{
	struct NodD *tmp = list.prim;
	if (tmp)
	{ // LD contine cel putin 1 nod
		unsigned short int i = 1;
		while (tmp && i < poz)
		{
			i += 1;
			tmp = tmp->next;
		}
		if (tmp)
		{
			// exista nod pe pozitie poz; se efectueaza dezalocarea lui tmp
			if (!tmp->next && !tmp->prev)
			{
				// tmp este unicul nod din LD
				free(tmp->ang.nume); // dezalocare spatiu mem heap pt nume angajat
				free(tmp); // dezalocare nod in LD

				list.prim = list.ultim = NULL; // LD devine empty
			}
			else
			{
				if (!tmp->next)
				{
					// tmp este ultimul nod din LD
					list.ultim = list.ultim->prev;
					list.ultim->next = NULL;

					free(tmp->ang.nume);
					free(tmp);
				}
				else
				{
					if (!tmp->prev)
					{
						// tmp este primul nod in LD
						list.prim = list.prim->next;
						list.prim->prev = NULL;

						free(tmp->ang.nume);
						free(tmp);
					}
					else
					{
						// caz general; tmp este in interior LD
						struct NodD* p, * q;
						p = tmp->prev;
						q = tmp->next;

						p->next = q;
						q->prev = p;

						free(tmp->ang.nume);
						free(tmp);
					}
				}
			}
		
		}
	}

	return list;
}

// interschimbare noduri adiacente in LD (prin modificare legaturi)
// [in] list - lista dubla in care se aplica interschimb adiacente
// [in] poz - pozitia primului nod care se interschimba in lista dubla list
// [return] - lista dubla actualizata (adresele primului, respectiv ultimulu nod posibil modificate)
struct ListaDubla interschimb_adiacente(struct ListaDubla list, unsigned short int poz)
{
	struct NodD* tmp = list.prim;
	if (tmp && tmp->next)
	{ // LD contine cel putin 1 nod
		unsigned short int i = 1;
		while (tmp && i < poz)
		{
			i += 1;
			tmp = tmp->next;
		}
		if (tmp->next) // exista succesor pentru tmp
		{
			struct NodD* p, * q, * r;
			p = tmp->prev;
			q = tmp->next;
			r = q->next;

			tmp->next = r;
			tmp->prev = q;
			q->next = tmp;
			q->prev = p;

			if (tmp == list.prim)
			{
				// interschimb nodul 1 cu 2
				list.prim = q;
				if (q == list.ultim) // interschimb 1 cu 2 in LD cu 2 noduri
					list.ultim = tmp;
				else
					r->prev = tmp;
			}
			else
			{
				if (q == list.ultim)
				{
					// interschimb n-1 cu n
					list.ultim = tmp;
					p->next = q;
				}
				else
				{
					// cazul general; exista p si q
					p->next = q;
					r->prev = tmp;
				}
			}
		}
	}

	return list;
}

// interschimbare noduri adiacente in LD (prin modificare legaturi)
// [in] list - lista dubla in care se aplica interschimb adiacente
// [in] poz1 - pozitia primului nod care se interschimba in lista dubla list
// [in] poz2 - pozitia celui de al doilea nod care se interschimba in lista dubla list
// [return] - lista dubla actualizata (adresele primului, respectiv ultimului nod posibil modificate)
struct ListaDubla interschimb_oarecare(struct ListaDubla list, unsigned short int poz1, unsigned short int poz2)
{
}

// BubbleSort
// sortare prin selectie

void main()
{
	FILE* f;

	f = fopen("Angajati.txt", "r");
	struct Angajat fang;
	char buffer[128];

	struct ListaDubla lista;
	lista.prim = lista.ultim = NULL; // lista empty la definire

	unsigned short int nr_angajati = 0;

	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #1
	while (!feof(f) && nr_angajati < 2)
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		lista = inserare_pozitie(lista, fang, 1);

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
		nr_angajati += 1;
	}

	// parsare LS
	struct NodD* t;
	printf("\nLista dubla dupa creare:\n");
	t = lista.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla traversata invers:\n");
	t = lista.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}

	fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia #(nr_angajati-1)
	while (!feof(f) && nr_angajati < 4)
	{
		fscanf(f, "%[^,],%f\n", buffer, &fang.salariu);

		fang.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fang.nume, buffer);

		lista = inserare_pozitie(lista, fang, 2);

		fscanf(f, "%hu,", &fang.cod); // citire cod angajat linia urmatoare
		nr_angajati += 1;
	}

	printf("\nLista dubla dupa inserare angajat #%hu:\n", nr_angajati);
	t = lista.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla traversata invers:\n");
	t = lista.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}

	// stergere nod in LD pe baza pozitie specificata
	lista = stergere_pozitie(lista, 5);


	// interschimbare noduri adiacente in LD
	lista = interschimb_adiacente(lista, 2);
	printf("\nLista dubla dupa interschimbare angajati:\n");
	t = lista.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla dupa interschimbare traversata invers:\n");
	t = lista.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}

	fclose(f);
}