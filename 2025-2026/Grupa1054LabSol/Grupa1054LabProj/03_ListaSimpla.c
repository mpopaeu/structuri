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
	nou->next = NULL; // inserare la sfarsitul listei simple
	nou->ang = a;	  // copiere date angajat in nodul nou
	if (p == NULL)
		return nou;
	else
	{
		// parsare lista simpla la ultimul nod
		Nod* t = p;
		while (t->next) // cautarea ultimul nod din lista
			t = t->next;

		t->next = nou; // actualizare legatura ultim nod catre nodul nou care se insereaza
	}

	return p;
}

void traversare(Nod* p)
{
	Nod* t = p;
	while (t)
	{
		printf("id = %s\n", t->ang.id);
		t = t->next;
	}
}

int main()
{
	Nod* prim = NULL; // prim variabila locala; adresa primul nod din lista simpla; prim NULL echivalent cu lista empty

	FILE* f;

	f = fopen("Angajati.txt", "r");

	char buffer[256]; // byte array pentru stocare linie preluata din fisier
	char sep[] = ",\n";
	Angajat angajat;
	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = strtok(buffer, sep);
		angajat.nume = malloc(strlen(token) + 1);
		strcpy(angajat.nume, token);

		token = strtok(NULL, sep); // NULL pentru a continua tokenizare dn pozitia curenta
		strcpy(angajat.id, token);

		token = strtok(NULL, sep);
		angajat.varsta = atoi(token);

		token = strtok(NULL, sep);
		angajat.salariu = atof(token);

		token = strtok(NULL, sep);
		angajat.functie = malloc(strlen(token) + 1);
		strcpy(angajat.functie, token);

		prim = inserareNodLS(prim, angajat);
	}

	traversare(prim);

	fclose(f);
	return 0;
}