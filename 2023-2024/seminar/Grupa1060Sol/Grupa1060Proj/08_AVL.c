#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct User
{
	char* nume_cont;
	char* nume_user;
	unsigned char varsta;
	char deschis_la[11]; // 10 bytes pt data calendaristica + 1 byte pt terminator string (0x00)
};

typedef struct User User;

struct NodAVL
{
	unsigned short int id_user;
	User u;
	struct NodAVL* st, * dr;
	char grad_echilibru;
};

typedef struct NodAVL NodAVL;

// maximul a doi intregi
int maxim(int a, int b) {
	return a > b ? a : b;
}


// inaltime (sub)arbore r
int h(NodAVL* r) {
	if (r)
		return 1 + maxim(h(r->st), h(r->dr));
	else
		return 0;
}


// gradul de echilibru al unui nod
void calculGENod(NodAVL* r) {
	if (r) {
		//prelucrare (calcul GE)
		r->grad_echilibru = h(r->dr) - h(r->st);
	}
}


// rotire simpla la dreapta
NodAVL* rotireSimplaDr(NodAVL* pivot, NodAVL* fiuSt) {
	pivot->st = fiuSt->dr;
	calculGENod(pivot);
	fiuSt->dr = pivot;
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire simpla la stanga
NodAVL* rotireSimplaSt(NodAVL* pivot, NodAVL* fiuDr) {
	pivot->dr = fiuDr->st;
	calculGENod(pivot);
	fiuDr->st = pivot;
	calculGENod(fiuDr);

	return fiuDr;
}

// rotire dubla stanga-dreapta
NodAVL* rotireDblStDr(NodAVL* pivot, NodAVL* fiuSt) {
	//aducerea dezechilibrului pe aceeasi directie
	pivot->st = rotireSimplaSt(fiuSt, fiuSt->dr);
	calculGENod(pivot);
	fiuSt = pivot->st;
	//rotire propriu-zisa in pivot
	fiuSt = rotireSimplaDr(pivot, fiuSt);
	calculGENod(fiuSt);

	return fiuSt;
}

// rotire dubla dreapta-stanga
NodAVL* rotireDblDrSt(NodAVL* pivot, NodAVL* fiuDr) {
	// aducerea dezechilibrului pe aceeasi directie
	pivot->dr = rotireSimplaDr(fiuDr, fiuDr->st);
	calculGENod(pivot);
	fiuDr = pivot->dr;
	// rotire propriu-zisa in pivot
	fiuDr = rotireSimplaSt(pivot, fiuDr);
	calculGENod(fiuDr);

	return fiuDr;
}

// inserare nod in arbore binar de cautare
// cheie de cautare: id_user
NodAVL* inserare_user_AVL(NodAVL* r, unsigned short int id, User usr, char* inserat)
{
	// r este nod curent
	if (r != NULL)
	{
		if (r->id_user > id)
		{
			r->st = inserare_user_AVL(r->st, id, usr, inserat);
		}
		else if (r->id_user < id)
		{
			r->dr = inserare_user_AVL(r->dr, id, usr, inserat);
		}
		else
			*inserat = 0; // utilizatorul cu id nu poate fi inserat in AVL
	}
	else
	{
		r = (NodAVL*)malloc(sizeof(NodAVL));
		r->dr = NULL;
		r->st = NULL;
		r->u = usr;
		r->id_user = id;

		*inserat = 1; // utilizatorul cu id este inserat in AVL
	}

	// recalculez grad de echilibru pt nodul curent
	calculGENod(r);
	if (r->grad_echilibru == 2) {
		if (r->dr->grad_echilibru == -1) {
			//dezechilibru dreapta-stanga
			r = rotireDblDrSt(r, r->dr);
		}
		else {
			//dezechilibru dreapta
			r = rotireSimplaSt(r, r->dr);
		}
	}
	else {
		if (r->grad_echilibru == -2) {
			if (r->st->grad_echilibru == 1) {
				//dezechilibru combinat stanga-dreapta
				r = rotireDblStDr(r, r->st);
			}
			else {
				//dezechilibru stanga
				r = rotireSimplaDr(r, r->st);
			}
		}
	}

	return r;
}

void afisareAVLInordine(NodAVL* r)
{
	if (r)
	{
		afisareAVLInordine(r->st);
		
		printf("%hu %s %d\n", r->id_user, r->u.nume_cont, r->grad_echilibru);

		afisareAVLInordine(r->dr);
	}
}

NodAVL* sterge_nod_cheie(NodAVL* r, unsigned short int cheie, User* pdata)
{
	if (r) {
		if (r->id_user < cheie) {
			r->dr = sterge_nod_cheie(r->dr, cheie, pdata);
		}
		else if (r->id_user > cheie) {
			r->st = sterge_nod_cheie(r->st, cheie, pdata);
		}
		else {
			// nodul de sters este prezent in arbore (identificat pe baza de cheie)
			if ((r->st != NULL) && (r->dr != NULL))
			{
				NodAVL* parinte_temp = NULL;
				NodAVL* temp = r->st; // alegere subarbore stanga pentru a cauta cheia maxima
				while (temp->dr != NULL)
				{
					parinte_temp = temp; // actualizare parinte temp inainte de modificarea lui temp
					temp = temp->dr; // cheia maxima se afla in cel mai din dreapta nod din subrabore stanga
				}

				// interschimb date din nodurile r si temp
				unsigned short int auxi = r->id_user;
				r->id_user = temp->id_user;
				temp->id_user = auxi;
				User usr = r->u;
				r->u = temp->u;
				temp->u = usr;

				NodAVL* desc_temp_stanga = temp->st;

				// temp este nodul care se dezaloca
				*pdata = temp->u;
				free(temp);			// dezalocare nod cu User cu cheie dupa interschimb

				if (parinte_temp != NULL)
				{
					parinte_temp->dr = desc_temp_stanga;
				}
				else
				{
					// temp este chiar radacina de subarbore stanga
					r->st = desc_temp_stanga;
				}
			}
			else
			{
				// nodul este frunza SAU are 1 singur descendent
				NodAVL* temp = NULL;
				if (r->st != NULL)
					temp = r->st;
				else
					if (r->dr != NULL)
						temp = r->dr;

				*pdata = r->u;
				free(r); // dezalocare nod

				r = temp; // pentru a lega NULL sau descendent de parinte de r inainte de dezalocare
			}
		}
	}

	return r;
}

int main()
{
	FILE* f = fopen("AccountsTree.txt", "r");
	NodAVL* rad = NULL;

	char buffer[256];
	char sep[] = ";";

	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = NULL;
		User utilizator;
		unsigned short int id_user;
		token = strtok(buffer, sep); // token contine adresa de inceput in buffer pt id_user
		id_user = (unsigned short int)atoi(token);

		token = strtok(NULL, sep);
		utilizator.nume_cont = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_cont, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt nume_user
		utilizator.nume_user = (char*)malloc(strlen(token) + 1);
		strcpy(utilizator.nume_user, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt varsta
		utilizator.varsta = (unsigned char)atoi(token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt deschis_la
		strcpy(utilizator.deschis_la, token);

		// inserare user in arbore binar de cautare
		char inserat = 0; // 0 - false
		rad = inserare_user_AVL(rad, id_user, utilizator, &inserat);
		if (inserat == 0)
		{
			// inserare esuata
			// dezalocare zone pentru evitare memory leaks
			printf("Utilizator cu id %d nu a fost inserat in AVL!\n", id_user);
			free(utilizator.nume_cont);
			free(utilizator.nume_user);
		}
		else
		{
			printf("Utilizator cu id %d confirmat la inserare in AVL!\n", id_user);
		}
	}

	fclose(f);

	// parsare arbore de tip AVL (inordine)
	printf("\nArbore AVL dupa creare:\n");
	afisareAVLInordine(rad);

	// stergere nod pe baza de cheie
	User utilizator;
	utilizator.nume_cont = NULL;
	rad = sterge_nod_cheie(rad, 273, &utilizator);
	if (utilizator.nume_cont != NULL)
	{
		printf("Utilizator %s sters", utilizator.nume_cont);
	}
	printf("\nArbore AVL dupa stergere #1:\n");
	afisareAVLInordine(rad);

	if (utilizator.nume_cont != NULL)
	{
		free(utilizator.nume_cont);
		free(utilizator.nume_user);
		utilizator.nume_cont = NULL;
		utilizator.nume_user = NULL;
	}
	
	rad = sterge_nod_cheie(rad, 399, &utilizator);
	if (utilizator.nume_cont != NULL)
	{
		printf("Utilizator %s sters", utilizator.nume_cont);
	}
	printf("\nArbore AVL dupa stergere #1:\n");
	afisareAVLInordine(rad);

	// dezalocare campuri utilizator
	// dezalocare AVL

	return 0;
}