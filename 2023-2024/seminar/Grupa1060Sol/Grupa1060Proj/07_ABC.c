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

struct NodABC
{
	unsigned short int id_user;
	User u;
	struct NodABC* st, * dr;
};

typedef struct NodABC NodABC;

// inserare nod in arbore binar de cautare
// cheie de cautare: id_user
NodABC* inserare_user_ABC(NodABC* r, unsigned short int id, User usr, char* inserat)
{
	// r este nod curent
	if (r != NULL)
	{
		if (r->id_user > id)
		{
			r->st = inserare_user_ABC(r->st, id, usr, inserat);
		}
		else if (r->id_user < id)
		{
			r->dr = inserare_user_ABC(r->dr, id, usr, inserat);
		}
		else
			*inserat = 0; // utilizatorul cu id nu poate fi inserat in ABC
	}
	else
	{
		r = (NodABC*)malloc(sizeof(NodABC));
		r->dr = NULL;
		r->st = NULL;
		r->u = usr;
		r->id_user = id;

		*inserat = 1; // utilizatorul cu id este inserat in ABC
	}


	return r;
}

void afisareABCInordine(NodABC* r) {
	if (r) {
		//SRD
		// r este nod curent
		afisareABCInordine(r->st);
		printf("%d. Nume:%s, User:%s are varsta de %d, deschis la %s\n", 
					r->id_user, r->u.nume_cont, r->u.nume_user, r->u.varsta, r->u.deschis_la);
		afisareABCInordine(r->dr);
	}
}


void afisareABCPreordine(NodABC* r) {
	if (r) {
		//RSD
		// r este nod curent
		printf("%d. Nume:%s, User:%s are varsta de %d, deschis la %s\n", 
					r->id_user, r->u.nume_cont, r->u.nume_user, r->u.varsta, r->u.deschis_la);
		afisareABCPreordine(r->st);
		afisareABCPreordine(r->dr);
	}
}

void numaraFrunze(NodABC* r, unsigned char* count)
{
	if (r)
	{ // r este nod curent
		if (r->dr == NULL && r->st == NULL)
		{
			(*count)++;
		}
		numaraFrunze(r->st, count);
		numaraFrunze(r->dr, count);
	}
}

NodABC* dezalocareABC(NodABC* r) {
	if (r) { // r este nod curent
		r->st = dezalocareABC(r->st);
		r->dr = dezalocareABC(r->dr);
		free(r->u.nume_cont);
		free(r->u.nume_user);
		free(r);
	}
	return NULL;
}

User* cautaUserDupaId(NodABC* r, unsigned short int idCautat) {
	if (r) {
		if (r->id_user < idCautat) {
			return cautaUserDupaId(r->dr, idCautat);
		}
		else if (r->id_user > idCautat) {
			return cautaUserDupaId(r->st, idCautat);
		}
		else {
			//idurile corespund- am gasit userul;
			//return prin deep copy
			User* user = (User*)malloc(sizeof(User));
			strcpy(user->deschis_la, r->u.deschis_la);
			user->nume_cont = (char*)malloc(sizeof(char) * (strlen(r->u.nume_cont) + 1));
			strcpy(user->nume_cont, r->u.nume_cont);
			user->nume_user = (char*)malloc(sizeof(char) * (strlen(r->u.nume_user) + 1));
			strcpy(user->nume_user, r->u.nume_user);
			user->varsta = r->u.varsta;
			return user;
		}
	}
	else {
		return NULL;
	}
}

// numarul de noduri de pe un nivel specificat
void nr_noduri_nivel(NodABC* r, unsigned char* count, unsigned nivel)
{
	if (r != NULL)
	{
		if ((nivel - 1) == 0)
		{
			// nodul r este plasat pe nivelul specificat
			*count += 1;
			//return;
		}
		else
		{
			nr_noduri_nivel(r->st, count, nivel - 1); // nivel - 1: -1 ---> inca un salt pe nivel inferior (+1) efectuat
			nr_noduri_nivel(r->dr, count, nivel - 1);
		}
	}
}

NodABC* sterge_nod_cheie(NodABC* r, unsigned short int cheie, User* pdata)
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
				NodABC* parinte_temp = NULL;
				NodABC* temp = r->st; // alegere subarbore stanga pentru a cauta cheia maxima
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

				NodABC* desc_temp_stanga = temp->st;
				
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
				NodABC* temp = NULL;
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
	NodABC* rad = NULL;

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
		rad = inserare_user_ABC(rad, id_user, utilizator, &inserat);
		if (inserat == 0)
		{
			// inserare esuata
			// dezalocare zone pentru evitare memory leaks
			printf("Utilizator cu id %d nu a fost inserat in ABC!\n", id_user);
			free(utilizator.nume_cont);
			free(utilizator.nume_user);
		}
		else
		{
			printf("Utilizator cu id %d confirmat la inserare in ABC!\n", id_user);
		}
	}

	fclose(f);

	// parsare arbore binar de cautare (inordine)
	afisareABCInordine(rad);
	printf("\n");
	afisareABCPreordine(rad);

	// determinare numar de noduri frunza
	unsigned char count = 0;
	numaraFrunze(rad, &count);
	printf("Numarul de frunze este: %d\n", count);

	// numar noduri pe nivel specificat
	count = 0;
	nr_noduri_nivel(rad, &count, 4);
	printf("Numarul de noduri de pe nivel specificat este: %d\n", count);

	//cautare dupa id
	User* user = cautaUserDupaId(rad, 399);
	if (user != NULL)
		printf("Nume: %s, User: %s are varsta de %d, deschis la %s\n", 
			user->nume_cont, user->nume_user, user->varsta, user->deschis_la);
	else
		printf("User nu a fost identificat in ABC!\n");

	// stergere nod pe baza de cheie
	User utilizator;
	rad = sterge_nod_cheie(rad, 273, &utilizator);
	printf("Arborele dupa stergere nod: \n");
	afisareABCInordine(rad);

	// dezalocare arbore binar de cautare
	rad = dezalocareABC(rad);
	afisareABCInordine(rad);

	//dezalocarea userului returnat prin DeepCopy
	if (user) {
		if (user->nume_cont) {
			free(user->nume_cont);
		}
		if (user->nume_user) {
			free(user->nume_user);
		}
		free(user);
	}

	return 0;
}