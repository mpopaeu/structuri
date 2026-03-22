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

Nod* inserareNodPozitie(Nod *p, Angajat a, unsigned int poz)
{
	Nod* nou = malloc(sizeof(Nod)); // alocare nod nou pentru lista simpla
	nou->angajat = a; // salvare data angajat in nodul care se insereaza pe pozitie data poz

	if (p == NULL)
	{
		// lista este empty
		nou->next = NULL;
		return nou; // nou devine inceput de lista (nodul #1)
	}
	else
	{
		Nod* t = p;

		if (poz == 1)
		{
			// nou se insereaza pe poz 1, deci se modifica adresa de inceput a listei
			nou->next = p;
			return nou;
		}
		else
		{
			unsigned int contor = 1;
			while (t->next && contor < poz - 1)
			{
				contor += 1;
				t = t->next;
			}

			if (t->next)
			{
				// t nu este ultimul nod din lista
				// t se afla pe poz-1 in lista
				// nou se insereaza pe poz
				nou->next = t->next;
				t->next = nou;
			}
			else
			{
				// t este ultimul nod din lista
				// nou devine ultimul nod
				nou->next = NULL; // NULL poate fi inlocuit cu t->next care este NULL; cod redundant pe ambele variante de if; putem elimina if si pastra 2 linii de cod pentru ambele situatii
				t->next = nou;
			}
		}
	}

	return p;
}

void traversareLista(Nod* p)
{
	Nod* t = p;
	while (t)
	{
		printf("%s %s\n", t->angajat.CNP, t->angajat.nume);
		t = t->next;
	}
}

Nod* stergereNodNume(Nod* p, char* nume_ang)
{
	if (p)
	{
		while (p && strcmp(p->angajat.nume, nume_ang) == 0)
		{
			Nod* t = p;
			p = p->next;
			free(t->angajat.nume); // dezalocare nume angajat
			free(t->angajat.functie); // dezalocare functie angajat
			free(t); // dezalocare nod lista simpla
		}
		if (p)
		{
			// lista contine noduri care trebuie verificate/sterse
			Nod* x = p;
			while (x->next)
			{
				Nod* t = x->next;
				if (strcmp(t->angajat.nume, nume_ang) == 0)
				{
					x->next = t->next;
					free(t->angajat.nume);
					free(t->angajat.functie);
					free(t);
				}
				else
					x = x->next;
			}
		}
	}

	return p;
}

Angajat* angajatiVechime(Nod* lista, unsigned char vechime_angajati, unsigned char* size_vector)
{
	// 1 Trebuie sa stiu marimea la size_vector
	// adica nr angajati vector
	Nod* t = lista;
	*size_vector = 0;
	while (t) {
		if (t->angajat.vechime_ani == vechime_angajati) {
			*size_vector += 1;
		}
		t = t->next;
	}
	// 2 Alocare vector pentru numarul de angajati
	
	Angajat* v = NULL;

	if (*size_vector > 0) {
		v = malloc(sizeof(Angajat) * (*size_vector));

		// 3 Scrierea datelor din lista in vector (fara partajare de zone heap angajati)

		t = lista;
		int poz = 0;
		while (t) {
			if (t->angajat.vechime_ani == vechime_angajati) {
				v[poz] = t->angajat; // temporar vectorul si lista partajeaza zone de heap pentru nume si functie angajat
				v[poz].nume = malloc(strlen(t->angajat.nume) + 1);
				v[poz].functie = malloc(strlen(t->angajat.functie) + 1);
				strcpy(v[poz].nume, t->angajat.nume);
				strcpy(v[poz].functie, t->angajat.functie);
				poz++;
			}
			t = t->next;
		}
	}

	return v;
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

		prim = inserareNodPozitie(prim, ang, 2);
	}

	fclose(f);

	printf("Lista dupa creare:\n");
	traversareLista(prim);

	// copiere angajati care au aceeasi vechime pentru datele stocate in lista simpla
	// structura output este un vector
	// functie + apel + dezalocari (eventual)

	Angajat* v;
	unsigned char size;

	v = angajatiVechime(prim, 10, &size);
	printf("Angajati cu aceasi vechime \n");
	for (int i = 0; i < size; i++) {
		printf("%s %s\n", v[i].CNP, v[i].nume);
	}

	prim = stergereNodNume(prim, "Vasilescu Rodica");
	printf("Lista dupa stergere nod:\n");
	traversareLista(prim);

	// dezalocare lista prin dezalocari repetate de noduri
	// numele angajatului se preia intotdeauna din primul nod al listei
	while (prim)
	{
		prim = stergereNodNume(prim, prim->angajat.nume);
	}

	printf("Lista dupa dezalocare lista:\n");
	traversareLista(prim);

	// dezalocare vector de angajati

	for (int i = 0; i < size; i++) {
		free(v[i].nume);
		free(v[i].functie);
	}

	free(v);
	v = NULL;

	// migrare implementare pe liste duble

	return 0;
}