#include <stdio.h>

#define NR_CIFRE_CARD 16
#define DIM_MONEDA 3
#define DIM_VECTOR_CARDBANCAR 27

struct DataExpirare
{
	unsigned short int anul;
	unsigned char luna;
};

typedef struct DataExpirare DataExpirare;

struct CardBancar
{
	char nr_card[NR_CIFRE_CARD + 1]; // +1 pentru terminatot de string util in cazul utilizarii ca string
	char* titular;
	DataExpirare data;
	float sold;
	char moneda[DIM_MONEDA + 1]; // RON, EUR, USD
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[DIM_VECTOR_CARDBANCAR];
	CardBancar* pv_card = NULL;

	printf("Dimensiune vector v_card = %d\n", sizeof(v_card));
	printf("Dimensiune pointer v_card = %d\n", sizeof(pv_card));
	printf("Dimensiune structura CardBancar = %d\n", sizeof(CardBancar));
	printf("Dimensiune structura DataExpirare = %d\n", sizeof(DataExpirare));

	FILE* f = NULL;

	f = fopen("CarduriBancare.txt", "r");

	// secventa de parsare a fisierului .txt si incarcarea datelor in vectorul v_card

	fclose(f);
}