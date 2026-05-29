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

NodABC* stergereNodCheie(NodABC* nodABC, char* cheie, Angajat* angajat_extras)
{
	if (nodABC != NULL)
	{
		if (strcmp(cheie, nodABC->ang.id) == -1)
		{
			// se continua cautarea in stanga nodului curent
			nodABC->stanga = stergereNodCheie(nodABC->stanga, cheie, angajat_extras);
		}
		else
		{
			if (strcmp(cheie, nodABC->ang.id) == 1)
			{
				// se continua cautarea in dreapta nodului curent
				nodABC->dreapta = stergereNodCheie(nodABC->dreapta, cheie, angajat_extras);
			}
			else
			{
				// nodul cu cheie cautata este eliminat din ABC
				if (nodABC->stanga == NULL && nodABC->dreapta == NULL)
				{
					// nodul care se sterge fizic din ABC este nodABC
					// nodul nodABC este frunza
					*angajat_extras = nodABC->ang;

					free(nodABC);
					nodABC = NULL;
				}
				else
				{
					if (nodABC->stanga != NULL && nodABC->dreapta != NULL)
					{
						// nodul de sters nodABC are 2 descendenti
						NodABC* nodCheieMax = nodABC->stanga; // nod cu cheie max din subarbore stanga
						NodABC* parinteNodCheieMax = nodABC; // parinte nod cu cheie max din subarbore stanga

						while (nodCheieMax->dreapta != NULL) 
						{
							parinteNodCheieMax = nodCheieMax;
							nodCheieMax = nodCheieMax->dreapta;
						}
						 //interschimb datele din nod curent cu nod cu cheie maxima din subarborele stanga lui nodABC
						Angajat temp = nodABC->ang;
						nodABC->ang = nodCheieMax->ang;
						nodCheieMax->ang = temp;

						if (parinteNodCheieMax == nodABC)
						{
							// radacina sub-arborelui stanga este nod cu cheie maxim (nu exista desc dreapta din radacin sub-arbore stanga)
							parinteNodCheieMax->stanga = nodCheieMax->stanga;
						}
						else
						{
							// actualizare legatura dreapta in parintele nodului cu cheie maxima
							parinteNodCheieMax->dreapta = nodCheieMax->stanga;
						}
						
						// nod cu cheie maxima este cel care se dezaloca fizic din ABC
						*angajat_extras = nodCheieMax->ang;

						free(nodCheieMax);
					}
					else
					{
						// nodABC are un singur descendent
						NodABC* desc_unic = nodABC->stanga;
						if (nodABC->dreapta != NULL)
						{
							desc_unic = nodABC->dreapta;
						}

						*angajat_extras = nodABC->ang;
						free(nodABC);
						nodABC = desc_unic;
					}
				}
			}
		}
	}
	else
	{
		// nodul cu cheie nu a fost identificat in ABC
		angajat_extras->nume = NULL;
	}
	return nodABC;
}

// determinare nr de noduri
unsigned short int nrNoduri(NodABC* nodABC)
{
	if (nodABC != NULL)
	{
		return 1 + nrNoduri(nodABC->stanga) + nrNoduri(nodABC->dreapta);
	}

	return 0;
}

// salvare/extragere noduri plasate pe un nivel specificat

// determinare nr de noduri frunza

// determinare nr de noduri frunza plasate pe un nivel specificat

// determinare nivelul cu nr maxim de frunze

// determinare succesiune de noduri plasate pe drumul de la radacina la un nod cu cheie specificata

// determinare inaltime arbore binar de cautare

// determinare nr de noduri care indeplinesc conditie cu privire la continut




// functie pentru construirea unui vector de angajati
// plasati pe un nivel specificat ca parametru


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

	unsigned short int nr = nrNoduri(root);
	printf("\nNr de noduri din ABC este %d\n", nr);

	// stergere nod in functie de cheie
	root = stergereNodCheie(root, "ID131", &angajat);
	printf("\n//////// STERGERE NOD IN ABC PE BAZA DE CHEIE ///////\n");
	if (angajat.nume != NULL)
	{
		printf("\nNodul cu angajat %s %s a fost eliminat din ABC", angajat.id, angajat.nume);
		// dezalocari pentru angaja extras
		free(angajat.functie);
		free(angajat.nume);
	}
	else
	{
		printf("\nAngajatul cu cheia cautata nu exista in ABC");
	}

	printf("\n\nArbore binar de cautare dupa stergere nod pe baza de cheie:\n");
	InordineABC(root);

	root = dezalocareABC(root);
	printf("Arbore binar de cautare dupa dezalocare:\n");
	InordineABC(root);

	return 0;
}