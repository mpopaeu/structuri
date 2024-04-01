#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ContBancar {
	char iban[25]; // 24 dim iban + 1 byte pt 0x00
	float sold;
	char moneda[4]; // 3 dim cod moneda + 1 byte pt 0x00
	char* titular;
};

struct NodLD
{
	struct ContBancar* pcont;
	struct NodLD* next, *prev;
};

typedef struct NodLD NodLD;
typedef struct ContBancar ContBancar;


struct ListaDubla
{
	NodLD* p, * u;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserare_sfarsit(ListaDubla lista, ContBancar* pcb)
{
	NodLD* nod_nou = (NodLD*)malloc(sizeof(NodLD));

	nod_nou->pcont = pcb;
	nod_nou->next = NULL;

	if (lista.p == NULL)
	{
		// lista dubla empty
		nod_nou->prev = NULL;
		lista.p = lista.u = nod_nou;
	}
	else
	{
		// lista dubla contine cel putin 1 nod
		nod_nou->prev = lista.u;
		lista.u->next = nod_nou;
		lista.u = nod_nou;
	}

	return lista;
}

ListaDubla interschimb_adiacente(ListaDubla lista, char* cIBAN)
{
	if (lista.p && lista.p->next)
	{
		// exista cel putin 2 noduri in lista simpla
		if (strcmp(lista.p->pcont->iban, cIBAN) == 0)
		{
			// nodul cautat p este primul din lista dubla
			NodLD* p = lista.p, * q = p->next;
			...
			if (lista.u == q)
			{
				// se interschimba [1,2], unde lista dubla are 2 noduri
			}
			else
			{
				// se interschimba [1,2] unde lista dubla are cel putin 3 noduri
			}
		}
		else
		{
			if (strcmp(lista.u->prev->pcont->iban, cIBAN) == 0)
			{
				// nodul cautat p este penultimul din lista dubla
				// interschimb [n-1, n]
			}
			else
			{
				// cautare nod p in lista dubla (caz general) pana la n-1
				NodLD* p = lista.p;
				while (p->next)
				{

				}
			}
		}
	}

	return lista;
}

// interschimbare noduri oarecare in lista dubla cIBAN1, cIBAN2

// implementare algoritm de sortare pe lista dubla

int main()
{

	FILE* f = fopen("Conturi.txt", "r");

	char buffer[256], separatori[] = ",\n";
	ListaDubla lista;
	lista.p = lista.u = NULL; // initial, lista dubla este empty (0 noduri)

	while (fgets(buffer, sizeof(buffer), f))
	{
		struct ContBancar *pCont;
		pCont = (ContBancar*)malloc(sizeof(ContBancar));
		char* token = strtok(buffer, separatori);
		strcpy(pCont->iban, token);

		token = strtok(NULL, separatori);
		strcpy(pCont->moneda, token);

		token = strtok(NULL, separatori);
		pCont->titular = (char*)malloc(strlen(token) + 1);
		strcpy(pCont->titular, token);

		token = strtok(NULL, separatori);
		pCont->sold = (float)atof(token);

		// inserare cont bancar in lista dubla
		lista = inserare_sfarsit(lista, pCont);
	}

	// traversare lista dubla pentru validare continut
	printf("Lista dubla dupa creare prim->ultim:\n");
	NodLD* temp = lista.p;
	while (temp)
	{
		printf("%s %s\n", temp->pcont->iban, temp->pcont->titular);
		temp = temp->next;
	}

	// dezalocare lista dubla
	while ((lista.p != NULL) && (lista.u != NULL))
	{
		temp = lista.p;
		lista.p = lista.p->next;
		if (lista.p == NULL)
			lista.u = NULL;

		free(temp->pcont->titular); // dezalocare nume titular cont bancar
		free(temp->pcont);			// dezalocare mem heap pentru structura cont bancar
		free(temp);					// dezalocare nod din lista dubla
	}
	// traversare lista dubla pentru validare continut
	printf("Lista dubla dupa dezalocare ultim->prim:\n");
	temp = lista.u;
	while (temp)
	{
		printf("%s %s\n", temp->pcont->iban, temp->pcont->titular);
		temp = temp->prev;
	}

	fclose(f);
	return 0;
}
