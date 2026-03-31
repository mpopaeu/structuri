#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Angajat {
	char* nume;
	char id[5]; // 1 byte rezervat pentru terminatorul de string
	unsigned char varsta;
	float salariu;
	char* functie;
};

typedef struct Angajat Angajat;

struct NodD {
	Angajat ang;
	struct NodD * next, *prev;
};

typedef struct NodD NodD;

struct ListaDubla {
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserareNodLD(ListaDubla list, Angajat a)
{
	NodD* nou = malloc(sizeof(NodD));
	nou->ang = a;
	nou->next = NULL;
	nou->prev = list.ultim;

	if (list.prim == NULL)
	{
		// lista dubla este empty (zero elemente in structura)
		list.prim = list.ultim = nou; // nou este primul, ultimul si unicul nod in lista dubla
	}
	else
	{
		// exista cel putin un nod in lista dubla
		list.ultim->next = nou;
		list.ultim = nou; // nou sfarsit de lista dubla
	}

	return list;
}

void traversare(ListaDubla list)
{
	printf("Lista dubla prim->ultim:\n");
	NodD* t = list.prim;
	while (t)
	{
		printf("%s %s\n", t->ang.id, t->ang.nume);
		t = t->next;
	}

	printf("\n\nLista dubla ultim->prim:\n");
	t = list.ultim;
	while (t)
	{
		printf("%s %s\n", t->ang.id, t->ang.nume);
		t = t->prev;
	}
}

ListaDubla stergereIdAngajat(ListaDubla list, char* id_cautat)
{
	NodD* t = list.prim;

	while (t)
	{
		if (strcmp(t->ang.id, id_cautat) == 0)
		{
			// nodul t trebuie eliminat din lista dubla
			NodD* p = t->prev;
			NodD* q = t->next;

			if (p && q)
			{
				// t este nod la interior
				p->next = q;
				q->prev = p;
			}
			else
			{
				if (p == NULL && q == NULL)
				{
					// nodul t (de sters) este unicul din lista dubla
					list.prim = list.ultim = NULL; // lista devine empty
				}
				else
				{
					if (p == NULL)
					{
						// nodul t este primul din lista dubla; q exista si devine noul inceput de lista
						q->prev = NULL;
						list.prim = q;
					}
					else
					{
						// nodul t este ultimul nod din lista dubla; p exista si devine noul sfarsit de list
						p->next = NULL;
						list.ultim = p;
					}
				}
			}

			free(t->ang.nume);   // dezalocare string nume angajat
			free(t->ang.functie);// dezalocare string functie angajat
			free(t);			 // dezalocare structura NodD

			return list;
		}

		t = t->next; // actualizeaza t cu succesor
	}

	return list;
}

ListaDubla interschimbNoduriIdAngajat(ListaDubla list, char* id_ang1, char* id_ang2)
{
	if ((list.prim != NULL) && (list.prim != list.ultim))
	{
		// exista cel putin 2 noduri in lista dubla
		NodD* p = list.prim;
		while (p && (strcmp(p->ang.id, id_ang1) != 0) &&
			(strcmp(p->ang.id, id_ang2) != 0)) // caut primul nod cu unul din cele doua id angajat
		{
			p = p->next;
		}

		if (p)
		{
			// a fost identificat primul nod (p)
			char* id_next;
			if (strcmp(p->ang.id, id_ang1) == 0)
				id_next = id_ang2; // id_2 este urmatorul angajat de identificat
			else
				id_next = id_ang1;

			NodD* q = p->next;
			while (q && (strcmp(q->ang.id, id_next) != 0))
				q = q->next;

			if (q)
			{
				// cele doua noduri (p, q) au fost identificate in lista dubla
				NodD* t, * v, * r, * s;

				t = p->prev;
				v = p->next;
				r = q->prev;
				s = q->next;

				if (p == list.prim && q == list.ultim)
				{
					// se interschimba primul si ultimul nod din lista dubla
					if (list.ultim == list.prim->next)
					{
						// lista are 2 noduri care se interschimba
						// interschimb pozitii (1, 2)
						p->prev = q;
						q->next = p;
					}
					else
					{
						// interschimb pozitii (1, n), unde n este nr de noduri in lista dubla
						p->prev = r;
						q->next = v;	
						v->prev = q; // *
						r->next = p; // *
					}
					p->next = NULL;
					q->prev = NULL;
					list.prim = q;
					list.ultim = p;
				}
				else
				{
					if (p != list.prim && q != list.ultim)
					{
						// nu se modifica nici unul din cele doua capete ale listei duble
						q->prev = t;

						t->next = q;
						s->prev = p;

						if (p->next == q)
						{
							// interschimb pozitii (i, i + 1)
							p->next = s;
							p->prev = q;
							q->next = p;
						}
						else
						{
							// interschimb pozitii (i, j)
							p->next = s;
							p->prev = r;
							q->next = v;

							v->prev = q;
							r->next = p;
						}
					}
					else
					{
						if (p == list.prim)
						{
							q->prev = t;
							s->prev = p;
							if (p->next == q)
							{
								// interschimb (1, 2)
								p->next = s;
								p->prev = q;
								q->next = p;
							}
							else
							{
								// interschimb (1, j)
								p->next = s;
								p->prev = r;
								q->next = v;

								v->prev = q;
								r->next = p;				
							}
							list.prim = q; // actualizare inceput de lista dubla
						}
						else
						{
							q->prev = t;
							t->next = q;
							if (p->next == q)
							{
								// interschimb (n - 1, n), n este nr de noduri
								p->next = s;
								p->prev = q;
								q->next = p;
							}
							else
							{
								// interschimb (i, n), n este nr de noduri
								p->next = s;
								p->prev = r;
								q->next = v;

								v->prev = q;
								r->next = p;
							}
							
							list.ultim = p; // actualizare sfarsit de lista dubla
						}
					}
				}
			}

		}
	}

	return list;
}

// functie care extrage/sterge angajatii din lista dubla pe baza de functie
// angajatii extrasi sunt salvati in alta lista dubla
ListaDubla extragereAngajatiFunctie(ListaDubla* list, char* functie)
{

}

int main()
{
	ListaDubla listaD; // listaD variabila locala care include 2 adrese: adresa prim nod, adres ultim nod in lista dubla
	listaD.prim = listaD.ultim = NULL; // cele doua adrese nule indica o lista dubla empty

	FILE* f;

	f = fopen("Angajati.txt", "r");

	char buffer[256]; // byte array pentru stocare linie preluata din fisier
	char sep[] = ",\n"; // lista de separatori utilizata de strtok pentru identificare token (substring)
	Angajat angajat;
	while (fgets(buffer, sizeof(buffer), f)) // fgets returns NULL daca nu mai exista linie de preluat din fisier
	{
		char* token = strtok(buffer, sep); // param #1 buffer pentru a incepe cu primul byte din buffer
		angajat.nume = malloc(strlen(token) + 1); // alocare heap seg pentru stocare string num
		strcpy(angajat.nume, token);			  // copiere string in campul nume

		token = strtok(NULL, sep); // param #1 NULL pentru a continua tokenizare dn pozitia curenta
		strcpy(angajat.id, token); // copiere string in campul id (vector alocat la compilare)

		token = strtok(NULL, sep);
		angajat.varsta = atoi(token); // conversie text-to-integer

		token = strtok(NULL, sep);
		angajat.salariu = (float)atof(token); // conversie text-to-float

		token = strtok(NULL, sep);
		angajat.functie = malloc(strlen(token) + 1); // alocare heap seg pentru stocare string functie
		strcpy(angajat.functie, token);				 // copiere string in campul functie


		listaD = inserareNodLD(listaD, angajat); // inseare in lista dubla date pregatite in angajat 
	}

	fclose(f);

	printf("\nLista dubla dupa creare:\n");
	traversare(listaD);

	listaD = interschimbNoduriIdAngajat(listaD, "ID95", "ID31");
	printf("\nLista dubla dupa interschimb:\n");
	traversare(listaD);

	listaD = stergereIdAngajat(listaD, "ID94");
	printf("\nLista dubla dupa stergere nod pe baza de id angajat:\n");
	traversare(listaD);

	// dezalocare lista dubla print stergere repetata a primului nod
	while (listaD.prim)
	{
		listaD = stergereIdAngajat(listaD, listaD.prim->ang.id);
	}	
	printf("\nLista dubla dupa dezalocare:\n");
	traversare(listaD);


	return 0;
}