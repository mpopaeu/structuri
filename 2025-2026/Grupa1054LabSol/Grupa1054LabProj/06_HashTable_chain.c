#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Angajat {
	char* nume;
	char id[5]; // 1 byte rezervat pentru terminatorul de string
	unsigned char varsta;
	float salariu;
	char* functie;
};

typedef struct Angajat Angajat;

struct Nod {
	Angajat ang;
	struct Nod* next;
};

typedef struct Nod Nod;

struct NodAdr
{
	Angajat* pang;
	struct NodAdr* next;
};

typedef struct NodAdr NodAdr;

Nod* inserareNodLS(Nod* p, Angajat a)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->next = NULL; // inserare la sfarsitul listei simple, deci nu exista succesor pentru nodul nou
	nou->ang = a;	  // copiere date angajat in nodul nou
	if (p == NULL)
		return nou; // nodul nou devine primul si unicul nod din lista simpla
	else
	{
		// parsare lista simpla la ultimul nod
		Nod* t = p;
		while (t->next) // cautarea ultimului nod din lista simpla
			t = t->next;

		t->next = nou; // actualizare legatura ultim nod catre nodul nou care se insereaza
	}

	return p; // functie trebuie sa intoarca rezultat si in cazul in care lista contine cel putin 1 nod
}

NodAdr* inserareNodAdrLS(NodAdr *p, Angajat *ang)
{
	NodAdr* nou = malloc(sizeof(NodAdr));
	nou->next = p;
	nou->pang = ang;

	return nou;
}

unsigned short int functie_hash(char * cheie, unsigned short int sizeht)
{
	unsigned int suma = 0;
	for (unsigned char i = 0; i < strlen(cheie); i++)
		suma += cheie[i]; // adunare cod ASCII cheie[i] la suma determinata anterior

	return (suma % sizeht); // rezultat cuprins in [0; sizeht-1]
}

void inserareAngajatHashTable(Nod** hasht, unsigned short int sizeht, Angajat ang)
{
	// 1. determinare pozitie in tabela hash prin aplicare functie hash
	unsigned short int poz = functie_hash(ang.id, sizeht);

	// 2. inserare in lista simpla corespondenta a angajatului
	hasht[poz] = inserareNodLS(hasht[poz], ang);
}

Angajat* cautaAngajatHT(Nod** hasht, unsigned short int sizeht, char* cheie_cautare)
{
	unsigned short int poz = functie_hash(cheie_cautare, sizeht);

	Nod* t = hasht[poz]; // poz este lista simpla in care (teoretic)se afla angajat
	while (t != NULL)
	{
		if (strcmp(cheie_cautare, t->ang.id) == 0)
		{
			// angajat identificat in lista simpla hasht[poz]
			return &t->ang; // adresa de heap unde incepe angajatul cu cheie_cautare pe post de id angajat
		}
		t = t->next;
	}

	return NULL; // angajat cu cheie_cautare nu a fost identificat in lista simpla hasht[poz]
}

Angajat* traversareLSRec(Nod* nod, char* cheie_cautare)
{
	if(nod != NULL)
	{ 
		if (strcmp(nod->ang.id, cheie_cautare) == 0)
			return &nod->ang;
		else
			return traversareLSRec(nod->next, cheie_cautare);
	}

	return NULL; // nod este NULL
}

Angajat* cautaAngajatHTRec(Nod** hasht, unsigned short int sizeht, char* cheie_cautare)
{
	unsigned short int poz = functie_hash(cheie_cautare, sizeht);

	return traversareLSRec(hasht[poz], cheie_cautare);
}

unsigned char stergereAngajatHashTable(Nod** hasht, unsigned short int sizeht, char* id_angajat)
{
	// 1. determinare pozitie in tabela lista in cre ar trebui sa gasim angajatul
	unsigned short int poz = functie_hash(id_angajat, sizeht);

	// 2. stergere nod cu angajatul identificat pe baza de cheie (id angajat)
	Nod* temp = hasht[poz]; // hasht[poz] este lista simpla in care ar trebui sa fie stocat angajatul de sters 
	if (hasht[poz] != NULL)
	{
		if (strcmp(hasht[poz]->ang.id, id_angajat) == 0)
		{
			// angajatul de sters este stocat in primul nod din lista simpla hasht[poz]
			hasht[poz] = hasht[poz]->next; // actualizare adresa prim nod in lista simpla cu nodul 2/NULL
			free(temp->ang.nume);
			free(temp->ang.functie);
			free(temp);

			return 1; // stergere efectuata
		}
		else
		{
			while (temp->next != NULL)
			{
				if (strcmp(temp->next->ang.id, id_angajat) == 0)
				{
					Nod* succesor_nou = temp->next->next; // temp->next este nodul de sters
					
					free(temp->next->ang.nume);
					free(temp->next->ang.functie);
					free(temp->next);

					temp->next = succesor_nou; // actualizare succesor temp

					return 1; // stergere efectuata
				}

				temp = temp->next;
			}
		}
	}

	return 0; // angajatul cautat nu exista in tabela hash
}

NodAdr* salveazaAngajatiNume(Nod** hasht, unsigned short int sizeht, char* nume_angajat)
{
	NodAdr* lista = NULL;

	for (unsigned short int i = 0; i < sizeht; i++)
	{
		if (hasht[i] != NULL)
		{
			Nod* temp = hasht[i];
			while (temp != NULL)
			{
				if (strcmp(temp->ang.nume, nume_angajat) == 0)
				{
					// temp contine angajat cu nume cautat pentru salvare in lista rezultat al functiei
					lista = inserareNodAdrLS(lista, &temp->ang);
				}

				temp = temp->next;
			}
		}
	}

	return lista;
}

int main()
{
	Nod* *HT = NULL; // hash table chaining: vector alocat la run-time pentru stocare adrese inceput liste simple
	unsigned short int size = 49; // dimensiune tabela de dispersie

	HT = malloc(size * sizeof(Nod*));
	for (unsigned short int i = 0; i < size; i++)
		HT[i] = NULL; // initial, toate listele simple sunt marcate ca empty

	FILE* f;

	f = fopen("Angajati.txt", "r");

	char buffer[256]; // byte array pentru stocare linie preluata din fisier
	char sep[] = ",\n"; // lista de separatori utilizata de strtok pentru identificare token (substring)
	Angajat angajat;
	while (fgets(buffer, sizeof(buffer), f)) // fgets returns NULL daca nu mai exista linie de preluat din fisier
	{
		char* token = strtok(buffer, sep); // param #1 buffer pentru a incepe cu primul byte din buffer
		angajat.nume = malloc(strlen(token) + 1); // alocare heap seg pentru stocare string num
		strcpy(angajat.nume, token);			  // copiere string in campul nume

		token = strtok(NULL, sep); // param #1 NULL pentru a continua tokenizare dn pozitia curenta
		strcpy(angajat.id, token); // copiere string in campul id (vector alocat la compilare)

		token = strtok(NULL, sep);
		angajat.varsta = atoi(token); // conversie text-to-integer

		token = strtok(NULL, sep);
		angajat.salariu = (float)atof(token); // conversie text-to-float

		token = strtok(NULL, sep);
		angajat.functie = malloc(strlen(token) + 1); // alocare heap seg pentru stocare string functie
		strcpy(angajat.functie, token);				 // copiere string in campul functie

		inserareAngajatHashTable(HT, size, angajat); // inserare angajat in tabela hash cu chaining
	}

	fclose(f);

	printf("Continut tabela hash chaining:\n");
	for (unsigned short int i = 0; i < size; i++)
	{
		if (HT[i] != NULL) // lista i din vectorul HT nu este empty
		{
			printf("Lista %d:\n", i);
			Nod* t = HT[i];
			while (t != NULL)
			{
				printf("%s %s\n", t->ang.id, t->ang.nume);
				t = t->next;
			}
		}
	}

	//Angajat* angajat_gasit = cautaAngajatHT(HT, size, "ID31");
	Angajat* angajat_gasit = cautaAngajatHTRec(HT, size, "ID31");
	printf("Cautare angajati dupa cheie (id angajat):\n");
	if (angajat_gasit != NULL)
	{
		printf("Angajat identificat in tabela hash: %s %s\n", angajat_gasit->id, angajat_gasit->nume);
	}
	else
	{
		printf("Angajatul cautat nu este stocat in tabela hash.\n");
	}

	// salveaza angajatii cu acelasi nume in lista separata
	NodAdr* lista_nume = salveazaAngajatiNume(HT, size, "Popescu Marin");
	printf("\nAngajatii cu acelasi nume cautat in tabela hash:\n");
	NodAdr* temp = lista_nume;
	while (temp != NULL)
	{
		printf("%s %s\n", temp->pang->id, temp->pang->nume);

		temp = temp->next;
	}

	// stergere angajat pe baza de cheie (id angajat)
	unsigned char sters = stergereAngajatHashTable(HT, size, "ID31");
	printf("\nStergere angajat in tabela hash: ");
	if (sters != 0)
	{
		printf("Stergere efectuata!\n");
	}
	else
	{
		printf("Angajatul nu exista in tabela hash!\n");
	}
	angajat_gasit = cautaAngajatHT(HT, size, "ID31");
	printf("Cauta angajat eliminat din tabela hash:");
	if (angajat_gasit != NULL)
	{
		printf("Angajat identificat in tabela hash: %s %s\n", angajat_gasit->id, angajat_gasit->nume);
	}
	else
	{
		printf("Angajatul cautat nu este stocat in tabela hash.\n");
	}

	// dezalocare tabela hash
	// 1. dezalocare liste simple agatate de vectorul suport al tabelei hash
	for (unsigned short int i = 0; i < size; i++)
	{
		while (HT[i] != NULL)
		{
			sters = stergereAngajatHashTable(HT, size, HT[i]->ang.id);
		}
	}
	// 2. dezalocare vector suport tabela hash
	free(HT);

	// dezalocare lista angajati cu acelasi nume
	while (lista_nume != NULL)
	{
		temp = lista_nume;
		lista_nume = lista_nume->next;

		free(temp);
	}

	return 0;

}