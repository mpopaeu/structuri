
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define VECTOR_SIZE 10

enum UM {RON, EUR, USD};

struct ContBancar
{
	char iban[24];
	char* titular;
	float sold;
	enum UM moneda;
	char activ; // boolean pentru cont activ; true - activ
};

struct Nod
{
	char* nume_titular;
	struct Nod *next;
};


// inserare nod in LS simpla de titulari (pe prima pozitie)
struct Nod* inserare_titular_inceputLS(struct Nod* p, char* nume)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->nume_titular = (char*)malloc(strlen(nume) + 1);
	strcpy(nou->nume_titular, nume);

	nou->next = p;

	return nou;
}

struct Nod* dezalocare_titulariLS(struct Nod* p)
{
	struct Nod* t;

	while (p)
	{
		t = p;
		p = p->next;

		// dezalocare nod t
		free(t->nume_titular);
		free(t);
		t = NULL;
	}

	return p;
}

// functia determina numarul de titulari "unici" din vector de conturi bancare
unsigned int nr_titulari(struct ContBancar v[], unsigned int nr_conturi)
{
	struct Nod* primNod = NULL;

	for (unsigned int i = 0; i < nr_conturi; i++)
	{
		struct Nod* t = primNod;
		char gasit = 0;
		while (t && (gasit == 0))
		{
			if (strcmp(v[i].titular, t->nume_titular) == 0)
				gasit = 1;

			t = t->next;
		}

		if (gasit == 0)
		{
			// nu a fost identificat titularul contului bancar v[i] in lista simpla
			// inserare nume titular in lista simpla
			primNod = inserare_titular_inceputLS(primNod, v[i].titular);
		}
	}

	// calcul numar de titulari diferitei == nr de noduri din lista simpla
	struct Nod* t = primNod;
	unsigned int nrt = 0;

	while (t)
	{
		nrt += 1;

		t = t->next;
	}

	// dezalocare lista simpla; structura locala functiei
	primNod = dezalocare_titulariLS(primNod);

	return nrt;
}


// functia determinare numar de conturi bancare active pe fiecare moneda

int main()
{
	FILE* f; 
	f = fopen("conturi.txt", "r");

	char buffer[BUFFER_SIZE], seps[] = ",\n";
	unsigned char i = 0;

	struct ContBancar v[VECTOR_SIZE];
	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct ContBancar cb;
		char * token = strtok(buffer, seps);
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

		
		v[i++] = cb;
	}

	unsigned int nr_conturi = i;
	unsigned int nr_clienti = nr_titulari(v, nr_conturi);
	printf("Nr clienti distincti = %u\n", nr_clienti);

	fclose(f);

}