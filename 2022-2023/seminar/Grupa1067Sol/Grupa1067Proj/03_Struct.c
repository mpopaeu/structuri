#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define BUFFER_SIZE 256
#define ACCOUNT_NUMBER 20

struct BankAccount
{
	char* owner;
	char iban[24];
	float balance;
	char currency[4];
};

// function to compute the number od currencies for each bank account owner
// the banck account data is taken from an array (vba)

int main()
{
	FILE* f;
	f = fopen("Accounts.txt", "r");

	unsigned char buffer[BUFFER_SIZE];
	char sep_list[] = ",";

	struct BankAccount vba[ACCOUNT_NUMBER];
	unsigned int i = 0;

	while (fgets(buffer, BUFFER_SIZE, f))
	{
		struct BankAccount ba;
		char* token = strtok(buffer, sep_list); // owner's name
		ba.owner = (char*)malloc(strlen(token) + 1);
		strcpy(ba.owner, token); // there is no conversion

		token = strtok(NULL, sep_list);
		strcpy(ba.iban, token); // no conversion; text-to-text

		token = strtok(NULL, sep_list);
		ba.balance = atof(token); // conversion text-to-binary(as float)

		token = strtok(NULL, sep_list);
		strcpy(ba.currency, token);

		vba[i++] = ba;
	}

	fclose(f);
	return 0;
}