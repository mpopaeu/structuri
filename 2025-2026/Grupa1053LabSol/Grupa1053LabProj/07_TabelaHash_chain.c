#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define DIM_TABELA_HASH 49

struct Client
{
	char* nume;			// 4 bytes
	unsigned int id;	// 4 bytes
	unsigned char tip;	// 1 bytes
	unsigned int puncte;// 4 bytes
	float medie_cos;	// 4 bytes
};

typedef struct Client Client;

struct Nod
{
	Client cl;
	struct Nod* next;
};

typedef struct Nod Nod;

unsigned char functieHash(unsigned int cheie)
{
	return (cheie % DIM_TABELA_HASH);
}

Nod* inserareClient(Nod* lista, Client data) // inserare la inceput in lista simpla lista
{
	Nod* nou = malloc(sizeof(Nod));
	nou->cl = data;
	nou->next = lista;

	return nou;
}

void inserareClientTabela(Nod** HT, Client data)
{
	// 1. identificare lista simpla in care data trebuie inserate
	// se realizeaza prin functie hash
	unsigned char pos = functieHash(data.id);

	// 2. inserare date client in lista identificata la pasul 1)
	HT[pos] = inserareClient(HT[pos], data);
}

Client* cautareClientCheie(Nod** HT, unsigned int cheie)
{
	// 1. determinare pozitie lista in care clientul cu id == cheie AR TREBUI sa fie stocata
	unsigned char pos = functieHash(cheie);

	// 2. cautare secventiala in lista determinata la pasul 1)
	Nod* temp = HT[pos];
	while (temp != NULL)
	{
		if (cheie == temp->cl.id)
			return &temp->cl; // cautarea se opreste la idenficarea clientului cu id cautat
		temp = temp->next;
	}

	return NULL;
}

void stergereClientTabela(Nod** HT, unsigned int cheie)
{
	// 1. determinare pozitie lista in care se plaseaza clientul
	unsigned char pos = functieHash(cheie);

	// 2. stergere nod in lista simpla corespondenta
	if (HT[pos] != NULL)
	{
		if (HT[pos]->cl.id == cheie)
		{
			// se sterge primul nod in lista simpla HT[pos]
			Nod* temp = HT[pos];
			HT[pos] = HT[pos]->next;

			free(temp->cl.nume);
			free(temp);
		}
		else
		{
			// se cauta nodul de sters in lista simpla HT[pos]
			Nod* temp = HT[pos];
			while (temp->next != NULL) // parsare lista simpla HT[pos] pana pe ultimul nod (temp)
			{
				if (temp->next->cl.id == cheie)
				{
					// temp este nodul de sters
					Nod* nodSters = temp->next;
					temp->next = nodSters->next;

					free(nodSters->cl.nume);
					free(nodSters);

					return;
				}

				temp = temp->next;
			}
		}
	}
}

int main()
{
	Nod** HashTable = NULL; // variabila acces la vector suport structura hash table alocat la run-time

	HashTable = malloc(DIM_TABELA_HASH * sizeof(Nod*)); // alocare vector suport pentru tabela hash
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++)
		HashTable[i] = NULL; // lista accesata prin HashTable[i] este marcata ca fiind empty

	FILE* f;

	f = fopen("Clienti.txt", "r");

	char buffer[256];
	char seps[] = ",\n"; // \n pentru a considera 0x0a separat astfel incat 0x0a sa nu fie parte a ultimul token

	while (fgets(buffer, sizeof(buffer), f)) // citire linie din fisier text si salvare continut linie in buffer
	{
		Client client; // variabila temporara in care sunt pregatite datele clientului conform tipuri de date din structura
		char* token = strtok(buffer, seps); // debut proces de tokenizare; buffer este bytearray care se sparge in tokeni separati de bytes conformseps
		client.nume = malloc(strlen(token) + 1); // alocare heap seg pentru fix lungimes string nume client
		strcpy(client.nume, token); //copiere string in heap seg tocmai alocat

		token = strtok(NULL, seps); // argumentul NULL asigura continarea procesului de tokenizare de la ultima pozitie a separatorului
		client.id = atoi(token); // conversie ASCII la int

		token = strtok(NULL, seps);
		client.tip = token[0]; // tip client stocheaza codul ASCII (simbolul)

		token = strtok(NULL, seps);
		client.puncte = atoi(token); // conversie ASCII la intreg

		token = strtok(NULL, seps);
		client.medie_cos = (float)atof(token); // conversie ASCII la float

		// inserare client in tabela de dispersie
		inserareClientTabela(HashTable, client);

	} // variabila temporara client este dezalocata din stack seg dupa fiecare apel de inserare nod

	fclose(f);

	printf("Tabela dispersie cu chanining:\n");
	for (unsigned char i = 0; i < DIM_TABELA_HASH; i++)
	{
		if (HashTable[i] != NULL) // lista i contine cel putin 1 nod
		{
			printf("Clientii din lista cu offset %d\n", i);
			Nod* temp = HashTable[i];
			while (temp != NULL)
			{
				printf("%d %s\n", temp->cl.id, temp->cl.nume);
				temp = temp->next;
			}
		}
	}

	Client* pClient = cautareClientCheie(HashTable, (unsigned int)2098);

	printf("\n\nCautare client pe baza de cheie in tabela hash: ");
	if (pClient != NULL)
	{
		printf("client identificat %d %s\n", pClient->id, pClient->nume);
	}
	else
	{
		printf("clientul nu este prezent in tabela de dispersie.\n");
	}

	// testare sterge client dupa cheie in tabela de dispersie

	// dezalocare tabela de dispersie, inclusiv dezalocare vectorului suport

	return 0;
}