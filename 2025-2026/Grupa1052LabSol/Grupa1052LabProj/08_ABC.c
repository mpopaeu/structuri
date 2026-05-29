#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

struct Angajat
{
	char* nume;					// 4 bytes
	float salariu;				// 4 bytes
	char CNP[14];				// 14 bytes
	char* functie;				// 4 bytes
	unsigned char vechime_ani;	// 1 byte
};

typedef struct Angajat Angajat;

struct NodABC
{
	Angajat angajat;
	struct NodABC* stanga, *dreapta;
};

typedef struct NodABC NodABC;

NodABC* inserareAngajatABC(NodABC * nod, Angajat data, unsigned char *gasit)
{
	if (nod != NULL)
	{
		// se continua cautarea locului de inserat
		if (strcmp(data.CNP, nod->angajat.CNP) == -1)
		{
			// CNP de inserat "mai mic" decat CNP existent in nod curent nod
			nod->stanga = inserareAngajatABC(nod->stanga, data, gasit);
		}
		else
		{
			if (strcmp(data.CNP, nod->angajat.CNP) == 1)
			{
				// CNP de inserat "mai mare" decat CNP existent in nod curent (param nod)
				nod->dreapta = inserareAngajatABC(nod->dreapta, data, gasit);
			}
			else
			{
				// data nu se insereaza deoarece exista deja CNP stocat in ABC
				*gasit = 1;
				return nod;
			}
		}
	}
	else
	{
		// locul de inserat a fost identificat in ABC
		*gasit = 0;
		NodABC* nou = malloc(sizeof(NodABC));

		nou->angajat = data;
		// nodul de inserat va fi frunza in ABC
		nou->stanga = NULL;
		nou->dreapta = NULL;

		return nou; // nod = nou;
	}

	return nod;
}

void Inordine(NodABC* nod)
{
	if (nod != NULL)
	{
		Inordine(nod->stanga);

		printf("%s %s\n", nod->angajat.CNP, nod->angajat.nume);

		Inordine(nod->dreapta);
	}
}

Angajat* cautareAngajatCheie(NodABC* nod, char* cheie_cnp)
{
	if (nod != NULL)
	{
		// se continua cautarea locului de inserat
		if (strcmp(cheie_cnp, nod->angajat.CNP) == -1)
		{
			// CNP de inserat "mai mic" decat CNP existent in nod curent nod
			return cautareAngajatCheie(nod->stanga, cheie_cnp);
		}
		else
		{
			if (strcmp(cheie_cnp, nod->angajat.CNP) == 1)
			{
				// CNP de inserat "mai mare" decat CNP existent in nod curent (param nod)
				return cautareAngajatCheie(nod->dreapta, cheie_cnp);
			}
			else
			{
				// nodul cu cnp cautat este identificat ca param nod in ABC
				return &nod->angajat;
			}
		}
	}

	return NULL;
}

void cautareAngajatiFunctie(NodABC* nod, char* functie_angajat)
{
	if (nod != NULL)
	{
		if (strcmp(functie_angajat, nod->angajat.functie) == 0)
			printf("%s %s\n", nod->angajat.CNP, nod->angajat.nume);

		cautareAngajatiFunctie(nod->stanga, functie_angajat);

		cautareAngajatiFunctie(nod->dreapta, functie_angajat);
	}
}

NodABC* dezalocareABC(NodABC* nod)
{
	if (nod != NULL)
	{
		nod->stanga = dezalocareABC(nod->stanga);

		nod->dreapta = dezalocareABC(nod->dreapta);

		free(nod->angajat.functie); // dezalocare extensie angajat in heap
		free(nod->angajat.nume);	// dezalocare extensie angajat in heap
		free(nod);		// dezalocare nod

		nod = NULL;
	}

	return nod;
}

NodABC* stergereNodCheie(NodABC* nod, char* cheie_cnp, Angajat* pAngajat)
{
	if (nod != NULL)
	{
		if (strcmp(cheie_cnp, nod->angajat.CNP) == -1)
			nod->stanga = stergereNodCheie(nod->stanga, cheie_cnp, pAngajat);
		else
		{
			if (strcmp(cheie_cnp, nod->angajat.CNP) == 1)
				nod->dreapta = stergereNodCheie(nod->dreapta, cheie_cnp, pAngajat);
			else
			{
				// am gasit nodul de sters -> nod
				NodABC* desc_stanga = nod->stanga;
				NodABC* desc_dreapta = nod->dreapta;


				NodABC* temp = desc_dreapta;

				if (temp != NULL)
				{
					// exista subarbore dreapta
					while (temp->stanga != NULL)
						temp = temp->stanga;

					// subarbore stanga legat la nodul cu cheie minima din subarbore dreapta
					temp->stanga = desc_stanga;
					temp = desc_dreapta;
				}
				else
				{
					temp = desc_stanga;
				}

				// dezalocare nod curent
				//free(nod->angajat.functie);
				//free(nod->angajat.nume);
				*pAngajat = nod->angajat;
				free(nod);

				nod = temp;
			}
		}
	}

	return nod;
}

// functie care creeaza un vector cu CNP angajati avand vechimea mai mica decat vechimea medie
// a tuturor angajatilor stocati in arbore binar de cautare
// rezultat: vector si dimensiune vector


int main()
{
	NodABC* root = NULL; // root este punctul unic de acces la structura ABC

	FILE* f = fopen("Angajati.txt", "r");

	char buffer[256];
	char seps[] = ",\n";

	while (fgets(buffer, sizeof(buffer), f))
	{
		Angajat ang; // variabila temporara pentru stocare date angajat dupa conversia text->binary
		char* token = strtok(buffer, seps); // debut proces tokenizare si identificare token #1 in linia preluata de buffer
		ang.nume = malloc(strlen(token) + 1); // +1 pt byte nul ca terminator de string
		strcpy(ang.nume, token); // copiere nume angajat in zona alocata (nu se aplica conversie pentru nume angajat -> string)

		token = strtok(NULL, seps); // continuare tokenizare din ultimul punct identificat pe baza separator
		ang.salariu = (float)atof(token); // conversie text->float binar

		token = strtok(NULL, seps); // continuare tokenizare din ultimul punct identificat pe baza separator
		strcpy(ang.CNP, token);     // copiere string in CNP (alocar static ca byte array)

		token = strtok(NULL, seps); // continuare tokenizare din ultimul punct identificat pe baza separator
		ang.functie = malloc(strlen(token) + 1); // alocare spatiu heap seg pentru functie
		strcpy(ang.functie, token); // copierea functie in zona alocata (nu se aplica conversie la string)

		token = strtok(NULL, seps);     // continuare tokenizare din ultimul punct identificat pe baza separator
		ang.vechime_ani = atoi(token);  // conversie text->int binar

		// inserare angajat in ABC
		unsigned char gasit;
		root = inserareAngajatABC(root, ang, &gasit);

		if (gasit == 1)
		{
			// inserarea nu a avut loc pentru ca CNP duplicat in ang
			free(ang.nume);
			free(ang.functie);
		}
	}

	fclose(f);

	printf("ABC dupa creare:\n");
	Inordine(root);

	Angajat* pAngajat = cautareAngajatCheie(root, "1981123466710");
	printf("\n//////// CAUTARE DUPA CHEIE ///////\n");
	if (pAngajat != NULL)
	{
		printf("Angajat idenificat: %s %s\n", pAngajat->CNP, pAngajat->nume);
	}
	else
	{
		printf("Angajatul nu a fost identificat in ABC.\n");
	}

	
	printf("\n//////// CAUTARE DUPA NON-CHEIE ///////\n");
	cautareAngajatiFunctie(root, "specialist HR");

	Angajat ang_extras;
	ang_extras.nume = NULL;
	root = stergereNodCheie(root, "1890223420897", &ang_extras);
	printf("\n//////// ABC dupa STERGERE NOD pe baza de CHEIE ///////\n");
	if (ang_extras.nume != NULL)
	{
		printf("Angajatul %s %s a fost eliminat din ABC\n", ang_extras.CNP, ang_extras.nume);
		free(ang_extras.functie);
		free(ang_extras.nume);
	}
	else
	{
		printf("Angajatul de sters nu exista in ABC.\n");
	}
	Inordine(root);
	
	root = dezalocareABC(root);
	printf("\n//////// ABC dupa DEZALOCARE ///////\n");
	Inordine(root);

	return 0;
}