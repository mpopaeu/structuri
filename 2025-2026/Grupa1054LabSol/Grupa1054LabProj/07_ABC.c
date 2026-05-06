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

struct NodABC {
	Angajat ang;
	struct NodABC* stanga, *dreapta;
};

typedef struct NodABC NodABC;

NodABC* inserareNodABC(NodABC* nodABC, Angajat data, unsigned char *flag)
{
	if (nodABC != NULL)
	{
		if (strcmp(data.id, nodABC->ang.id) < 0)
		{
			// continuare cautare pozitie de inserat pe stanga nodului curent
			nodABC->stanga = inserareNodABC(nodABC->stanga, data, flag);
		}
		else
		{
			if (strcmp(data.id, nodABC->ang.id) > 0)
			{
				// continuare cautare pozitie de inserat pe dreapta nodului curent
				nodABC->dreapta = inserareNodABC(nodABC->dreapta, data, flag);
			}
			else
			{
				// data.id este deja prezent in ABC
				// se abandoneaza cautarea locului de inserat
				*flag = 0; // inserare nu are loc
				return nodABC;
			}
		}
	}
	else
	{
		// cautarea locului de inserat s-a finalizat in pozitie de NULL in ABC
		// este locul unde nodul nou trebuie adaugat la ABC
		NodABC* nou = malloc(sizeof(NodABC));
		nou->ang = data;
		// nou devine frunza in ABC
		nou->stanga = NULL; 
		nou->dreapta = NULL;

		*flag = 1; // inserarea are loc in ABC

		return nou;
	}

	return nodABC;
}

void InordineABC(NodABC* nodABC)
{
	if (nodABC != NULL)
	{
		InordineABC(nodABC->stanga);
		printf("%s %s\n", nodABC->ang.id, nodABC->ang.nume);
		InordineABC(nodABC->dreapta);
	}
}

NodABC* dezalocareABC(NodABC* nodABC)
{
	if (nodABC != NULL)
	{
		nodABC->stanga = dezalocareABC(nodABC->stanga);
		nodABC->dreapta = dezalocareABC(nodABC->dreapta);

		free(nodABC->ang.nume); // dezalocare extensie angajat din nod curent
		free(nodABC->ang.functie); // dezalocare extensie angajat din nod curent
		free(nodABC); // dezalore nod curent
	}

	return NULL;
}

int main()
{
	NodABC* root = NULL; // root este adresa nod radacina ABC

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

		unsigned char inserat;
		root = inserareNodABC(root, angajat, &inserat); // inserare date angajat in ABC gestionat cu root

		if (inserat == 0)
		{
			printf("Angajatul %s nu a fost inserat.\n", angajat.id);
			free(angajat.nume);
			free(angajat.functie);
		}
		else
		{
			printf("Angajatul %s a fost inserat.\n", angajat.id);
		}
	}

	fclose(f);

	printf("Arbore binar de cautare dupa creare:\n");
	InordineABC(root);

	root = dezalocareABC(root);
	printf("Arbore binar de cautare dupa dezalocare:\n");
	InordineABC(root);

	return 0;
}