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

Nod* inserareAscId(Nod* p, Client c)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->cl = c; // datele sunt salvate in nod alocat in heap seg
	
	if (p == NULL) 
	{
		// lista este empty; nou devine primul si unicul nod din lista
		nou->next = NULL;
		return nou;
	}
	else
	{
		// lista contine cel putin 1 nod
		if (nou->cl.id < p->cl.id)
		{
			// id nod nou este mai mic decat id inceput de lista
			// nou debine noul inceput de lista
			nou->next = p; // p devine nodul #2 in lista
			return nou;
		}
		else
		{
			// nodul nou are id peste cel din primul nod
			Nod* t = p;
			if (t->next == NULL)
			{
				nou->next = NULL;
				t->next = nou;
			}
			else
			{
				// lista contine cel putin 2 noduri
				while (t->next)
				{
					if (t->next->cl.id > nou->cl.id)
					{
						nou->next = t->next;
						t->next = nou;
						return p;
					}

					t = t->next;
				}
				
				// t este ultimul nod
				nou->next = NULL; // nou devine ultimul nod din lista
				t->next = nou;
			}

			return p;
		}
	}

}

void traversare(Nod* p)
{
	Nod* t = p;
	while (t)
	{
		printf("%d %s\n", t->cl.id, t->cl.nume);
		t = t->next;
	}
}

Nod* stergereNodMedie(Nod* p, float medie)
{

	if (p)
	{
		while (p && p->cl.medie_cos == medie)
		{
			// cel putin 1 nod de sters la inceputul listei
			Nod* t = p; // t este primul nod care se sterge
			p = p->next; // p devine nodul #2

			free(t->cl.nume); // dezalocare nume client
			free(t); // dezalocare nod t
		}
		if (p)
		{
			// p nu contine media pentru stergere
			Nod* x = p;
			while (x->next)
			{
				// cautare nod succesor care satisface conditia de stergere
				if (x->next->cl.medie_cos == medie)
				{
					Nod* t = x->next;
					x->next = t->next; // refacere legatura succesor x catre succesor t

					free(t->cl.nume);
					free(t);
				}
				else
					x = x->next;
			}
		}
	}

	return p;
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
		char * token = strtok(buffer, seps); // debut proces de tokenizare; buffer este bytearray care se sparge in tokeni separati de bytes conformseps
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

		prim = inserareAscId(prim, client); // inserare date client in nod lista simpla
	} // variabila temporara client este dezalocata din stack seg dupa fiecare apel de inserare nod

	fclose(f);

	printf("Lista simpla dupa creare: \n");
	traversare(prim);

	prim = stergereNodMedie(prim, (float)289.49);
	printf("Lista simpla dupa stergere nod:\n");
	traversare(prim);

	// dezalocare lista simpla prin dezalocare noduri cu media preluata din primul nod al listei simple
	while (prim)
	{
		prim = stergereNodMedie(prim, prim->cl.medie_cos);
	}

	printf("Lista simpla dupa dezalocare:\n");
	traversare(prim);


	return 0;
}