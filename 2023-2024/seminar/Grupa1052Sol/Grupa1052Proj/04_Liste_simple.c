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

int main()
{

	FILE* f = fopen("Conturi.txt", "r");

	char buffer[256], separatori[] = ",\n";
	unsigned char i_curent = 0;
	struct Nod* primLS = NULL;

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


	// dezalocare lista simpla
	fclose(f);
	return 0;
}