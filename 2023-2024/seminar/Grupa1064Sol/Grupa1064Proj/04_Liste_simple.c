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

struct Nod
{
	struct ContBancar cb;
	struct Nod* next;
};

typedef struct ContBancar ContBancar;
typedef struct Nod Nod;

Nod* inserare_sfarsit(Nod* p, ContBancar cont)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->cb = cont;
	nou->next = NULL;

	if (p == NULL)
		return nou;

	Nod* t = p;
	while (t->next != NULL)
		t = t->next;
	// t este ultimul nod din lista simpla p
	t->next = nou;

	return p;
}

int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	Nod* prim = NULL;

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

		// inserare nod in lista simpla
		prim = inserare_sfarsit(prim, contB);

		contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
		contB.iban[0] = 0;
		fscanf(f, "%s\n", contB.iban);
	}

	Nod* t = prim;
	while (t != NULL)
	{
		printf("%s %s\n", t->cb.iban, t->cb.titular);
		t = t->next;
	}

	// dezalocare lista simpla
	// interschimb noduri lista simpla cu modificare adrese de legatura
	fclose(f);
	return 0;
}