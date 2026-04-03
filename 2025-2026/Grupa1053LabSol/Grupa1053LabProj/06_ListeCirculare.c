#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

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


Nod* inserareAscIdCirculara(Nod* list, Client c)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->cl = c; // datele sunt salvate in nod alocat in heap seg

	if (list == NULL)
	{
		// lista circulara empty
		nou->next = nou; // primul nod pointeaza catre el insusi
		list = nou;
	}
	else
	{
		// lista contine cel putin 1 nod
		if (c.id < list->cl.id)
		{
			// inserare nod la inceput lista circulara
			nou->next = list;

			Nod* t = list;
			while (t->next != list) // parsare lista circulara pana pe ultimul nod
				t = t->next;

			t->next = nou;
			list = nou;
		}
		else
		{
			// inserare nod interior lista circulara
			Nod* t = list;

			while (t->next != list && t->next->cl.id < c.id) // parsare lista circulara pana la nodul t dupa care tb inserat nou
				t = t->next;

			Nod* p = t->next;
			nou->next = p;
			t->next = nou;
		}
	}

	return list;
}

void parsareCirculara(Nod* list)
{
	if (list != NULL)
	{
		printf("%d %s\n", list->cl.id, list->cl.nume); // primul nod prelucrat in afara lui while care are conditie bazata pe primul nod
		Nod* t = list->next; // t pleaca de pe nodul #2 in parsarea listei circulare
		while (t != list)
		{
			printf("%d %s\n", t->cl.id, t->cl.nume);
			t = t->next;
		}
	}
}


Nod* stergereNodMedie(Nod* list, float medie)
{
	if (list != NULL)
	{
		// exista cel putin 1 nod in lista circulara

		// parsez lista circulara incepand cu nodul #2 
		// pentru a evita traversari aditionale in vederea actualizarii succesorului ultimului nod catre inceput
		// actualizat de lista circulara
		Nod* t = list;
		while (t->next != list)
		{
			if (t->next->cl.medie_cos == medie)
			{
				// nodul t->next trebuie sters din lista circulara
				Nod* p = t->next; // nodul p este nodul de sters
				Nod* q = p->next; // q este noul succesor pentru t
				t->next = q; //

				free(p->cl.nume);
				free(p);
			}
			else
				t = t->next;
		}

		// verificare medie cos in primul nod al listei circulare
		if (list->cl.medie_cos == medie)
		{
			Nod* p = list;
	
			if (t == list)
			{
				// lista contine un singur nod 
				list = NULL;
			}
			else
			{
				list = list->next; // nou inceput de lista circulara
				t->next = list; // actualizare succesor catre nou inceput de lista circulara
			}

			free(p->cl.nume);
			free(p);
		}
	}

	return list;
}

Nod* interschimbAdiacentePozitie(Nod* list, unsigned short int poz)
{
	if (list == NULL || list->next == list)
		return list;
	
	if (poz == 1)
	{
		Nod* p = list;
		Nod* q = p->next;
		Nod* r = q->next;
		if (r == p)
		{
			//lista contine 2 noduri care se interschimba
			q->next = p;
			p->next = q;
			list = q;
		}
		else
		{
			Nod* t = list;
			while (t->next!=list)
			{
				t = t->next;
			}
			t->next = q;
			p->next = r;
			q->next = p;
			list = q;
		}
	}
	else
	{
		int c = 1;
		Nod* t = list;
		while(t->next->next!=list && c<poz-1)
		{ 
			t = t->next;
			c++;
		}
		if (c == poz - 1)
		{
			Nod* p = t->next;
			Nod* q = p->next;
			Nod* r = q->next;
			if (q == list)
			{
				//se interschimba ultimul cu primul
				t->next = q;
				p->next = r;
				q->next = p;
				list = p;
			}
			else
			{
				//se interschimba poz cu poz+1 in interiorul listei
				t->next = q;
				p->next = r;
				q->next = p;
			}
		}
	}
	return list;
}

int main()
{
	Nod* prim = NULL; // lista marcata ca fiind empty

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

		prim = inserareAscIdCirculara(prim, client); // inserare date client in nod lista circulara
	} // variabila temporara client este dezalocata din stack seg dupa fiecare apel de inserare nod

	fclose(f);

	printf("Lista simpla circulara dupa creare: \n");
	parsareCirculara(prim);

	prim = interschimbAdiacentePozitie(prim, 7);
	printf("Lista circulara dupa interschimbare:\n");
	parsareCirculara(prim);

	prim = stergereNodMedie(prim, (float)289.01);
	printf("Lista simpla circulara dupa stergere noduri: \n");
	parsareCirculara(prim);

	// dezalocare lista circulara
	while (prim != NULL)
	{
		prim = stergereNodMedie(prim, prim->cl.medie_cos);
	}
	printf("Lista simpla circulara dupa dezalocare: \n");
	parsareCirculara(prim);

	return 0;
}