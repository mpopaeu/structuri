#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Client
{
	unsigned int id;
	char* denumire;
	unsigned char tip;
	char ultima_comanda[11]; // 10 + 1; +1 pentru spatiu necesar terminatorului de string (byte 0x00)
	float valoare_totala_comenzi;
};

typedef struct Client Client;

struct Nod {
	Client cl;
	struct Nod* next; // adresa nodului succesor pentru nod curent
};

typedef struct Nod Nod;

Nod* inserareNod(Nod* p, Client client)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare heap mem pentru un nod al listei simple (Nod)

	nou->cl = client; // salvare date in nodul nou alocat
	nou->next = p;	  // salvare date de organizare a structurii (implementare relatie de ordine pe structura liniar lista simpla)

	return nou; // return nod nou alocat si initializat in apelator => inserare nod nou la inceputul listei (pozitia 1)
}

unsigned short int functie_hash(unsigned int cheie, unsigned short int size_tabela)
{
	return (cheie % size_tabela); // rezultatul trebuie sa fie cuprins in [0; size_tabela - 1] ca offset valid pe tabela hash
}

void inserareClientHT(Nod** tabela, unsigned short int size_tabela, Client c)
{
	// 1. determinare pozitie lista simpla in care se salveaza clientul c
	unsigned short int poz = functie_hash(c.id, size_tabela);
	printf("Pozitie in tabela pentru %s -> %d\n", c.denumire, poz);

	// 2. inserarea date client c in lista simpla corespondenta
	tabela[poz] = inserareNod(tabela[poz], c);
}

Client* cautareClientId(Nod** tabela, unsigned short int size_tabela, unsigned int cheie_cautata)
{
	// 1. determinare pozitie lista simpla in care clientrul cu id==cheie_cautata are trebui sa fie stocat
	unsigned short int poz = functie_hash(cheie_cautata, size_tabela);

	Nod* t = tabela[poz]; // t pentru parsare lista simpla tabela[poz]
	while (t != NULL)
	{
		if (t->cl.id == cheie_cautata)
			return &t->cl; // return adresa client din nodul care contine id cautat (cheie_cautata)

		t = t->next;
	}

	return NULL; // clientul cautat nu exista in tabela de dispersie
}

Nod* stergereNod(Nod* p, unsigned int id_client)
{
	Nod* x = p;

	if (x->cl.id == id_client)
	{
		// nodul de sters este primul nod din lista simpla
		p = p->next;// actualizare inceput de lista simpla

		free(x->cl.denumire); // dezalocare denumire client (mai indepartat fata de sursa x)
		free(x);   // dezalocare nod din lista simpla (Nod)
	}
	else
	{
		// cautarea incepe cu nodul #2
		x = p->next;

		// t este nodul predecesor al lui x
		Nod* t = p;

		while (x != NULL)
		{
			if (x->cl.id == id_client)
			{
				// client de sters este identificat in lista simpla
				t->next = x->next; // nodul x este izolat de lista simpla (stergere logica al lui x)

				// stergere/dezalocare fizica nod x
				free(x->cl.denumire);
				free(x);

				return p; // opresc fortat traversarea inutila a nodurilor ramase (id client este unic)
			}

			t = x; // actualizare cu x curent care devine predecesor pe linia urmatoare
			x = x->next; // modific x cu adresa nod succesor
		}
	}

	return p;
}

void stergereClientHT(Nod** tabela, unsigned short int size_tabela, unsigned int cheie_stergere)
{
	// 1. determinare pozitie lista simpla din care se sterge clientul cu cheie_stergere==id
	unsigned short int poz = functie_hash(cheie_stergere, size_tabela);

	// 2. stergere nod cu datele clientului din lista simpla tabela[poz]
	tabela[poz] = stergereNod(tabela[poz], cheie_stergere);
}

int main()
{
	Nod* *HT = NULL; // adresa vector alocat la runtime care contine adrese de inceput de liste simple
	unsigned short int size = 59; // dimensiune vector HT (nr maxim de liste simple in care se salveaza clienti)

	HT = malloc(size * sizeof(Nod*)); // alocare vector cu adrese de inceput de liste simple (59 liste simple)
	for (unsigned short int i = 0; i < size; i++) // initial, toate listele din HT sunt marcate ca fiind empty
		HT[i] = NULL; 

	FILE* f = NULL;

	f = fopen("Clienti.txt", "r");

	char buffer[256]; // buffer pentru stocarea unei linii din fisierul text Clienti.txt
	char sep[] = ",\n"; // lista separatori pentru identificare de tokeni (sub-stringuri)
	Client c;

	while (fgets(buffer, sizeof(buffer), f)) // preluare continut din fisierul text Clienti.txt (o linie)
	{
		char* token = strtok(buffer, sep);	// identificare token #1 in linia salvata in buffer
		c.id = atoi(token); // conversie ASCII-to-int si stocare rezultat in campul id

		token = strtok(NULL, sep); // identificare token urmator in buffer
		c.denumire = malloc(strlen(token) + 1); // +1 pentru spatiu necesar terminatorului de string
		strcpy(c.denumire, token); // copiere text in campul denumire

		token = strtok(NULL, sep); // identificare token urmator in buffer
		c.tip = token[0]; // stocare valoare numerica (cod ASCII) in campul tip

		token = strtok(NULL, sep); // identificare token urmator in buffer
		strcpy(c.ultima_comanda, token); // copiee string in campul ultima_comanda

		token = strtok(NULL, sep); // identificare token urmator in buffer
		c.valoare_totala_comenzi = (float)atof(token); // conversie ASCII-to-float si salvare rezultat in campul valoare_totala_comenzi

		inserareClientHT(HT, size, c);
	}

	fclose(f);

	printf("\nContinut tabela de dispersie:\n");
	for (unsigned short int i = 0; i < size; i++)
	{
		if (HT[i] != NULL)
		{
			// lista simpla HT[i] contine cel putin 1 nod/client
			printf("Lista %d:\n", i);
			Nod* t = HT[i];
			// parsare lista simpla HT[i]
			while (t != NULL)
			{
				printf("%d %s\n", t->cl.id, t->cl.denumire);
				t = t->next;
			}
		}
	}

	Client* client_cautat = cautareClientId(HT, size, 70);
	printf("\nCautare client dupa cheie in tabela de dispersie:\n");
	if (client_cautat == NULL)
		printf("Clientul cautat nu exista in tabela hash.\n");
	else
		printf("Clientul cautat exista in tabela hash: %d %s\n", client_cautat->id, client_cautat->denumire);

	stergereClientHT(HT, size, 70);
	client_cautat = cautareClientId(HT, size, 70);
	printf("\nCautare client dupa stergere in tabela de dispersie:\n");
	if (client_cautat == NULL)
		printf("Clientul cautat nu exista in tabela hash.\n");
	else
		printf("Clientul cautat exista in tabela hash: %d %s\n", client_cautat->id, client_cautat->denumire);


	// dezalocare tabela de dispersie
	// 1. dezalocare liste simple
	for (unsigned short int i = 0; i < size; i++)
	{
		while (HT[i] != NULL)
		{
			HT[i] = stergereNod(HT[i], HT[i]->cl.id); // dezalocare nod prim din lista HT[i]
		}
	}

	// 2. dezalocare vector suport
	free(HT); 
	HT = NULL;

	return 0;
}