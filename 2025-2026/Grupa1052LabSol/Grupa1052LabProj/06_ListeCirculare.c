#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

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

Nod* inserareNodPozitieCirculara(Nod* p, Angajat a, unsigned int poz)
{
	Nod* nou = malloc(sizeof(Nod));
	nou->angajat = a;

	if (p == NULL)
	{
		// nou devine primul si unicul nod in lista circulara
		nou->next = nou;
		p = nou;
	}
	else
	{
		if (poz == 1)
		{
			// nodul nou se insereaza ca nou inceput de lista circulara
			nou->next = p;
			Nod* t = p;
			while (t->next != p) // parsare lista circulara pana pe ultimul nod t
				t = t->next;

			t->next = nou; // actualizare succesor pentru nodul t ultimul din lista
			p = nou;
		}
		else
		{
			// cautare locatie pentru inserare lui nou
			// poate fi la interiorul listei sau ultima pozitie din lista (inserare la sfarsit)
			Nod* t = p;
			unsigned int counter = 1;
			while (t->next != p && counter < poz - 1)
			{
				t = t->next;
				counter += 1;
			}

			Nod* q = t->next;
			nou->next = q;
			t->next = nou;
		}
	}

	return p; // se returneaza inceput (eventual diferit) de lista circulara
}


void traversareListaCirculara(Nod* p)
{
	if (p != NULL)
	{
		printf("%s %s\n", p->angajat.CNP, p->angajat.nume);
		Nod* t = p->next;
		while (t != p)
		{
			printf("%s %s\n", t->angajat.CNP, t->angajat.nume);
			t = t->next;
		}
	}
}


Nod* stergereNodNumeCirculara(Nod* p, char* nume_ang)
{
	if (p != NULL)
	{
		Nod* t = p;
		while (t->next != p) // parsare lista circulara incepand cu nodul #2 pana pe ultimul nod
		{
			if (strcmp(t->next->angajat.nume, nume_ang) == 0)
			{
				// nodul care trebuie sters este succesorului lui t
				Nod* q = t->next;
				Nod* r = q->next;

				t->next = r;

				free(q->angajat.nume);
				free(q->angajat.functie);
				free(q);
			}
			else
				t = t->next;
		}


		// t este ultimul nod din lista circulara in urma stergerilor de mai sus
		// verific daca primul nod trebuie eliminat din lista circulara
		if (strcmp(p->angajat.nume, nume_ang) == 0)
		{
			// primul nod din lista trebuie sters
			Nod* q = p;
			if (p == p->next)
			{
				p = NULL; // lista devine empty
			}
			else
			{
				// lista contine cel putin doua noduri
				p = p->next;
				t->next = p;
			}

			free(q->angajat.nume);
			free(q->angajat.functie);
			free(q);
		}
	}

	return p;
}

Nod* interschimbAdiacenteCirculara(Nod* p, unsigned int poz)
{
	if (p == NULL || p == p->next)
		return p; // nu sunt 2 noduri in lista

	if (poz == 1)
	{
		// interschimb (1,2)
		Nod* q = p;
		Nod* r = q->next;
		Nod* s = r->next;

		q->next = s;
		r->next = q;

		Nod* t = p->next;
		while (t->next != p)
		{
			t = t->next;
		}

		t->next = r;
		p = r;
	}
	else
	{
		// interschimb (poz, poz+1)
		Nod* t = p;
		unsigned int counter = 1;
		while (t->next->next != p && counter < poz - 1)
		{
			t = t->next;
			counter += 1; 
		}

		if (counter == poz - 1)
		{
			// exista pozitia poz in lista
			Nod* q = t->next;
			Nod* r = q->next;
			Nod* s = r->next;

			t->next = r;
			q->next = s;
			r->next = q;

			if (r == p)
			{
				p = q;
			}
		}
	}

	return p;
}

int main()
{
	Nod* prim = NULL; // initial, lista simpla este empty
	FILE* f;

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

		prim = inserareNodPozitieCirculara(prim, ang, 1);
	}

	fclose(f);

	printf("Lista circulara dupa creare:\n");
	traversareListaCirculara(prim);

	prim = interschimbAdiacenteCirculara(prim, 7);
	printf("\nLista circulara dupa interschimb noduri adiacente:\n");
	traversareListaCirculara(prim);

	prim = stergereNodNumeCirculara(prim, "Vasilescu Rodica");
	printf("\nLista circulara dupa stergere angajati cu acelasi nume:\n");
	traversareListaCirculara(prim);

	// dezalocare structura lista circulara
	while (prim != NULL)
	{
		prim = stergereNodNumeCirculara(prim, prim->angajat.nume);
	}
	printf("\nLista circulara dupa dezalocare structura:\n");
	traversareListaCirculara(prim);

	return 0;
}