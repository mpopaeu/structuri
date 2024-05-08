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
NodABC* inserare_user_ABC(NodABC* r, unsigned short int id, User usr)
{
	// TODO: implementare cu apel recursiv pentru cautare pozitie in arbore a noului nod
	if (r != NULL)
	{
		//if(strcmp(nume,r->user.nume)>0)
		if (r->id_user > id)
		{
			r->st = inserare_user_ABC(r->st, id, usr);
		}
		else if (r->id_user < id)
		{
			r->dr = inserare_user_ABC(r->dr, id, usr);
		}
	}
	else
	{
		r = (NodABC*)malloc(sizeof(NodABC));
		r->dr = NULL;
		r->st = NULL;
		r->u = usr;
		r->id_user = id;

	}


	return r;
}

void afisareABCInordine(NodABC* rad) {
	if (rad) {
		//SRD
		afisareABCInordine(rad->st);
		printf("%d. Nume:%s, User:%s are varsta de %d, deschis la %s\n", rad->id_user, rad->u.nume_cont, rad->u.nume_user, rad->u.varsta, rad->u.deschis_la);
		afisareABCInordine(rad->dr);
	}
}


void afisareABCPreordine(NodABC* rad) {
	if (rad) {
		//RSD
		printf("%d. Nume:%s, User:%s are varsta de %d, deschis la %s\n", rad->id_user, rad->u.nume_cont, rad->u.nume_user, rad->u.varsta, rad->u.deschis_la);
		afisareABCPreordine(rad->st);
		afisareABCPreordine(rad->dr);
	}
}

void numaraFrunze(NodABC* rad, unsigned char* count)
{
	if (rad)
	{
		if (rad->dr == NULL && rad->st == NULL)
		{
			(*count)++;
		}
		numaraFrunze(rad->st, count);
		numaraFrunze(rad->dr, count);
	}
}

NodABC* dezalocareABC(NodABC* rad) {
	if (rad) {
		rad->st = dezalocareABC(rad->st);
		rad->dr = dezalocareABC(rad->dr);
		free(rad->u.nume_cont);
		free(rad->u.nume_user);
		free(rad);
	}
	return NULL;
}

User* cautaUserDupaId(NodABC* rad, unsigned short int idCautat) {
	if (rad) {
		if (rad->id_user < idCautat) {
			return cautaUserDupaId(rad->dr, idCautat);
		}
		else if (rad->id_user > idCautat) {
			return cautaUserDupaId(rad->st, idCautat);
		}
		else {
			//idurile corespund- am gasit userul;
			//return prin deep copy
			User* user = (User*)malloc(sizeof(User));
			strcpy(user->deschis_la, rad->u.deschis_la);
			user->nume_cont = (char*)malloc(sizeof(char) * (strlen(rad->u.nume_cont) + 1));
			strcpy(user->nume_cont, rad->u.nume_cont);
			user->nume_user = (char*)malloc(sizeof(char) * (strlen(rad->u.nume_user) + 1));
			strcpy(user->nume_user, rad->u.nume_user);
			user->varsta = rad->u.varsta;
			return user;
		}
	}
	else {
		return NULL;
	}
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
		rad = inserare_user_ABC(rad, id_user, utilizator);
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

	//cautare dupa id
	User* user = cautaUserDupaId(rad, 399);
	printf("Nume:%s, User:%s are varsta de %d, deschis la %s\n", user->nume_cont, user->nume_user, user->varsta, user->deschis_la);

	// dezalocare arbore binar de cautare
	rad = dezalocareABC(rad);
	afisareABCInordine(rad);

	//cod scris dupa seminar
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