
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

struct NodCA // nod conturi active per moneda
{
	enum UM moneda;
	unsigned int nr_conturi_active;
	struct NodCA* next;
};

// inserare nod in lista simpla de titulari (pe prima pozitie)
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
	struct Nod* primNod = NULL; // variabila de acces la lista simpla (adresa primului nod)

	for (unsigned int i = 0; i < nr_conturi; i++) // acces la un cont bancar (offset i on vector)
	{
		struct Nod* t = primNod; // variabila temporare de parsare a listei primNod
		char gasit = 0;
		while (t && (gasit == 0)) // gasit flag de semnalare a unui titular deja prezent in lista primNod
		{
			if (strcmp(v[i].titular, t->nume_titular) == 0)
				gasit = 1; // titularul v[i].titular este deja prezent in lista primNod

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
	unsigned int nrt = 0; // contor numarare titulari == nr de noduri in lista primNod

	while (t)
	{
		nrt += 1;

		t = t->next;
	}

	// dezalocare lista simpla; structura locala functiei
	primNod = dezalocare_titulariLS(primNod); // dezalocare lista simpla primNod

	return nrt; // numar de titulari "unici" in vectorul de conturi bancare
}


// functia determinare numar de conturi bancare active pe fiecare moneda
struct NodCA* conturi_active_pe_moneda(struct ContBancar v[], unsigned int nr_conturi)
{
	struct NodCA* primNodLCA = NULL;
	for (unsigned int i = 0; i < nr_conturi; i++)
	{
		struct NodCA* p = primNodLCA;
		char gasit = 0;
		while (p && gasit==0)
		{
			if (v[i].moneda == p->moneda)
			{	
				gasit = 1;
				if (v[i].activ) {
					p->nr_conturi_active++;
				}
			}
			p = p->next;
		}
		if (gasit == 0)
		{
			struct NodCA* nou = (struct NodCA*)malloc(sizeof(struct NodCA));
			nou->moneda = v[i].moneda;
			nou->nr_conturi_active = 0;
			if (v[i].activ) {
				nou->nr_conturi_active = 1;
			}
			nou->next = primNodLCA;
			primNodLCA = nou;
		}
		
	}

	// pentru fiecare element din vector:
	// 1. verificare existenta moneda in lista primNodCA
	// 2. DA, se verifica daca contul bancar curent este activ
	//		2.1 DA, se adauga la nr de conturi active pentru moneda identificata (incrementare nr conturi active)
	//		2.2 NU, nu se efectueaza nici o prelucrare pe contul bancar curent
	// 3. NU, se adauga moneda in lista ca element/nod nou; 
	// se initializeaza nr conturi bancare active cu 1 daca contul curent este activ sau 0 pentru inactiv

	return primNodLCA;
}

void get_nume_moneda(enum UM moneda, char nume_moneda[])
{
	switch (moneda) {
	case RON:
		strcpy(nume_moneda, "RON");
		break;
	case USD:
		strcpy(nume_moneda, "USD");
		break;
	case EUR:
		strcpy(nume_moneda, "EUR");
		break;
	}
}

// inserare nod (cont bancar) in lista simpla cu ordine crescatoare a soldurilor

// creare stiva pentru prelucrarea in ordine descrescatoare a nodurilor create intr-o lista simpla de conturi

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

	struct NodCA* listCA = conturi_active_pe_moneda(v, nr_conturi);
	struct NodCA* t = listCA;

	while (t) {
		char nume_moneda[4];
		get_nume_moneda(t->moneda, nume_moneda);
		printf("Moneda: %s, Conturi active: %u\n", nume_moneda, t->nr_conturi_active);
		t = t->next;
	}

	// dezalocare lista listCA
}