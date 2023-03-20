#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define VECTOR_SIZE 10
#define BUFFER_SIZE 256

struct ContBancar
{
	char iban[24];
	char* titular;
	char moneda[4];
	float sold;
	unsigned int nr_carduri;
};

struct Nod
{
	char moneda[4];
	double sold_total;
	struct Nod *next;
};

struct Nod* inserare_inceputLS(struct Nod* p, struct ContBancar cb)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	strcpy(nou->moneda, cb.moneda);
	nou->sold_total = cb.sold;
	nou->next = p;

	return nou;
}

// functie pentru determinare solduri conturi bancare grupate pe moneda
// conturile utilizate sunt cele stocate in vectorul vcd

struct Nod* solduri_conturi(struct ContBancar* vcb, unsigned char nr_conturi)
{
	struct Nod* primNod = NULL; // lista simpla nu contine nici un nod (empty)

	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		struct Nod* t = primNod;
		char gasit = 0;
		while (t && (gasit == 0))
		{
			if (strcmp(vcb[i].moneda, t->moneda) == 0)
			{
				// string-uri identice pentru moneda
				gasit = 1;
				t->sold_total += vcb[i].sold;
			}
			t = t->next; // modificare t cu adresa nodului succesor
		}

		if (gasit == 0)
		{
			// nu a fost identificat nod cu moneda din vcb[i]
			// nod nou se insereaza in lista simpla gestionata cu primNod
			primNod = inserare_inceputLS(primNod, vcb[i]);
		}
	}

	return primNod;
}

// functie determinare numar de carduri per titular cont
// "inchidere" conturi bancare cu sold nul (se efectueaza pe vector)

// stergere nod din lista simpla (2 cerinte)
// stergere lista simpla

int main()
{

	struct ContBancar cb, vcb[VECTOR_SIZE];
	FILE* f;
	unsigned int i = 0;
	unsigned char nr_conturi;

	f = fopen("Conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[]=",\n";

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

	nr_conturi = (unsigned char)i;

	struct Nod* primNod = NULL;

	primNod = solduri_conturi(vcb, nr_conturi); // i este ultima valoare din secventa de preluare date din fisier

	fclose(f);
	return 0;
}