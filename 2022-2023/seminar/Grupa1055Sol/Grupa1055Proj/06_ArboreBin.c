#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

enum UM { RON, EUR, USD };

struct ContBancar
{
	char iban[25];
	char* titular;
	float sold;
	enum UM moneda;
	char activ; // boolean pentru cont activ; true - activ
};

struct NodABC // structura nod arbore binar de cautare (ABC)
{
	unsigned int cheie;
	struct ContBancar cb;
	struct NodABC *st, *dr;
};

struct NodABC* inserare_cb_abc(struct NodABC* r, unsigned int key, 
								struct ContBancar cont_bancar, unsigned char *cod_iesire)
{
	if (r)
	{
		// continuare cautare loc de inserat pentru cont bancar cu cheia key
		if (r->cheie > key)
		{
			// se continua cautarea locului pe stanga nodului curent r
			r->st = inserare_cb_abc(r->st, key, cont_bancar, cod_iesire);
		}
		else
		{
			if (r->cheie < key)
			{
				// se continua cautarea locului de inserat pe dreapta nodului curent r
				r->dr = inserare_cb_abc(r->dr, key, cont_bancar, cod_iesire);
			}
			else
			{
				// cheia key exista deja in ABC
				*cod_iesire = 1;
			}
		}
	}
	else
	{
		// r == NULL; locul de inserat nodul nou este identificat
		struct NodABC* nou = (struct NodABC*)malloc(sizeof(struct NodABC));
		nou->st = nou->dr = NULL;
		nou->cb = cont_bancar;
		nou->cheie = key;

		*cod_iesire = 0;

		r = nou;
	}

	return r;
}


void drum_invers_nod(struct NodABC* r, unsigned int key)
{
	if (r)
	{
		if (r->cheie > key)
		{
			drum_invers_nod(r->st, key);
		}
		else
		{
			if (r->cheie < key)
			{
				drum_invers_nod(r->dr, key);
			}
			else
			{
				// nodul a fost identificat in ABC
				printf("\nNodul cu cheia %u a fost gasit in ABC. Drumul invers este: ", key);
			}
		}

		printf(" %u ", r->cheie);
	}

}

void traversare_inordine(struct NodABC *r)
{
	if (r)
	{
		traversare_inordine(r->st);

		printf(" %u ", r->cheie);

		traversare_inordine(r->dr);
	}
}

// stergere nod in ABC; nodul este cautat dupa cheie

int main()
{
	FILE* f;
	f = fopen("conturi_abc.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";
	unsigned int k;

	struct NodABC* root = NULL; // variabila acces la ABC (adresa nod radacina ABC)

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct ContBancar cb;
		char* token = strtok(buffer, seps);
		k = (unsigned int)atoi(token);

		token = strtok(NULL, seps);
		strcpy(cb.iban, token);

		token = strtok(NULL, seps);
		cb.titular = (char*)malloc(strlen(token) + 1);
		strcpy(cb.titular, token);

		token = strtok(NULL, seps);
		cb.sold = atof(token);

		token = strtok(NULL, seps);
		if (strcmp(token, "RON") == 0)
			cb.moneda = RON;
		if (strcmp(token, "EUR") == 0)
			cb.moneda = EUR;
		if (strcmp(token, "USD") == 0)
			cb.moneda = USD;

		token = strtok(NULL, seps);
		if (strcmp(token, "true") == 0)
			cb.activ = 1;
		else
			if (strcmp(token, "false") == 0)
				cb.activ = 0;

		// inserare cont bancar cu cheia k in ABC
		unsigned char err;
		root = inserare_cb_abc(root, k, cb, &err);
		if (err)
		{
			printf("Contul bancar cu cheia %u nu a fost inserat\n", k);
			free(cb.titular); // cb nu a ajuns in ABC
		}
	}
	fclose(f);

	printf("ABC la traversarea in inordine: ");
	traversare_inordine(root);
	printf("\n\n");

	printf("Drumul invers de la un nod catre radacina:\n");
	drum_invers_nod(root, 51);
	printf("\n\n");

	// dezalocare ABC
}
