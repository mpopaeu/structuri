#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define BA_ARRAY_SIZE 20

struct BankAccount {
	char iban[24];
	char* owner;
	float balance;
	char currency[4];
};

// write the function to compute total balance per currency
// input is taken from a bank account array

int main()
{

	FILE* f;
	f = fopen("Account.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",\n";

	struct BankAccount vba[BA_ARRAY_SIZE];
	unsigned int i = 0;

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct BankAccount ba;
		char* token = strtok(buffer, sep_list); // first token (iban) is starting from adress token
		strcpy(ba.iban, token); // iban from the file is copied into ba.iban (it is a text, no conversion)

		token = strtok(NULL, sep_list);
		ba.owner = malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // no conversion for the owner's name

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // cpnversion from ASCII to float internal represetation

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token); // no conversion for currency

		vba[i++] = ba;
	}


	fclose(f);

	return 0;
}