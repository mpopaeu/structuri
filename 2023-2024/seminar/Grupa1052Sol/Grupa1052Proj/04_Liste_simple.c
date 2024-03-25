#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ContBancar {
	char iban[25]; // 24 dim iban + 1 byte pt 0x00
	float sold;
	char moneda[4]; // 3 dim cod moneda + 1 byte pt 0x00
	char* titular;
};

struct NodLS
{
	struct ContBancar cont;
	struct NodLS* next;
};

typedef struct NodLS NodLS;
typedef struct ContBancar ContBancar;

NodLS* inserare_sfarsit(NodLS* prim, ContBancar cb)
{
	NodLS* nod_nou = (NodLS*)malloc(sizeof(NodLS));

	nod_nou->cont = cb;
	nod_nou->next = NULL;

	if (prim == NULL)
		return nod_nou;

	// parsare lista simpla pana la ultimul nod
	NodLS* t = prim;

	while (t->next != NULL) // parsare lista simpla pana pe ultimul nod
		t = t->next; // modificare adresa din t cu adresa nod succesor

	t->next = nod_nou; // actualizare legatura ultimul nod la nodul adaugat la sfarsitul listei

	return prim;
}

NodLS* interschimb_adiacente(NodLS* prim, char* cIBAN)
{
	if (prim && prim->next)
	{
		// exista cel putin 2 noduri in lista simpla
		if (strcmp(prim->cont.iban, cIBAN) == 0)
		{
			// nodul cautat p este primul din lista simpla
			NodLS* p = prim, * q = prim->next, * s = q->next;
			p->next = s;
			q->next = p;
			prim = q;
		}
		else
		{
			// cazul general
			// se cauta nodul p (incepand cu nodul #2) cu IBAN cIBAN
			NodLS* p = prim->next;
			NodLS* r = prim;
			char vb = 0;
			while ((p->next != NULL) && (vb == 0))
			{
				// parsez lista simpla pana la penultimul nod
				if (strcmp(p->cont.iban, cIBAN) == 0)
				{
					NodLS* q = p->next, * s = q->next;
					r->next = q;
					p->next = s;
					q->next = p;
					vb = 1;
				}
				else
				{
					r = r->next; // r = p;
					p = p->next;
				}
			}
		}
	}

	return prim;
}

// interschimb noduri oarecare p = cIBAN1, q = cIBAN2
NodLS* interschimb_oarecare(NodLS* prim, char* cIBAN1, char* cIBAN2)
{
}

// sortare lista simpla cu interschimbare noduri la nivel de adrese de legatura

int main()
{

	FILE* f = fopen("Conturi.txt", "r");

	char buffer[256], separatori[] = ",\n";
	unsigned char i_curent = 0;
	struct NodLS* primLS = NULL;

	while (fgets(buffer, sizeof(buffer), f))
	{
		struct ContBancar tCont;
		char* token = strtok(buffer, separatori);
		strcpy(tCont.iban, token);

		token = strtok(NULL, separatori);
		strcpy(tCont.moneda, token);

		token = strtok(NULL, separatori);
		tCont.titular = (char*)malloc(strlen(token) + 1);
		strcpy(tCont.titular, token);

		token = strtok(NULL, separatori);
		tCont.sold = (float)atof(token);

		// inserare cont bancar in lista simpla
		primLS = inserare_sfarsit(primLS, tCont);
	}

	// parsare lista pentru validare
	printf("Lista simpla dupa creare:\n");
	NodLS* temp = primLS;
	while (temp)
	{
		printf("%s %s\n", temp->cont.iban, temp->cont.titular);
		temp = temp->next;
	}

	// interschimb noduri adiacente pe baza de iban
	primLS = interschimb_adiacente(primLS, "RO13BRDE1234560987654321");

	// parsare lista pentru validare
	printf("Lista simpla dupa interschimb noduri adiacente:\n");
	temp = primLS;
	while (temp)
	{
		printf("%s %s\n", temp->cont.iban, temp->cont.titular);
		temp = temp->next;
	}



	// dezalocare lista simpla
	while (primLS)
	{
		temp = primLS; // nodul care se dezalocare
		primLS = primLS->next; // noul inceput al listei simple

		free(temp->cont.titular);	// dezalocare string titular cont bancar
		free(temp);				// dezalocare nod
	}

	printf("Lista simpla dupa dezalocare:\n");
	temp = primLS;
	while (temp)
	{
		printf("%s %s\n", temp->cont.iban, temp->cont.titular);
		temp = temp->next;
	}


	fclose(f);
	return 0;
}