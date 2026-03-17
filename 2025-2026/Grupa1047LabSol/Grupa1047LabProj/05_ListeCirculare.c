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

Nod* inserareCirculara(Nod* p, Client client)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare heap mem pentru un nod al listei simple (Nod)

	nou->cl = client; // salvare date in nodul nou alocat

	if (p == NULL)
	{
		nou->next = nou; // succesorul lui nou este nou; inserare prim nod in lista circulara
	}
	else
	{
		nou->next = p;

		Nod* t = p->next;
		while (t->next != p) // parsare lista circulara pana pe ultimul nod t
		{
			t = t->next;
		}

		t->next = nou; // actualizare legatura ultim nod la primul nod
	}

	return nou; // nou devine primul nod in lista circulara 
}

void traversare(Nod* p)
{
	if (p != NULL)
	{
		printf("id client = %d\n", p->cl.id); // primul nod tratat separat fata de restul de noduri

		Nod* t = p->next; // t temporar de acces la un nod al listei simple, incepand cu nodul #2
		while (t != p) // t not p insemna inca un nod de prelucrat identificat pe structura liniara lista simpla
		{
			printf("id client = %d\n", t->cl.id);

			t = t->next; // actualizare/rescriere temporar pentru acces la nod succesor in interatia urmatoare
		}
	}
}

Nod* stergereCirculara(Nod* p, unsigned int id_client)
{
	Nod* x = p;

	if (p != NULL && x->cl.id == id_client)
	{
		// codul de sters este primul nod din lista simpla
		p = p->next;// actualizare inceput de lista simpla

		if (p == x)
			p = NULL; // nodul de sters este primul si unicul din lista circulara
		else
		{
			Nod* t = p;
			while (t->next != x)
				t = t->next;
			t->next = p;
		}

		free(x->cl.denumire); // dezalocare denumire client (mai indepartat fata de sursa x)
		free(x);   // dezalocare nod din lista simpla (Nod)
	}
	else 
	{
		if (p != NULL) {


			// cautarea incepe cu nodul #2
			x = p->next;

			// t este nodul predecesor al lui x
			Nod* t = p;

			while (x != p)
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
	}

	return p;
}

Nod* stergereNodTipClient(Nod* lista, unsigned char tip_client) {
	if (lista != NULL) {

		Nod* q = lista;
		while (q->next != lista) {
			if (q->next->cl.tip == tip_client) {
				Nod* p = q->next;
				Nod* r = p->next;
				q->next = r;
				free(p->cl.denumire);
				free(p);
			}
			else // daca are loc stergerea lui p atunci q trebuie pastrat pe nod curent (nu se actualizeaza q)
				q = q->next; 
		}

		if (lista->cl.tip == tip_client) {
			Nod* r = lista->next;
			q->next = r;
			free(lista->cl.denumire);
			free(lista);
			if (lista == q)
				lista = NULL; // se dezaloca singurul nod din lista circulara
			else
				lista = r; // noul inceput de lista este nodul 2
		}
	}

	return lista;
}

int main()
{
	Nod* prim = NULL; // adresa primului nod in lista simpla; punct de acces la structura de date lista simpla stocata in heap mem
	FILE* f = NULL;

	f = fopen("Clienti.txt", "r");

	char buffer[256];   // buffer pentru stocarea unei linii din fisierul text Clienti.txt
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

		prim = inserareCirculara(prim, c); // inserare date pregatite in variabila client c intr-un nod de lista simpla
		// inseare nod cu datele pregatite in c are la inceput, deci prim se rescrie nu adresa noua dupa fiecare apel al functiei inserareNod
	}
	fclose(f);

	printf("Lista circulara dupa creare:\n");
	traversare(prim);

	prim = stergereNodTipClient(prim, 'F');
	printf("Lista circulara dupa stergee tip client\n");
	traversare(prim);

	prim = stergereCirculara(prim, 1230);
	printf("Lista circulara dupa stergere nod:\n");
	traversare(prim);

	//dezalocare structura lista circulara
	while (prim)
		prim = stergereCirculara(prim, prim->cl.id);

	printf("Lista circulara dupa dezalocare structura:\n");
	traversare(prim);

	return 0;
}