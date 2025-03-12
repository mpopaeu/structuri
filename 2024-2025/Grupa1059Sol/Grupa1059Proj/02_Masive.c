#include <stdio.h>

#define CARD_NO_LENGTH 16
#define MONEDA_COD_LENGTH 3
#define VECTOR_LENGTH 20

struct CardBancar
{
	char nr_card[CARD_NO_LENGTH + 1]; //  +1 pt terminator de string (char[])
	char* detinator;
	char expira_la[5];
	float sold;
	char moneda[MONEDA_COD_LENGTH + 1];
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_cards[VECTOR_LENGTH];
	CardBancar* pv_cards = NULL;

	printf("Dimensiune CardBancar = %d\n", sizeof(CardBancar));
	printf("Dimensiune vector v_cards = %d\n", sizeof(v_cards));
	printf("Dimensiune pointer pv_cards = %d\n", sizeof(pv_cards));

	// preluarea datelor din fisierul CarduriBancare.txt si incarcarea acestora in vectorul v_cards
	return 0;
}