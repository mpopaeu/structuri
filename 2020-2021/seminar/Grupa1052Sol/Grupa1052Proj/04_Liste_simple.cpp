#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 128

struct Student {
	int id;
	char* nume;
	char nrGrupa[5];
};

struct Nod {
	Student stud;
	Nod* next;
};

Nod* inserare_inceput_lista(Nod* p, Student s)
{
	Nod* nou;
	nou = (Nod*)malloc(1 * sizeof(Nod)); // se aloca 1 singur nod

	nou->stud.id = s.id;
	nou->stud.nume = s.nume;
	strcpy(nou->stud.nrGrupa, s.nrGrupa);

	nou->next = p; // succesorul lui nou este inceput lista curenta (inserare la inceput)

	return nou;
}

Nod* stergere_inceput_lista(Nod* p, Student &s)
{
	if (p) // exista cel putin 1 nod in lista
	{
		// salvare date din primul nod in parametrul s
		s.id = p->stud.id;
		s.nume = p->stud.nume;
		strcpy(s.nrGrupa, p->stud.nrGrupa);

		Nod* t = p;
		p = p->next; // noul inceput de lista

		free(t); // dezalocare inceput curent de lista
	}

	return p; // se intoarce noul inceput de lista
}

// TEMA
// inserare de nod pe pozitie specificata
// stergere de nod de pe pozitie specificata
// interschimb noduri adiacente in lista simpla pe baza pozitiei/pozitiilor celor doua noduri
// interschimb de noduri oarecare in lista simpla pe baza pozitiilor celor doua noduri
// concatenare doua liste simple in lista separata ca rezultat
// "spargere"/"rupere" lista in doua liste diferite pe baza unei pozitii specificate
// ----> testare pt diverse scenarii de apel, inclusiv pe cazuri particulare


// stergere noduri (toate) studenti care fac parte din grupa specificata
Nod* stergere_nod_grupa(Nod* lst, char* nr_grupa)
{

}

int main() {
	Nod* prim = NULL; // lista este empty
	Student s;	// locatie buffer intre sursa de date externa si lista simpla (alocata dinamic)
	FILE* f;
	f = fopen("Studenti.txt", "r");

	char * token, sep_list[] = ",\n";
	char file_buf[LINESIZE];
	while (fgets(file_buf, sizeof(file_buf), f)) { // "citeste" continut (o linie) din fisierul accesat prin f (Studenti.txt)
													// linia se copiaza din fisier in buffer-ul file_buf
		// preluare continut fisier studenti; se initializeaza temporarul s
		token = strtok(file_buf, sep_list);
		s.id = atoi(token); // conversie ASCII->Binar(int)

		token = strtok(NULL, sep_list);
		s.nume = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(s.nume, token); // copiere string in zona heap alocata in buffer-ul s

		token = strtok(NULL, sep_list);
		strcpy(s.nrGrupa, token); // copiere string in vectorul din buffer-ul s

		// operatie pe lista simpla (inserare in lista simpla)
		prim = inserare_inceput_lista(prim, s);

		s.nume = NULL; // eliminare partajare zona heap pt ultimul student inserat
	}

	// traversare listei simple (cu afisare de continut)
	printf("Continut lista simpla:\n");
	Nod* t = prim;
	while (t)
	{
		printf(" %d %s\n", t->stud.id, t->stud.nume);

		t = t->next; // modificare adresa stocata in t; dupa, t contine adresa nodului succesor
					// t devine 0/NULL cand t curent este ultimul nod
	}

	// apel functie stergere noduri/studenti in lista simpla in fct de nr grupa

	// stergere lista simpla
	printf("Dezalocare lista simpla:\n");
	while (prim)
	{
		prim = stergere_inceput_lista(prim, s); // studentul este extras in param s

		printf(" Student extras: %d %s\n", s.id, s.nume);
		free(s.nume);
		s.nume = NULL;
	}

	fclose(f);

	return 0;
}