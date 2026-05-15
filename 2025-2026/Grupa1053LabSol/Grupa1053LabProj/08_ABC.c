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

struct NodABC
{
	Client cl;
	struct NodABC* stanga, *dreapta;
};

typedef struct NodABC NodABC;

NodABC* inserareNodABC(NodABC* nod, Client data, unsigned char * gasit)
{
	if (nod != NULL)
	{
		// se continua cautarea locului de inserat (daca exista)
		if (data.id < nod->cl.id)
		{
			// se cauta locul de inserat pe stanga nodului curent
			nod->stanga = inserareNodABC(nod->stanga, data, gasit);
		}
		else
		{
			if (data.id > nod->cl.id)
			{
				// se continua cautarea locului de inserat pe sub-arborele dreapta
				nod->dreapta = inserareNodABC(nod->dreapta, data, gasit);
			}
			else
			{
				// clientul de inserat are id existent in ABC
				*gasit = 1;
				return nod;
			}
		}
	}
	else
	{
		// locul de inserat este identificat
		*gasit = 0;
		NodABC* newNode = malloc(sizeof(NodABC));
		newNode->cl = data;
		// nodul care se insereaza va fi frunza in ABC
		newNode->stanga = NULL;
		newNode->dreapta = NULL;

		return newNode; // nod = newNode;
	}

	return nod;
}

void Inordine(NodABC* nod)
{
	if (nod != NULL)
	{
		Inordine(nod->stanga);

		printf("%d %s\n", nod->cl.id, nod->cl.nume);

		Inordine(nod->dreapta);
	}
}

void cautareNodABCNume(NodABC* nod, char* nume_client)
{
	if (nod != NULL)
	{
		if (strcmp(nume_client, nod->cl.nume) == 0)
			printf("%d %s\n", nod->cl.id, nod->cl.nume);

		cautareNodABCNume(nod->stanga, nume_client);
		cautareNodABCNume(nod->dreapta, nume_client);
	}
}

Client* cautareNodABC(NodABC* nod, unsigned int cheie_client)
{
	if (nod != NULL)
	{
		// se continua cautarea locului de inserat (daca exista)
		if (cheie_client < nod->cl.id)
		{
			// se cauta locul de inserat pe stanga nodului curent
			return cautareNodABC(nod->stanga, cheie_client);
		}
		else
		{
			if (cheie_client > nod->cl.id)
			{
				// se continua cautarea locului de inserat pe sub-arborele dreapta
				return cautareNodABC(nod->dreapta, cheie_client);
			}
			else
			{
				// clientul este identificat
				return &nod->cl;
			}
		}
	}

	return NULL;
}

NodABC* dezalocareABC(NodABC* nod)
{
	if (nod != NULL)
	{
		nod->stanga = dezalocareABC(nod->stanga);
		nod->dreapta = dezalocareABC(nod->dreapta);

		free(nod->cl.nume); // dezalocare extensie in heap a clientului din nodul curent
		free(nod); // dezalocare nod in ABC

		nod = NULL;
	}

	return nod;
}

NodABC* stergereNodCheie(NodABC* nod, unsigned int cheie_client)
{
	if (nod != NULL)
	{
		if (cheie_client < nod->cl.id)
			nod->stanga = stergereNodCheie(nod->stanga, cheie_client);
		else
			if (cheie_client > nod->cl.id)
				nod->dreapta = stergereNodCheie(nod->dreapta, cheie_client);
			else
			{
				// nodul de sters este identificat
				NodABC* subarbore_stanga = nod->stanga;
				NodABC* subarbore_dreapta = nod->dreapta;

				NodABC* temp = subarbore_stanga;
				if (temp != NULL)
				{
					while (temp->dreapta != NULL)
						temp = temp->dreapta;


					// subarbore dreapta se ataseaza la subarbore stanga
					temp->dreapta = subarbore_dreapta;
				}
				else
				{
					subarbore_stanga = subarbore_dreapta; // DOAR pentru a pastra return subarbore_stanga; (vezi mai jos)
				}


				// dezalocare nod
				free(nod->cl.nume);
				free(nod);

				return subarbore_stanga;
			}
	}

	return nod;
}

// determinare numar de noduri frunza din ABC

// determinare noduri plasate pe drumul de la root la un nod in ABC

// determinare noduri plasate pe acelasi nivel in ABC

// modificare date in ABC pe baza criteriu definit

int main()
{
	NodABC* root = NULL; // root este punctul de acces la structura ABC
	FILE* f;

	f = fopen("Clienti.txt", "r");

	char buffer[256];
	char seps[] = ",\n"; // \n pentru a considera 0x0a separat astfel incat 0x0a sa nu fie parte a ultimul token

	while (fgets(buffer, sizeof(buffer), f)) // citire linie din fisier text si salvare continut linie in buffer
	{
		Client client; // variabila temporara in care sunt pregatite datele clientului conform tipuri de date din structura
		char* token = strtok(buffer, seps); // debut proces de tokenizare; buffer este bytearray care se sparge in tokeni separati de bytes conformseps
		client.nume = malloc(strlen(token) + 1); // alocare heap seg pentru fix lungime string nume client
		strcpy(client.nume, token); //copiere string in heap seg tocmai alocat

		token = strtok(NULL, seps); // argumentul NULL asigura continarea procesului de tokenizare de la ultima pozitie a separatorului
		client.id = atoi(token); // conversie ASCII la int

		token = strtok(NULL, seps);
		client.tip = token[0]; // tip client stocheaza codul ASCII (simbolul)

		token = strtok(NULL, seps);
		client.puncte = atoi(token); // conversie ASCII la intreg

		token = strtok(NULL, seps);
		client.medie_cos = (float)atof(token); // conversie ASCII la float

		// inserare client in ABC
		unsigned char gasit;
		root = inserareNodABC(root, client, &gasit);

		if (gasit == 1)
		{
			// exista id client deja inserat anterior in ABC
			free(client.nume);
		}

	} // variabila temporara client este dezalocata din stack seg dupa fiecare apel de inserare nod

	fclose(f);

	printf("ABC dupa creare:\n");
	Inordine(root);

	Client* pClient = cautareNodABC(root, 8973);
	printf("\n///////// CAUTARE DUPA CHEIE in ABC ///////////\n");
	if (pClient != NULL)
	{
		printf("Client identificat in ABC: %d %s\n", pClient->id, pClient->nume);
	}
	else
	{
		printf("Clientul cautat dupa cheie nu este stocat in ABC.\n");
	}

	printf("\n///////// CAUTARE DUPA NON-CHEIE in ABC ///////////\n");
	cautareNodABCNume(root, "Vasilescu Mircea");

	root = stergereNodCheie(root, 386);
	printf("\n///////// ABC dupa STERGERE PE BAZA DE CHEIE///////\n");
	Inordine(root);

	//root = dezalocareABC(root);
	while (root != NULL)
	{
		root = stergereNodCheie(root, root->cl.id);
	}
	printf("\n///////// ABC dupa DEZALOCARE ///////////\n");
	Inordine(root);

	return 0;
}