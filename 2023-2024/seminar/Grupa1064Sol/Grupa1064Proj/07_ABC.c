#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define HTABLE_SIZE 200

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

struct NodABC
{
	unsigned short int cheie;
	struct ContBancar data;
	struct NodABC* st, *dr;
};


typedef struct ContBancar ContBancar;
typedef struct NodABC NodABC;

NodABC* inserare_nod_arbore(NodABC* r, ContBancar contB, 
						unsigned short int key, unsigned char* flag)
{
	if (r != NULL)
	{
		if (key < r->cheie)
		{
			r->st = inserare_nod_arbore(r->st, contB, key, flag);
		}
		else
		{
			if (key > r->cheie)
			{
				r->dr = inserare_nod_arbore(r->dr, contB, key, flag);
			}
			else
			{
				*flag = 0; // flag setat pe ESEC!
			}
		}
	}
	else
	{
		// locul unde nodul nou se insereaza
		NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
		nou->cheie = key;
		nou->data = contB;
		nou->st = NULL;
		nou->dr = NULL;

		*flag = 1; // flag setat pe SUCCES!
		r = nou;
	}

	return r;
}

void inordine(NodABC* r)
{
	if (r)
	{
		inordine(r->st);
		printf("%d ", r->cheie);
		inordine(r->dr);
	}
}

int main()
{
	FILE* f = fopen("ConturiABC.txt", "r");
	NodABC* root = NULL; // arbore binar de cautare empty
	unsigned short int key;
	char nume_buff[128];

	struct ContBancar contB;
	fscanf(f, "%hu", &key);
	while (key != 0)
	{
		fscanf(f, "%s\n", contB.iban);

		fscanf(f, "%[^\n]", nume_buff);
		contB.titular = (char*)malloc(strlen(nume_buff) + 1);
		strcpy(contB.titular, nume_buff);

		fscanf(f, "%s", contB.moneda);
		fscanf(f, "%f", &contB.sold);

		// inserare cont bancar in arbore binar de cautare
		unsigned char inserat = 0;
		root = inserare_nod_arbore(root, contB, key, &inserat);
		if (inserat != 0)
		{
			contB.titular = NULL; // pentru a elimina partajarea dintre ultimul nod inserat si contB
			contB.iban[0] = 0;
		}
		else
		{
			// contul bancar nu a fost inserat in ABC
			free(contB.titular); // dezalocare mem heap pt titular
		}
		key = 0; // reinitializare cheie pentru a verifica existenta urmatorului cont bancar in fisier

		fscanf(f, "%hu", &key);
	}

	printf("Arbore dupa creare: ");
	inordine(root);
	printf("\n\n");

	// TODO: cautare cont bancar dupa cheie

	// TODO: cautare cont bancar dupa iban

	// TODO: dezalocare ABC

	fclose(f);
	return 0;
}