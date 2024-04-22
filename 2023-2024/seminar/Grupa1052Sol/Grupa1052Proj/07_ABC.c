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
		arbore = inserare_cont_ABC(arbore, tCont, &inserat);
		if (!inserat)
		{
			printf("Nodul %d nu a fost inserat!\n", tCont.cheie);
			free(tCont.titular);
		}
	}

	fclose(f);
	return 0;
}