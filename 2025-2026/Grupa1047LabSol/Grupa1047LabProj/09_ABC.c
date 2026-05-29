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

struct NodABC {
	Client cl;
	struct NodABC* stanga, *dreapta; 
};

typedef struct NodABC NodABC;

NodABC* inserareClientABC(NodABC* nodCurent, Client data, unsigned char *flag_inserare)
{
	if (nodCurent != NULL)
	{
		if (nodCurent->cl.id < data.id)
		{
			// nodul cu data trebuie inserat la dreapta nodului curent
			// se continua cautarea pozitiei de inserat in sub-arborele dreapta
			nodCurent->dreapta = inserareClientABC(nodCurent->dreapta, data, flag_inserare);
		}
		else
		{
			if (nodCurent->cl.id > data.id)
			{
				// nodul cu data trebuie inserat la stanga nodului curent
				// se continua cautarea pozitiei de inserat in sub-arborele stanga
				nodCurent->stanga = inserareClientABC(nodCurent->stanga, data, flag_inserare);
			}
			else
			{
				// cheie din data exista deja in ABC
				// se abandoneaza inserarea datelor cu cheie duplicat
				*flag_inserare = 0; // inserare abandonata
				return nodCurent;
			}
		}
	}
	else
	{
		// nodCurent este NULL; pozitia de inserat in ABC a fost identificata
		// nodul cu data se insereaza in ABC
		NodABC* nou = malloc(sizeof(NodABC));
		nou->cl = data;
		// nodul inserat este mereu nod frunza in ABC
		nou->stanga = NULL;
		nou->dreapta = NULL;

		*flag_inserare = 1; // flag pentru marcare inserare cu succes
		return nou;
	}

	return nodCurent;
}

void InordineABC(NodABC* nodCurent)
{
	if (nodCurent != NULL)
	{
		InordineABC(nodCurent->stanga); // prelucrare date/noduri din sub-arborele stanga al nodului curent
		printf("%d %s\n", nodCurent->cl.id, nodCurent->cl.denumire); // prelucrare nod curent
		InordineABC(nodCurent->dreapta); // prelucrare date/noduri din sub-arborele dreapta al nodului curent
	}
}

NodABC* dezalocareNoduriABC(NodABC* nodCurent)
{
	if (nodCurent != NULL)
	{
		nodCurent->stanga = dezalocareNoduriABC(nodCurent->stanga); // stergere noduri din subarborele stanga
		nodCurent->dreapta = dezalocareNoduriABC(nodCurent->dreapta); // stergere noduri din subarborele dreapta

		free(nodCurent->cl.denumire); // dezalocare extensie client in mem heap
		free(nodCurent); // dezalocare nod

		nodCurent = NULL;
	}

	return nodCurent;
}

Client* cautareClientCheie(NodABC* nodCurent, unsigned int cheie_client)
{
	if (nodCurent != NULL)
	{
		if (cheie_client < nodCurent->cl.id)
		{
			// se continua cautarea pe sub-arborele stanga
			return cautareClientCheie(nodCurent->stanga, cheie_client);
		}
		else
		{
			if (cheie_client > nodCurent->cl.id)
			{
				// se continua cautarea pe sub-arborele dreapta
				return cautareClientCheie(nodCurent->dreapta, cheie_client);
			}
			else
			{
				// noc curent contine cheie cautata
				return &nodCurent->cl; // se returneaza adresa clientului din nod curent
			}
		}
	}
	
	return NULL;
}

NodABC* stergereNodCheie(NodABC* nodCurent, unsigned int cheie_client, Client * client_extras)
{
	if (nodCurent != NULL)
	{
		if (cheie_client < nodCurent->cl.id)
		{
			// se continua cautarea pe sub-arborele stanga
			nodCurent->stanga = stergereNodCheie(nodCurent->stanga, cheie_client, client_extras);
		}
		else
		{
			if (cheie_client > nodCurent->cl.id)
			{
				// se continua cautarea pe sub-arborele dreapta al nodului curent
				nodCurent->dreapta = stergereNodCheie(nodCurent->dreapta, cheie_client, client_extras);
			}
			else
			{
				// nodCurent este nodul de sters
				*client_extras = nodCurent->cl; // salvare date client in parametru de iesire din functie
				if (nodCurent->stanga == NULL && nodCurent->dreapta == NULL)
				{
					// nodul de sters este nod frunza
					free(nodCurent);
					nodCurent = NULL; // permite salvarea in parinte a adresei de NULL pe directia lui nodCurent inainte de stergere
				}
				else
				{
					if (nodCurent->stanga != NULL && nodCurent->dreapta != NULL)
					{
						// nodul de sters are 2 descendenti
						NodABC* desc_stanga = nodCurent->stanga;
						NodABC* desc_dreapta = nodCurent->dreapta;

						free(nodCurent);

						NodABC* temp = desc_dreapta;
						while (temp->stanga)
							temp = temp->stanga;

						temp->stanga = desc_stanga; // alipirea sub-arborelui stanga ca descendent stanga al nodului cu cheie minima din sub-arborele dreapta

						nodCurent = desc_dreapta;
					}
					else
					{
						// nodul de sters are un singur descendent
						NodABC* desc_unic = nodCurent->stanga;
						if (nodCurent->dreapta != NULL)
							desc_unic = nodCurent->dreapta;

						free(nodCurent);
						nodCurent = desc_unic;
					}
				}
			}
		}
	}
	else
	{
		// nodul cautat nu exista in ABC
		client_extras->denumire = NULL;
	}

	return nodCurent;
}

// determinare nr de noduri frunza

// determinare nr de noduri cu 2 descendenti

// determinare noduri (salvare date) plasate pe un nivel specificat la ca parametru al functiei

// determinare nr clienti cu valoarea comenzilor sub un prag specificat ca parametru




// functie pentru crearea unei liste simple cu clientii plasati pe drumul invers de la un nod
// identificat pe baza de id client spre radacina arbore

int main()
{
	NodABC* root = NULL; // adresa nod radacina; pointer null inseamna structura ABC empty
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
		strcpy(c.ultima_comanda, token); // copiere string in campul ultima_comanda

		token = strtok(NULL, sep); // identificare token urmator in buffer
		c.valoare_totala_comenzi = (float)atof(token); // conversie ASCII-to-float si salvare rezultat in campul valoare_totala_comenzi

		unsigned char flag = 0;
		root = inserareClientABC(root, c, &flag);

		if (flag == 1)
		{
			printf("Inserare cu succes a clientului %d\n", c.id);
		}
		else
		{
			printf("Inserare esuata a clientului %d\n", c.id);
			// extensii client trebuie dezalocate pentru a evita memory leaks
			free(c.denumire);
		}
	}

	fclose(f);

	printf("ABC dupa creare:\n");
	InordineABC(root);

	Client* pclient = cautareClientCheie(root, 81);
	printf("\n///////////////// CAUTARE client dupa cheie ////////////////\n");
	if (pclient != NULL)
	{
		printf("Client identificat in ABC: %d %s:", pclient->id, pclient->denumire);
	}
	else
	{
		printf("Clientul cauta nu exista in ABC");
	}

	root = stergereNodCheie(root, 12, &c);
	printf("\n//////////// STERGERE CLIENT pe baza de cheie in ABC ////////////\n");
	if (c.denumire != NULL)
	{
		printf("Client eliminat din ABC: %d %s\n", c.id, c.denumire);
		free(c.denumire);
	}
	else
	{
		printf("Clientul nu a fost identificat in ABC.\n");
	}
	printf("\n//////////// ABC dupa stergere client pe baza de CHEIE ////////////\n");
	InordineABC(root);

	root = dezalocareNoduriABC(root);
	printf("\n//////////// ABC dupa dezalocare ////////////\n");
	InordineABC(root);

	return 0;
}