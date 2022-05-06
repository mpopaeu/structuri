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
struct ListaD stergere_criteriu(struct ListaD list, unsigned short int cod)
{
	if (list.prim)
	{
		struct NodD* tmp = list.prim;
		while (tmp)
		{
			if (tmp->ang.id % cod == 0)
			{
				// a fost identificat nod de sters (tmp)
				if (tmp->prev && tmp->next)
				{
					// nodul este in interiorul LD
					struct NodD* aux = tmp->next;
					tmp->prev->next = aux;
					aux->prev = tmp->prev;

					free(tmp->ang.nume);
					free(tmp);

					tmp = aux; // punctul din care se continua cautarea nodurilor de sters
				}
				else
				{
					if (!tmp->next && !tmp->prev)
					{
						// LD are un singur nod care trebuie sters
						free(tmp->ang.nume);
						free(tmp);
						list.prim = list.ultim = NULL;
						tmp = NULL;
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

							tmp = list.prim; // se continua cautarea nodurilor de sters incepand cu noul start de LD
						}
						else
						{
							// tmp este ultimul nod in LD
							list.ultim = list.ultim->prev;
							list.ultim->next = NULL;

							free(tmp->ang.nume);
							free(tmp);
							tmp = NULL; // nu mai exista noduri de verificat/sters
						}
					}
				}
			}
			else
				tmp = tmp->next;
		}
	}

	return list;
}

// completare cu implementari operatii de baza preluate de la liste simple
// operatii de baza cu liste circulare

// interschimbare noduri adiacente in LS si LD (modificare adrese de legatura)
struct ListaD interschimb_adiacente(struct ListaD list, unsigned short int i)
{
	if (list.prim != list.ultim)
	{
		// exista cel putin 2 noduri in LD
		unsigned short int k = 1;
		struct NodD* temp = list.prim;
		while (temp != list.ultim && k < i)
		{
			k += 1;
			temp = temp->next;
		}

		if (temp != list.ultim)
		{
			struct NodD* p, * q, * r;
			p = temp->prev;
			q = temp->next;
			r = q->next;

			temp->next = r;
			temp->prev = q;
			q->next = temp;
			q->prev = p;

			if (temp == list.prim)
			{
				// interschimb noduri (1, 2)
				list.prim = q;
				if (list.ultim == q)
				{
					// exista doar 2 noduri in LD
					list.ultim = temp;
				}
				else
				{
					// exista cel putin 3 noduri in lista, deci r nu este NULL
					r->prev = temp;
				}
			}
			else
			{	
				p->next = q;
				if (q == list.ultim)
				{
					// interschimb noduri (n-1, n)					
					list.ultim = temp;
				}
				else
				{
					// cazul general
					r->prev = temp;
				}
			}
		}
	}

	return list;
}

// interschimbare noduri oarecare in LD (modificare adrese de legatura)
struct ListaD interschimb_oarecare(struct ListaD list, unsigned short int i, unsigned short int j)
{
}

// BubbleSort
// sortare prin selectie

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

	printf("\nLista dubla dupa creare (prim->ultim)\n");
	struct NodD* t;
	t = listDubla.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla dupa creare (ultim->prim)\n");
	t = listDubla.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}


	struct Angajat* vang;
	//unsigned char size;

	//vang = export_angajati(&listDubla, &size);
	//printf("\nContinut vector de angajati:\n");
	//for (unsigned char i = 0; i < size; i++)
	//	printf("\t%s\n", vang[i].nume);

	//printf("\nLista dubla dupa export angajati:\n");
	//struct NodD* t;
	//t = listDubla.prim;
	//while (t)
	//{
	//	printf("\t%s\n", t->ang.nume);

	//	t = t->next;
	//}

	// listDubla = stergere_criteriu(listDubla, 5); // dezalocare v1: cod = 1 pentru dezalocarea intregii LD


	listDubla = interschimb_adiacente(listDubla, 5);
	printf("\nLista dubla dupa interschimb adiacente (prim->ultim)\n");
	t = listDubla.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla dupa interschimb adiacente (ultim->prim)\n");
	t = listDubla.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}


	// dezalocare v2: apel repatat functie stergere nod cu precizare cod angajat din nodul #1
	while (listDubla.prim)
	{
		listDubla = stergere_criteriu(listDubla, listDubla.prim->ang.id);
	}

	printf("\nLista dubla dupa stergere (inceput->sfarsit):\n");
	t = listDubla.prim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->next;
	}
	printf("\nLista dubla dupa stergere (sfarsit->inceput):\n");
	t = listDubla.ultim;
	while (t)
	{
		printf("\t%s\n", t->ang.nume);
		t = t->prev;
	}

	//// dezalocare vector de angajati
	//for (unsigned char i = 0; i < size; i++)
	//	free(vang[i].nume);
	//free(vang);
	vang = NULL;
	
}