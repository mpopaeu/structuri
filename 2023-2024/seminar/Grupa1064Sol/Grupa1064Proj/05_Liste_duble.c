#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

struct NodLD
{
	struct ContBancar *pcb;
	struct NodLD* next, *prev;
};

typedef struct ContBancar ContBancar;
typedef struct NodLD NodLD;

struct ListaDubla
{
	NodLD* p, * u;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserare_sfarsit(ListaDubla lista, ContBancar* pcont)
{
	NodLD* nou = (NodLD*)malloc(sizeof(NodLD));
	nou->pcb = pcont;
	nou->next = NULL;

	if (lista.p == NULL)
	{
		// lista este empty
		nou->prev = NULL;
		lista.p = lista.u = nou;
	}
	else
	{
		// lista contine cel putin 1 nod
		nou->prev = lista.u;
		lista.u->next = nou;
		lista.u = nou;
	}

	return lista;
}

struct IBAN
{
	char iban[25];
};
typedef struct IBAN IBAN;

// salvare conturi bancare cu aceeasi moneda
// conturile bancare sunt stocate in lista dubla
// functia intoarce vectorul: elemente de tip IBAN

IBAN* salveaza_conturi_vector(ListaDubla lista, char * currency, unsigned char *n)
{
	*n = 0;
	NodLD* temp = lista.p;
	while (temp)
	{
		if (strcmp(temp->pcb->moneda, currency) == 0)
			*n += 1;
		temp = temp->next;
	}

	IBAN* vector = (IBAN*)malloc((*n) * sizeof(IBAN));

	unsigned char i = 0;
	temp = lista.p;

	while (temp)
	{
		if (strcmp(temp->pcb->moneda, currency) == 0)
		{
			strcpy(vector[i].iban, temp->pcb->iban);
			i += 1;
		}
		temp = temp->next;
	}

	return vector;
}

// interschimb noduri adiacente in lista dubla pe baza de pozitie [i,i+1]

// interschimb noduri oarecare in lista dubla pe baza de pozitie [i,j]

// sortare lista dubla (folosind interschimbare de mai sus)

int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	ListaDubla listaD;
	listaD.p = listaD.u = NULL; // lista dubla este empty

	char nume_buff[128];
	struct ContBancar contB;
	fscanf(f, "%s\n", contB.iban);
	while (strlen(contB.iban))
	{
		fscanf(f, "%[^\n]", nume_buff);
		contB.titular = (char*)malloc(strlen(nume_buff) + 1);
		strcpy(contB.titular, nume_buff);

		fscanf(f, "%s", contB.moneda);
		fscanf(f, "%f", &contB.sold);

		ContBancar* pContB = (ContBancar*)malloc(sizeof(ContBancar));
		*pContB = contB;

		// inserare cont bancar in lista dubla
		listaD = inserare_sfarsit(listaD, pContB);

		contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
		contB.iban[0] = 0;
		fscanf(f, "%s\n", contB.iban);
	}

	// traversare lista dubla in ambele sensuri
	NodLD* temp = listaD.p;
	printf("Lista dubla prim->ultim:\n");
	while (temp)
	{
		printf("%s %s\n", temp->pcb->iban, temp->pcb->titular);
		temp = temp->next;
	}
	printf("Lista dubla ultim->prim:\n");
	temp = listaD.u;
	while (temp)
	{
		printf("%s %s\n", temp->pcb->iban, temp->pcb->titular);
		temp = temp->prev;
	}

	// salvare conturi bancare in vector de IBAN-uri
	unsigned char size = 0;
	IBAN* conturi = salveaza_conturi_vector(listaD, "EUR", &size);
	printf("Conturi bancare in EUR:\n");
	for (unsigned char i = 0; i < size; i++)
		printf("%s\n", conturi[i].iban);

	// dezalocare lista dubla
	while (listaD.p)
	{
		temp = listaD.p;
		listaD.p = listaD.p->next;
		if(listaD.p != NULL)
			listaD.p->prev = NULL;

		free(temp->pcb->titular); // dezalocare string pt titular
		free(temp->pcb);		  // dezalocare ContBancar
		free(temp);				  // dezalocare nod lista dubla (NodLD)
	}
	listaD.u = NULL;

	printf("Lista dubla ultim->prim dupa dezalocare:\n");
	temp = listaD.u;
	while (temp)
	{
		printf("%s %s\n", temp->pcb->iban, temp->pcb->titular);
		temp = temp->prev;
	}

	//dezalocare vector de conturi bancare
	free(conturi);
	conturi = NULL;

	fclose(f);
	return 0;
}