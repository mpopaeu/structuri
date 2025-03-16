
#include <stdio.h>

#define CARD_NUMBER_LENGTH 16
#define EXPIRING_DATE_FORMAT_LENGTH 5 // MM/YY

struct BankCard
{
	char* holder; // 4 bytes
	char card_no[CARD_NUMBER_LENGTH + 1];// +1 for null terminator byte; 17 bytes
	float balance; // 4 bytes
	char exp_date[EXPIRING_DATE_FORMAT_LENGTH + 1]; // +1 for null terminator byte; 6 bytes
	char* currency; // 4 bytes
}; // 35 bytes ?!

typedef struct BankCard BankCard;

int main()
{
	BankCard v_card[20];
	BankCard* p_card = NULL;
	printf("Size of the structure BankCard is = %d bytes\n", sizeof(BankCard));
	printf("Size of the array v_card is = %d bytes\n", sizeof(v_card));
	printf("Size of the pointer p_card is = %d bytes\n", sizeof(p_card));


	return 0;
}