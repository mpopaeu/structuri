#include <stdio.h>
#include <string.h>

#define CARD_NUMBER_SIZE 16

struct Date
{
	char month; // stored as value
	char year; // stored as value; only last 2 letters are stored
};

typedef struct Date Date;

struct BankCard
{
	char* holder; // 4 bytes
	char card_no[CARD_NUMBER_SIZE +1]; // 17 bytes
	Date exp_date; // 2 bytes -> no alignment (month and year are char)
	char* issuer; // 4 bytes -> enforce alignment by adding +1 byte to card_no
	float balance; // 4 bytes
}; // 31 bytes; actual length is 32 bytes

typedef struct BankCard BankCard;

int main()
{
	printf("Size of structure BankCard = %d", sizeof(BankCard));
	
	return 0;
}