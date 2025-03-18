#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define CARD_NO_LENGTH 16
#define MONEDA_COD_LENGTH 3

struct CardBancar
{
	char nr_card[CARD_NO_LENGTH + 1]; //  +1 pt terminator de string (char[])
	char* detinator;
	char expira_la[6];
	float sold;
	char moneda[MONEDA_COD_LENGTH + 1];
};

typedef struct CardBancar CardBancar;

struct Nod
{
	CardBancar card;
	struct Nod* next;
};

// operatii de baza liste simple: inserare nod inceput, inserare nod sfarsit, stergere nod sfarsit, stergere nod din interior

int main()
{


	return 0;
}
