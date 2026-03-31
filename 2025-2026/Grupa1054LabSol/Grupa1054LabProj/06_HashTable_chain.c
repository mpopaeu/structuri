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

	Angajat* angajat_gasit = cautaAngajatHT(HT, size, "ID33");
	printf("Cautare angajati dupa cheie (id angajat):\n");
	if (angajat_gasit != NULL)
	{
		printf("Angajat identificat in tabela hash: %s %s\n", angajat_gasit->id, angajat_gasit->nume);
	}
	else
	{
		printf("Anagajatul cautat nu este stocat in tabela hash.\n");
	}

	// stergere angajat pe baza de cheie (id angajat)

	return 0;

}