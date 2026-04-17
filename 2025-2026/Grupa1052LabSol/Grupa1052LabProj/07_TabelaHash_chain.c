#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>

#define DIM_TABELA_HASH 59

struct Angajat
{
	char* nume;					// 4 bytes
	float salariu;				// 4 bytes
	char CNP[14];				// 14 bytes
	char* functie;				// 4 bytes
	unsigned char vechime_ani;	// 1 byte
};

typedef struct Angajat Angajat;

struct Nod
{
	Angajat angajat;
	struct Nod* next;
};

typedef struct Nod Nod;

unsigned char functieHash(char* cheie, unsigned short int size_ht)
{
	char transformCheie[8];
	memcpy(transformCheie, cheie, 7);
	transformCheie[7] = 0; // terminator de string scris manual in transformCheie

	int value = atoi(transformCheie);

	return (value % size_ht);
}

Nod* inserareAngajatInceput(Nod* lista, Angajat data) 
{
	Nod* nou = malloc(sizeof(Nod));
	nou->next = lista; // inserare la inceputul unei liste simple; nou devine noul inceput de lista
	nou->angajat = data;

	return nou;
}

void inserareAngajatTabelaHash(Nod** HT, unsigned short int size_ht, Angajat data)
{
	// 1. determinare pozitie lista simpla in care se insereaza data
	unsigned char pos = functieHash(data.CNP, size_ht);

	// 2. inserare date angajat in lista simpla determinata la pasul 1)
	HT[pos] = inserareAngajatInceput(HT[pos], data);
}

Angajat* cautareAngajatCheie(Nod** HT, unsigned short int size_ht, char* cheie)
{
	// 1. determinare pozitie lista simpla in care are trebui regasit/stocat angajat cu cheie
	unsigned char pos = functieHash(cheie, size_ht);

	// 2. cautare secventiala in lista corespondenta (determinata la pasul 1)
	if (HT[pos] != NULL)
	{
		Nod* temp = HT[pos];
		while (temp != NULL)
		{
			if (strcmp(cheie, temp->angajat.CNP) == 0)
				return &temp->angajat; // executia functiei este oprita si se intoarce adresa angajatului din nod

			temp = temp->next;
		}
	}


	return NULL; // angajatul nu este stocat in tabela de dispersie
}

void stergereAngajatTabelaHash(Nod** HT, unsigned short int size_ht, char* cheie)
{
	// 1. determinare pozitie lista simpla in care angajatul cu cheie ar trebuie sa fie stocat 
	unsigned char pos = functieHash(cheie, size_ht);

	// 2. stergere nod in lista simpla corespondenta
	if (HT[pos] != NULL)
	{
		// lista corespondenta are cel putin un nod
		if (strcmp(HT[pos]->angajat.CNP, cheie) == 0)
		{
			Nod* temp = HT[pos]; // temp este nodul de sters din lista simpla HT[pos]
			HT[pos] = HT[pos]->next; // actualizare inceput de lista simpla

			free(temp->angajat.nume);
			free(temp->angajat.functie);
			free(temp);
		}
		else
		{
			// nodul de sters nu este primul din lista simpla
			Nod* temp = HT[pos];
			while (temp->next != NULL)
			{
				if (strcmp(temp->next->angajat.CNP, cheie) == 0)
				{
					// se sterge nodul succesor al lui temp
					Nod* nodSters = temp->next;
					temp->next = nodSters->next; // actualizare succesor temp catre succesorul nodului de sters

					free(nodSters->angajat.nume);
					free(nodSters->angajat.functie);
					free(nodSters);

					return; // deoarece cheie este CNP si are valoarea unica la nivel de angajati
				}

				temp = temp->next;
			}
		}
	}
}

int main()
{
	Nod** HashTable = NULL; // HashTable - vector suport pentru implemenatare tabela hash cu chaining
	FILE* f;

	HashTable = malloc(DIM_TABELA_HASH * sizeof(Nod*));
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++)
	{
		HashTable[i] = NULL; //HashTable[i] este o lista simpla care se initializeaza cu NULL ca marcaj empty list
	}

	f = fopen("Angajati.txt", "r");

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
		strcpy(ang.CNP, token); // copiere string in CNP (alocar static ca byte array)

		token = strtok(NULL, seps); // continuare tokenizare din ultimul punct identificat pe baza separator
		ang.functie = malloc(strlen(token) + 1); // alocare spatiu heap seg pentru functie
		strcpy(ang.functie, token); // copierea functie in zona alocata (nu se aplica conversie la string)

		token = strtok(NULL, seps);// continuare tokenizare din ultimul punct identificat pe baza separator
		ang.vechime_ani = atoi(token); // conversie text->int binar

		// inserare angajat in tabela hash
		inserareAngajatTabelaHash(HashTable, DIM_TABELA_HASH, ang);
	}

	fclose(f);

	printf("\nTabela de dispersie dupa creare:\n");
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++)
	{
		if (HashTable[i] != NULL)
		{
			// lista HashTable[i] contine cel putin un nod
			printf("Lista cu offset %d in vectorul suport tabela hash:\n", i);
			Nod* temp = HashTable[i];
			while (temp != NULL)
			{
				printf("%s %s\n", temp->angajat.CNP, temp->angajat.nume);
				temp = temp->next;
			}
		}
	}

	Angajat* pAngajat = cautareAngajatCheie(HashTable, DIM_TABELA_HASH, "1950406421483");
	printf("\nRezultat cautare angajat dupa cheie (CNP): ");
	if (pAngajat != NULL)
	{
		printf("%s %s\n", pAngajat->CNP, pAngajat->nume);
	}
	else
	{
		printf("angajatul cautat nu exista in tabela hash.\n");
	}

	stergereAngajatTabelaHash(HashTable, DIM_TABELA_HASH, "1950406421483");

	// validare stergere angajat in tabela hash
	pAngajat = cautareAngajatCheie(HashTable, DIM_TABELA_HASH, "1950406421483");
	printf("\nRezultat cautare angajat dupa stergere pe baza de cheie (CNP): ");
	if (pAngajat != NULL)
	{
		printf("%s %s\n", pAngajat->CNP, pAngajat->nume);
	}
	else
	{
		printf("angajatul cautat nu exista in tabela hash.\n");
	}

	// dezalocare tabela hash
	// dezalocare liste simple
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++) 
	{
		while (HashTable[i] != NULL)
		{
			stergereAngajatTabelaHash(HashTable, DIM_TABELA_HASH, HashTable[i]->angajat.CNP);
		}
	}
	// dezalocare vector suport
	free(HashTable);
	HashTable = NULL;

	return 0;
}