#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct Client
{
	char* nume;			// 4 bytes
	unsigned int id;	// 4 bytes
	unsigned char tip;	// 1 bytes
	unsigned int puncte;// 4 bytes
	float medie_cos;	// 4 bytes
};

typedef struct Client Client;

struct NodD
{
	Client cl;
	struct NodD* prev, *next;
};

typedef struct NodD NodD;

struct ListaDubla
{
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserareAscId(ListaDubla lista, Client c)
{
	NodD* nou = malloc(sizeof(NodD));
	nou->cl = c; // datele sunt salvate in nod alocat in heap seg

	if (lista.prim == NULL)
	{
		// lista este empty; nou devine primul si unicul nod din lista
		nou->next = NULL;
		nou->prev = NULL;
		lista.prim = lista.ultim = nou;
	}
	else
	{
		NodD* t = lista.prim;
		while (t)
		{
			if (t->cl.id > nou->cl.id)
			{
				NodD* p = t->prev; // p este nodul din fata lui t; nou se insereaza intre p si t
				nou->next = t;
				nou->prev = p;
				t->prev = nou;
				if (p == NULL)
				{
					// nou va fi inserat pe pozitia 1 din lista dubla
					lista.prim = nou;
				}
				else {
					p->next = nou;
				}
				return lista; // pentru a nu continua cautarea pozitiei de inserat, operatia fiind deja efectuata mai sus
			}

			t = t->next;
		}
		
		// t este NULL, deci nou va fi inserat pe ultima pozitie din lista dubla
		nou->next = NULL;
		nou->prev = lista.ultim;

		lista.ultim->next = nou; // succesorului lui ultim va fi nou dupa inserare lui nou la sfarsit lista dubla
		lista.ultim = nou;
	}

	return lista;
}

void traversareListaDubla(ListaDubla lista)
{
	NodD* t = lista.prim;
	printf("Traversare lista dubla prim->ultim:\n");

	while (t != NULL)
	{
		printf("%d %s\n", t->cl.id, t->cl.nume);

		t = t->next;
	}

	printf("Traversare lista dubla ultim->prim:\n");
	t = lista.ultim;
	while (t != NULL)
	{
		printf("%d %s\n", t->cl.id, t->cl.nume);
		t = t->prev;
	}
}

ListaDubla stergereNodDCosMediu(ListaDubla lista, float cos_mediu)
{
	NodD* t = lista.prim;

	while (t != NULL)
	{
		if (t->cl.medie_cos == cos_mediu)
		{
			// t este nodul care se sterge
			NodD* p, * r;
			p = t->prev;
			r = t->next;

			free(t->cl.nume);
			free(t); // dezalocare nod lista dubla

			if (p == NULL && r == NULL)
			{
				// nodul t care se sterge este primul, ultimul si unicul nod in lista dubla
				lista.prim = lista.ultim = NULL; // lista dubla devine empty
				t = NULL;
			}
			else
			{
				if (p == NULL)
				{
					// t este primul nod din lista
					r->prev = p;
					lista.prim = r;
					t = r;
				}
				else
				{
					if (r == NULL)
					{
						// t este ultimul nod din lista dubla
						p->next = r;
						lista.ultim = p;
						t = NULL;
					}
					else
					{
						// caz general
						p->next = r;
						r->prev = p;

						t = r; // actualizare t curent pentru a fi verificat in iteratia urmatoare
					}
				}
			}
		}
		else
			t = t->next;
	}

	return lista;
}

ListaDubla interschimbAdiacentePozitie(ListaDubla list, unsigned short int poz)
{
	if (list.prim != list.ultim)
	{
		// lista dubla contine cel putin doua noduri
		unsigned short int counter = 1;
		NodD* t = list.prim;

		while (t->next != NULL)
		{
			if (counter < poz)
			{
				t = t->next;
				counter += 1;
			}
			else
			{
				NodD* p, * q, * r;
				p = t->prev;
				q = t->next;
				r = q->next;

				if (t != list.prim && t != list.ultim->prev)
				{
					// t nu este nici unul din cele doua capete ale listei duble
					p->next = q;
					t->next = r;
					q->next = t;

					t->prev = q;
					q->prev = p;
					r->prev = t;
				}
				else
				{
					q->next = t;
					t->prev = q;
					if (t == list.prim && t == list.ultim->prev)
					{
						// lista dubla contine doar doua noduri care se interschimba
						t->next = NULL;
						q->prev = NULL;

						list.prim = q;
						list.ultim = t;
					}
					else
					{
						t->next = r;
						q->prev = p;
						if (t == list.prim)
						{
							// t este primul nod din lista
							r->prev = t;

							list.prim = q;
						}
						else
						{
							// t este penultimul nod din lista
							p->next = q;

							list.ultim = t;
						}
					}
				}

				return list;
			} // else
		}
	}

	return list;
}




int main()
{
	ListaDubla lista;
	lista.prim = NULL;
	lista.ultim = NULL;

	FILE* f;

	f = fopen("Clienti.txt", "r");

	char buffer[256];
	char seps[] = ",\n"; // \n pentru a considera 0x0a separat astfel incat 0x0a sa nu fie parte a ultimul token

	while (fgets(buffer, sizeof(buffer), f)) // citire linie din fisier text si salvare continut linie in buffer
	{
		Client client; // variabila temporara in care sunt pregatite datele clientului conform tipuri de date din structura
		char* token = strtok(buffer, seps); // debut proces de tokenizare; buffer este bytearray care se sparge in tokeni separati de bytes conformseps
		client.nume = malloc(strlen(token) + 1); // alocare heap seg pentru fix lungimes string nume client
		strcpy(client.nume, token); //copiere string in heap seg tocmai alocat

		token = strtok(NULL, seps); // argumentul NULL asigura continarea procesului de tokenizare de la ultima pozitie a separatorului
		client.id = atoi(token); // conversie ASCII la int

		token = strtok(NULL, seps);
		client.tip = token[0]; // tip client stocheaza codul ASCII (simbolul)

		token = strtok(NULL, seps);
		client.puncte = atoi(token); // conversie ASCII la intreg

		token = strtok(NULL, seps);
		client.medie_cos = (float)atof(token); // conversie ASCII la float

		lista = inserareAscId(lista, client); // inserare date client in nod lista dubla
	} // variabila temporara client este dezalocata din stack seg dupa fiecare apel de inserare nod

	fclose(f);

	// traversare in ambele sensuri a listei duble
	printf("Lista dubla dupa creare:\n");
	traversareListaDubla(lista);

	lista = interschimbAdiacentePozitie(lista, 1);
	printf("\n\nLista dubla dupa interschimb adiacente pe baza de pozitie:\n");
	traversareListaDubla(lista);

	// stergere nod din lista dubla pe baza medie cos
	lista = stergereNodDCosMediu(lista, (float)289.91);
	printf("\n\nLista dubla dupa stergere nod cos mediu:\n");
	traversareListaDubla(lista);

	// dezalocare lista dubla
	while (lista.prim != NULL)
	{
		lista = stergereNodDCosMediu(lista, lista.prim->cl.medie_cos);
	}
	printf("\n\nLista dubla dupa dezalocare noduri:\n");
	traversareListaDubla(lista);

	return 0;
}