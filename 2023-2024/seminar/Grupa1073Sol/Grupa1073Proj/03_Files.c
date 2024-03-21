#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

struct BankAccount
{
	char iban[21]; // 20 for iban itself + 1 for end of the string (byte 0x00)
	char* owner_name;
	float balance;
	char currency[4];  // 3 for currency code + 1 for end of the string (byte 0x00)
};

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	unsigned short int line_counter = 0;
	char buffer[256];

	while (fgets(buffer, sizeof(buffer), f))
	{
		line_counter += 1;
	}

	unsigned short int account_count = line_counter / 4; // 4 is the number of fields in BankAccount
	struct BankAccount* account_array = NULL;
	account_array = malloc(sizeof(struct BankAccount) * account_count);
	unsigned char i_current = 0;

	fseek(f, 0, SEEK_SET);
	while (fgets(buffer, sizeof(buffer), f))
	{
		buffer[strlen(buffer) - 1] = 0; // overwrites the byte 0x0a ('\n') with byte 0x00 ('\n' added to buffer by fgets)
		strcpy(account_array[i_current].iban, buffer);

		fgets(buffer, sizeof(buffer), f); // for the owner's name
		buffer[strlen(buffer) - 1] = 0;
		account_array[i_current].owner_name = (char*)malloc(strlen(buffer) + 1);
		strcpy(account_array[i_current].owner_name, buffer);

		fgets(buffer, sizeof(buffer), f); // for the bank account balance
		buffer[strlen(buffer) - 1] = 0;
		account_array[i_current].balance = (float)atof(buffer);

		fgets(buffer, sizeof(buffer), f); // for the bank account currency
		buffer[strlen(buffer) - 1] = 0;
		strcpy(account_array[i_current].currency, buffer);

		i_current += 1;
	}

	printf("Bank account array:\n");
	for (unsigned char i = 0; i < account_count; i++)
	{
		printf("%s %s\n", account_array[i].iban, account_array[i].owner_name);
	}

	// deallocation of the bank account array
	for (unsigned char i = 0; i < account_count; i++)
	{
		free(account_array[i].owner_name); // deallocation performed for each item in the array
	}
	free(account_array); // deallocation of the bank account array
	account_array = NULL;

	printf("Bank account array after deallocation:\n");
	for (unsigned char i = 0; i < account_count; i++)
	{
		if(account_array != NULL)
			printf("%s %s\n", account_array[i].iban, account_array[i].owner_name);
	}

	fclose(f);
	return 0;
}