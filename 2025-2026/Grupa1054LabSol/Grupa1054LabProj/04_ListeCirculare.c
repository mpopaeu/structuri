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

Nod* inserareNodCirculara(Nod* p, Angajat a)
{
	Nod* nou = malloc(sizeof(Nod));	
	nou->ang = a;	  // copiere date angajat in nodul nou
	if (p == NULL) {
		nou->next = nou;
		return nou; // nodul nou devine primul si unicul nod din lista simpla
	}
	else
	{
		nou->next = p; // inserare la sfarsitul listei simple circulara, succesor pentru nodul nou este primul nod
		// parsare lista simpla la ultimul nod
		Nod* t = p;
		while (t->next != p) // cautarea ultimului nod din lista simpla circulara
			t = t->next;

		t->next = nou; // actualizare legatura ultim nod catre nodul nou care se insereaza
	}

	return p; // functie trebuie sa intoarca rezultat si in cazul in care lista contine cel putin 1 nod
}

void traversareCirculara(Nod* p)
{
	if (p != NULL)
	{
		// prelucrare nod p inainte de parsare noduri incepand cu nodul #2
		printf("id = %s\n", p->ang.id);

		Nod* t = p->next; // t incepe parsare liste cu nodul #2

		while (t != p) // t == p corespunde prelucrarii in iteratiile anterioare a tuturor nodurilor
				  // t == p trebuie sa opreasca parsarea listei simple circulare (iesiere din DO-WHILE)
		{
			printf("id = %s\n", t->ang.id);
			t = t->next;
		}
	}
}


Nod* stergereCirculara(Nod* p, char* id_cautat)
{

	Nod* t = p;

	if (strcmp(p->ang.id, id_cautat) == 0) // nodul de sters este primul din lista circulara
	{
		t = p->next; // t contine adresa nodului #2 din lista simpla

		if (t == p)
			t = NULL; // nodul de sters este primul si unicul din lista circulara; dupa stergere lista circ devine empty
		else
		{
			while (t->next != p) // pozitionare t pe ultimul nod din lista circulara
			{
				t = t->next;
			}
			t->next = p->next; // actualizare succesor al ultimului nod catre nodul #2 din lista circulara
			t = p->next; // t devine primul nod din lista circulara; vezi return t mai jos ca unic punct de return
		}

		// nodul de sters este primul din lista simpla
		free(p->ang.functie); // dezalocare mem heap pentru string functie
		free(p->ang.nume);	  // dezalocare mem heap pentru string nume
		free(p);		// dezalocare element lista simpla (Nod)

		return t; // return adresa actualizata pentru inceputul de lista simpla
	}

	// nodul de sters nu este primul din lista simpla
	// traversare lista simpla cu verificare id cautat in nodul succesor al nodului curent t
	while (t->next != p)
	{
		if (strcmp(t->next->ang.id, id_cautat) == 0)
		{
			// nodul cautat este identificat pe pozitie arbitrara in lista simpla
			// salvare nod de sters
			Nod* de_sters = t->next;

			// actualizare legatura t->next la succesor pentru de_sters
			// stergere logica a nodului de_sters
			t->next = de_sters->next;

			// stergere/dezalocare fizica
			free(de_sters->ang.functie);
			free(de_sters->ang.nume);
			free(de_sters);
		}

		if (t->next != p)
			t = t->next;
	}

	return p;

}

int main()
{
	Nod* prim = NULL; // prim variabila locala; adresa primul nod din lista simpla; prim NULL echivalent cu lista empty

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

		prim = inserareNodCirculara(prim, angajat); // inseare in lista simpla date pregatite in angajat 
	}

	fclose(f);

	printf("Lista circulara dupa creare:\n");
	traversareCirculara(prim);

	prim = stergereCirculara(prim, "ID13");
	printf("Lista circulara dupa stergere nod:\n");
	traversareCirculara(prim);

	return 0;
}