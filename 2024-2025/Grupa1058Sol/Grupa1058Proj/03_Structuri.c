#include <stdio.h>

#define DIM_NR_CARD 16
#define DIM_DATA_EXPIRARE 5
#define NR_ELEMENTE_VECTOR 30

struct CardBancar
{
	char* titular; // 4 bytes
	char nr_card[DIM_NR_CARD + 1]; // +1 pt byte terminator de string; 20 bytes (17 + 3 padding)
	float sold; // 4 bytes
	char* emitent; // 4 bytes
	char data_expirare[DIM_DATA_EXPIRARE + 1]; // LL/AA; 8 bytes (6 + 2 padding)
};

typedef struct CardBancar CardBancar;

int main()
{
	CardBancar v_card[NR_ELEMENTE_VECTOR];
	CardBancar *pv_card = NULL;

	printf("Dimensiune vector v_card = %d\n", sizeof(v_card));
	printf("Dimensiune structura CardBancar= %d\n", sizeof(CardBancar));
	printf("Dimensiune pointer pv_card = %d\n", sizeof(pv_card));


	// exemplu de populare a vectorului v_card cu date din fisier

	return 0;
}

