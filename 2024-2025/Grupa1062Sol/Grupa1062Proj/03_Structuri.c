#include <stdio.h>

#define DIM_CARD_BANCAR 16
#define DIM_DATA_EXPIRARE 8
#define DIM_MONEDA 3
#define DIM_VECTOR_CARDBANCAR 25

struct CardBancar
{
	char nr_card[DIM_CARD_BANCAR + 1]; // +1 pentru terminator string; 20 bytes (17 + 3 padding)
	char* titular; // 4 bytes
	char data_expirare[DIM_DATA_EXPIRARE + 1]; // +1 pentru terminator string; 12 bytes (9 + 3 padding) 
	float sold; // 4 bytes
	char moneda[DIM_MONEDA + 1]; // cod moneda; 4 bytes (no padding)
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[DIM_VECTOR_CARDBANCAR];
	CardBancar* pv_card = NULL;
	printf("Dimensiune structura CardBancar = %d bytes\n", sizeof(CardBancar));
	printf("Dimensiune vector v_card = %d bytes\n", sizeof(v_card));
	printf("Dimensiune pointer pv_card = %d bytes\n", sizeof(pv_card));


	// preluare date din fisiere pentru carduri bancare

	return 0;
}