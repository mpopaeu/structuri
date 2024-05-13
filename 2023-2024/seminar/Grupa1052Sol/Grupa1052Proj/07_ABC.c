#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ContBancar {
	unsigned short int cheie;
	char iban[25]; // 24 dim iban + 1 byte pt 0x00
	float sold;
	char moneda[4]; // 3 dim cod moneda + 1 byte pt 0x00
	char* titular;
};

struct NodABC
{
	struct ContBancar cont;
	struct NodABC *st, *dr;
};

typedef struct ContBancar ContBancar;
typedef struct NodABC NodABC;

NodABC* inserare_cont_ABC(NodABC* r, ContBancar data, unsigned char* inserat)
{
	if (r)
	{
		// continui cautarea locului de inserat
		if (r->cont.cheie > data.cheie)
			r->st = inserare_cont_ABC(r->st, data, inserat);
		else
			if (r->cont.cheie < data.cheie)
				r->dr = inserare_cont_ABC(r->dr, data, inserat);
			else
				*inserat = 0;

	}
	else
	{
		// am gasit locul de inserat pentru cont bancare data
		NodABC* nou = (NodABC*)malloc(sizeof(NodABC));
		nou->cont = data;
		nou->st = NULL;
		nou->dr = NULL;

		r = nou;
	}

	return r;
}

void inordine_ABC(NodABC * r)
{
	if (r)
	{
		inordine_ABC(r->st);
		printf("%d ", r->cont.cheie);
		inordine_ABC(r->dr);
	}
}

// I/ r nod din ABC (initial, r este nod redacina ABC
// I/ key cheia contului bancare care se cauta in ABC
// /O return adresa din NodABC a contului bancar cu key; altfel, NULL daca nu exista cont bancar cu key
ContBancar* cauta_cont_bancar(NodABC* r, unsigned short int key)
{
	ContBancar* pdata = NULL;
	if (r)
	{
		if (r->cont.cheie > key)
		{
			pdata = cauta_cont_bancar(r->st, key);
		}
		else
		{
			if (r->cont.cheie < key)
			{
				pdata = cauta_cont_bancar(r->dr, key);
			}
			else
			{
				pdata = &(r->cont);
			}
		}
	}

	return pdata;
}


NodABC* dezalocare_ABC(NodABC* r)
{
	if (r != NULL)
	{
		// parsare in post-ordine a ABC
		r->st = dezalocare_ABC(r->st);
		r->dr = dezalocare_ABC(r->dr);

		// dezalocare nod curent
		free(r->cont.titular);
		free(r);
		r = NULL;
	}

	return r;
}


// numarul de conturi bancare cu acelasi titular
unsigned char nr_conturi_titular(NodABC* r, char* titular)
{

}

int main()
{

	FILE* f = fopen("ContABC.txt", "r");

	char buffer[256], separatori[] = ",\n";
	NodABC* arbore = NULL; // retine adresa nodului radacina dupa creare structura

	while (fgets(buffer, sizeof(buffer), f))
	{
		struct ContBancar tCont;
		char* token = strtok(buffer, separatori);
		tCont.cheie = (unsigned short int)atoi(token);
		
		token = strtok(NULL, separatori);
		strcpy(tCont.iban, token);

		token = strtok(NULL, separatori);
		strcpy(tCont.moneda, token);

		token = strtok(NULL, separatori);
		tCont.titular = (char*)malloc(strlen(token) + 1);
		strcpy(tCont.titular, token);

		token = strtok(NULL, separatori);
		tCont.sold = (float)atof(token);

		// inserare cont bancar in arbore binar de cautare
		unsigned char inserat;
		arbore = inserare_cont_ABC(arbore, tCont, &inserat); // inserare nod in ABC
		if (!inserat)
		{
			printf("Nodul %d nu a fost inserat!\n", tCont.cheie);
			free(tCont.titular);
		}
	}

	// traversare ABC dupa creare
	printf("\nArbore traversat in inordine: ");
	inordine_ABC(arbore);
	printf("\n\n");

	// cautare nod pe baza de cheie in ABC
	ContBancar* p_cont = NULL;
	p_cont = cauta_cont_bancar(arbore, 84);
	if (p_cont != NULL)
	{
		printf("Cont bancar identificat: %d %s\n", p_cont->cheie, p_cont->iban);
	}
	else
		printf("Contul bancar nu exista in ABC!\n");

	// TODO: stergere nod in ABC

	// dezalocare structura ABC
	arbore = dezalocare_ABC(arbore);
	printf("\nArborele dupa dezalocare: ");
	inordine_ABC(arbore);
	printf("\n\n");

	fclose(f);
	return 0;
}