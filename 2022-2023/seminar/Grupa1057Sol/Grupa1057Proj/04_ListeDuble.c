#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define VECTOR_SIZE 10
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[25];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct NodD_CB
{
	struct ContBancar cb;
	struct NodD_CB *prev, *next;
};

struct ListaDubla
{
	struct NodD_CB* p, * u;
};

struct ListaDubla inserare_inceputLD(struct ListaDubla lst, struct ContBancar cb)
{
	struct NodD_CB* nou = (struct NodD_CB*)malloc(sizeof(struct NodD_CB));

	nou->cb = cb;
	nou->cb.titular = (char*)malloc(strlen(cb.titular) + 1);
	strcpy(nou->cb.titular, cb.titular);

	nou->prev = NULL;
	nou->next = lst.p;

	if (lst.p == NULL)
	{
		// lista dubla empty
		lst.p = lst.u = nou;
	}
	else
	{
		// exista cel putin 1 nod in lista dubla
		lst.p->prev = nou;
		lst.p = nou;
	}

	return lst;
}


// inserare nod in interiorul LD astfel incat conturile bancare sunt sortare crescator/descrescator pe sold

// stergere nod (cu extragere date cont bancar) de pe o pozitie specificata in lista dubla

// interschimbare noduri oarecare in lista dubla (cu modificarea adreselor de legatura/succesiunii de noduri) 

struct ListaDubla insterschimb_noduri(struct ListaDubla lst, unsigned char poz1, unsigned char poz2)
{
	if (poz1 && poz2 && poz1 != poz2)
	{
		// poz1 si poz2 nu sunt nuli
		// poz1 si poz 2 nu sunt egale
		if (poz1 > poz2)
		{
			// interschimb poz1 cu poz2 pentru a avea in poz1 prima pozitie de interschimb
			unsigned char t = poz1;
			poz1 = poz2;
			poz2 = t;
		}

		// traversare lista si pozitionare pe poz1 si poz2
		struct NodD_CB* temp, *q = NULL, *t = NULL;
		unsigned char i = 1;
		temp = lst.p;
		while (!q && temp)
		{
			if (i == poz1)
			{
				q = temp;
			}

			temp = temp->next;
			i += 1;
		}
		if (temp)
		{
			// exista poz1
			while (!t && temp)
			{
				if (i == poz2)
				{
					t = temp;
				}

				temp = temp->next;
				i += 1;
			}

			if (t && q)
			{
				// exista poz1 si poz2
				struct NodD_CB* p, * r, * s, * u;

				p = q->prev;
				r = q->next;

				s = t->prev;
				u = t->next;

				if (poz2 != poz1 + 1)
				{
					// q si t nu sunt adiacente
					// modificari comune adrese de legatura 
					t->next = r;
					t->prev = p;

					r->prev = t;
					s->next = q;

					q->next = u;					
					q->prev = s;
					if (p == NULL)
					{
						lst.p = t; // poz1 este 1
						if (u == NULL)
						{
							// se interschimba primul cu ultimul nod
							lst.u = q;
						}
						else
						{
							// se interschimba primul cu oarecare
							u->prev = q;
						}
					}
					else
					{
						p->next = t; // exista p
						if (u == NULL)
						{
							// poz2 este pe ultimul nod din lista
							lst.u = q;
						}
						else
						{
							// cazul general; noduri oarecare din lista
							u->prev = q;
						}
					}
				}
				else
				{
					// q si t sunt adiacente
					t->next = q;
					t->prev = p;
					q->prev = t;
					q->next = u;
					if (p == NULL)
					{
						lst.p = t; // poz1 este 1
						if (u == NULL)
						{
							// se interschimba primul cu ultimul nod
							lst.u = q;
						}
						else
						{
							// se interschimba primul cu oarecare
							u->prev = q;
						}
					}
					else
					{
						p->next = t; // exista p
						if (u == NULL)
						{
							// poz2 este pe ultimul nod din lista
							lst.u = q;
						}
						else
						{
							// cazul general; noduri oarecare din lista
							u->prev = q;
						}
					}
				}
			}
		}
	}

	return lst;
}

int main()
{

	struct ContBancar cb, vcb[VECTOR_SIZE];
	FILE* f;
	unsigned int i = 0;
	unsigned char nr_conturi;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		char* token;
		token = strtok(buffer, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1); // +1 pentru terminat de string, adica byte 0x00
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		strcpy(cb.moneda, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		cb.nr_carduri = atoi(token);

		vcb[i++] = cb;
	}
	fclose(f);

	struct ListaDubla lista;
	lista.p = lista.u = NULL;

	nr_conturi = (unsigned char)i;
	for (i = 0; i < nr_conturi; i++)
	{
		lista = inserare_inceputLD(lista, vcb[i]);
	}

	// parsare lista dubla in ambele sensuri
	struct NodD_CB* temp = lista.p;
	printf("Traversare lista dubla 1 -> n: \n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);

		temp = temp->next;
	}

	temp = lista.u;
	printf("Traversare lista dubla n -> 1: \n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);

		temp = temp->prev;
	}

	lista = insterschimb_noduri(lista, 1, 2);
	printf("\n\nLista dupa interschimb noduri:\n");
	temp = lista.p;
	printf("Traversare lista dubla 1 -> n: \n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);

		temp = temp->next;
	}

	temp = lista.u;
	printf("Traversare lista dubla n -> 1: \n");
	while (temp)
	{
		printf("%s %.2f\n", temp->cb.titular, temp->cb.sold);

		temp = temp->prev;
	}
}