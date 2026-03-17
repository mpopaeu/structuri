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

struct NodD {
	Client cl;
	struct NodD * prev, *next; // adresa nodului succesor pentru nod curent
};

typedef struct NodD NodD;

struct ListaDubla
{
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserareNodD(ListaDubla list, Client client)
{
	NodD* nou = malloc(sizeof(NodD)); // alocare heap mem pentru un nod al listei duble (NodD)

	nou->cl = client; // salvare date in nodul nou alocat
	nou->next = list.prim;	  // salvare date de organizare a structurii (implementare relatie de ordine pe structura liniara lista dubla)
	nou->prev = NULL;

	if (list.prim == NULL)
	{
		// lista dubla este empty
		list.ultim = nou;
	}
	else
	{
		list.prim->prev = nou; // primul nod curent al listei va avea predecesor pe nou
	}
	list.prim = nou; // nou devine primul nod in lista

	return list; // return pachet adrese cu ambele capete ale listei duble
}

void parsareListaDubla(ListaDubla list)
{
	printf("\nLista dubla prim->ultim:\n");
	NodD* t = list.prim;
	while (t)
	{
		printf("%d %s\n", t->cl.id, t->cl.denumire);
		t = t->next;
	}

	printf("\nLista dubla ultim->prim:\n");
	t = list.ultim;
	while (t)
	{
		printf("%d %s\n", t->cl.id, t->cl.denumire);
		t = t->prev;
	}
}

int main()
{
	ListaDubla listaD;
	listaD.prim = listaD.ultim = NULL; // marcaj pentru lista dubla empty; ambele capete sunt pointeri nuli
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

		listaD = inserareNodD(listaD, c); // inserare date pregatite in variabila client c intr-un nod de lista simpla
		// inserare nod cu datele pregatite in c are la inceput, deci prim se rescrie nu adresa noua dupa fiecare apel al functiei inserareNod
	}
	fclose(f);

	printf("Lista dubla dupa creare:\n");
	parsareListaDubla(listaD);

	// stergere noduri in lista dubla
	// dezalocare structura lista dubla

	return 0;
}