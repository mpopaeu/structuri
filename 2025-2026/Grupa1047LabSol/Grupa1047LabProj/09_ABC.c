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
		strcpy(c.ultima_comanda, token); // copiee string in campul ultima_comanda

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

	return 0;
}