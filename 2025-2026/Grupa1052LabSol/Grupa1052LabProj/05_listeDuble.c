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

struct NodD
{
	Angajat angajat;
	struct NodD* next, *prev;
};

typedef struct NodD NodD;

struct ListaDubla {
	NodD* prim, * ultim;
};

typedef struct ListaDubla ListaDubla;

ListaDubla inserareNodPozitie(ListaDubla list, Angajat a, unsigned int poz)
{
	NodD* nou = malloc(sizeof(NodD)); // alocare nod nou pentru lista simpla
	nou->angajat = a; // salvare data angajat in nodul care se insereaza pe pozitie data poz

	if (list.prim == NULL)
	{
		// lista este empty
		nou->next = NULL;
		nou->prev = NULL;
		list.prim = list.ultim = nou;
		return list; // nou devine inceput si sfarsit de lista dubla (nodul #1)
	}
	else
	{
		if (poz == 1)
		{
			// nou se insereaza pe poz 1, deci se modifica adresa de inceput a listei duble
			nou->next = list.prim;
			nou->prev = NULL;
			list.prim = nou; // nou devine primul nod in lista dubla
			return list;
		}
		else
		{
			NodD* t = list.prim;
			unsigned int contor = 1;
			while (t->next && contor < poz - 1)
			{
				contor += 1;
				t = t->next;
			}

			if (t->next != NULL)
			{
				// inserare la interior in lista dubla
				NodD* p = t->next;

				nou->next = p;
				nou->prev = t;

				t->next = nou;
				p->prev = nou;
			}
			else
			{
				// inserare la sfarsit in lista dubla
				nou->next = NULL;
				nou->prev = t;

				t->next = nou;
				list.ultim = nou;
			}
			
		}
	}

	return list;
}

void traversareListaDubla(ListaDubla list)
{
	printf("Traversare prim->ultim:\n");
	NodD* t = list.prim;
	while (t != NULL)
	{
		printf("%s %s\n", t->angajat.CNP, t->angajat.nume);
		t = t->next;
	}

	printf("Traversare ultim->prim:\n");
	t = list.ultim;
	while (t != NULL)
	{
		printf("%s %s\n", t->angajat.CNP, t->angajat.nume);
		t = t->prev;
	}
}

ListaDubla stergereNodNume(ListaDubla list, char* nume_ang)
{
	NodD* t = list.prim;

	while (t != NULL)
	{
		if (strcmp(t->angajat.nume, nume_ang) == 0)
		{
			// nodul t este identificat pentru stergere
			if (t->prev == NULL && t->next == NULL)
			{
				// t este unicul nod din lista dubla care trebuie eliminat
				free(t->angajat.nume);
				free(t->angajat.functie);
				free(t); // dezalocare nod
				list.prim = list.ultim = NULL; // lista dubla devine empty
			}
			else
			{
				if (t->prev == NULL)
				{
					// t este primul nod in lista dubla
					list.prim = t->next;
					list.prim->prev = NULL;

					free(t->angajat.nume);
					free(t->angajat.functie);
					free(t); // dezalocare nod

					t = list.prim; // cautarea nodurilor se continua cu nodul #2 din lista dubla care devine nou inceput
				}
				else
				{
					if (t->next == NULL)
					{
						// t este ultimul nod din lista dubla
						list.ultim = t->prev;
						list.ultim->next = NULL;

						free(t->angajat.nume);
						free(t->angajat.functie);
						free(t); // dezalocare nod

						t = NULL; // lista dubla a fost traversata si verificata pentru stergere
					}
					else
					{
						// t este nod la interior listei duble
						NodD* p, * r;
						p = t->prev;
						r = t->next;

						p->next = r;
						r->prev = p;

						free(t->angajat.nume);
						free(t->angajat.functie);
						free(t); // dezalocare nod

						t = r; // actulizare t la r pentru verificare iteratie urmatoare
					}
				}
			}
		}
		else
			t = t->next; // mutare t pe nod succesor
	}

	return list;
}

int main()
{
	ListaDubla listaD;
	listaD.prim = listaD.ultim = NULL; // lista dubla empty

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

		listaD = inserareNodPozitie(listaD, ang, 2);
	}

	fclose(f);

	printf("\n\nTraversare lista dubla dupa creare:\n");
	traversareListaDubla(listaD);

	// dezalocare lista dubla 
	return 0;
}