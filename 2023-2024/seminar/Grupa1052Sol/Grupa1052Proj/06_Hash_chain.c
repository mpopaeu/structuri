#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HTABLE_SIZE 100

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

// implementare functie hash aplicata pe cheie de tip string
unsigned char calcul_hash(char* cheie, unsigned char size_ht)
{
	unsigned int suma_ascii = 0;
	for (unsigned char i = 0; i < strlen(cheie); i++)
	{
		suma_ascii += cheie[i];
	}

	return (unsigned char)(suma_ascii % size_ht);
}

// inserare cont bancar tCont in tabela de dispersie HTable cu size adrese de inceput
// de liste simple
void inserare_htable(NodLS** HT, unsigned char size, ContBancar tCont)
{
	unsigned char pozitie_hash = calcul_hash(tCont.iban, size);

	HT[pozitie_hash] = inserare_sfarsit(HT[pozitie_hash], tCont);
}


// functia intoarce adresa nodului de lista simpla unde se afla contul bancar
// cu IBAN cautat
NodLS* cauta_cont(NodLS ** HT, unsigned char size, char* cheie_cautare)
{
	NodLS* nod_gasit = NULL;

	unsigned char pozitie_hash = calcul_hash(cheie_cautare, size);
	nod_gasit = HT[pozitie_hash];
	while (nod_gasit != NULL)
	{
		if (strcmp(cheie_cautare, nod_gasit->cont.iban) == 0)
		{
			return nod_gasit; // deoarece IBAN este unic in multimea de conturi bancare
		}
		nod_gasit = nod_gasit->next;
	}

	return nod_gasit;
}

int main()
{

	FILE* f = fopen("Conturi.txt", "r");

	char buffer[256], separatori[] = ",\n";
	NodLS** HTable = NULL;
	unsigned char size_htable = HTABLE_SIZE;

	// alocare vector suport pentru tabela hash cu chaining
	HTable = (NodLS**)malloc(size_htable * sizeof(NodLS*));
	if (HTable)
	{
		// initializare elemente tabela hash cu chaining
		for (unsigned char i = 0; i < size_htable; i++)
			HTable[i] = NULL; // HTable[i] este adresa de inceput a listei i din vector (tabela hash)
	}

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

		// inserare cont bancar in tabela de dispersie cu chaining
		inserare_htable(HTable, size_htable, tCont);
	}

	NodLS* nod_gasit = cauta_cont(HTable, size_htable, "RO13BRDE7777760987654321");
	if (nod_gasit != NULL)
	{
		printf("\nCont bancar identificat in tabela hash: %s %.2f\n", 
					nod_gasit->cont.titular, 
					nod_gasit->cont.sold);
	}
	else
	{
		printf("\nContul bancar cautat nu exista in tabela de dispersie!\n");
	}

	fclose(f);
	return 0;
}