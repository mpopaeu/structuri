#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct BankAccount
{
	char iban[25]; // 24 bytes/positions for iban itself + 1 additional byte at the end (0x00)
	char* owner_name;
	double balance;
	char* currency; 
};

typedef struct BankAccount BankAccount;

int main()
{
	FILE* f = fopen("Accounts.txt", "r");
	char buffer[256];
	unsigned char line_counter = 0;

	while (fgets(buffer, sizeof(buffer), f))
	{
		line_counter += 1;
	}

	unsigned char ba_array_size = line_counter / 4; // 4 is the number of fields in structure BankAccount

	BankAccount*  ba_array = (BankAccount*)malloc(ba_array_size * sizeof(BankAccount));
	fseek(f, 0, SEEK_SET);

	unsigned char item_offset = 0;

	while (fgets(buffer, sizeof(buffer), f)) // buffer must contain iban
	{
		strncpy(ba_array[item_offset].iban, buffer, strlen(buffer) - 1);
		ba_array[item_offset].iban[strlen(buffer) - 1] = 0;

		fgets(buffer, sizeof(buffer), f); // buffer must contain owner's name
		ba_array[item_offset].owner_name = (char*)malloc(strlen(buffer));
		strncpy(ba_array[item_offset].owner_name, buffer, strlen(buffer) - 1);
		ba_array[item_offset].owner_name[strlen(buffer) - 1] = 0;

		fgets(buffer, sizeof(buffer), f); // buffer must contain balance data (as string)
		ba_array[item_offset].balance = atof(buffer);

		fgets(buffer, sizeof(buffer), f); // buffer must contain currency
		ba_array[item_offset].currency = (char*)malloc(strlen(buffer));
		strncpy(ba_array[item_offset].currency, buffer, strlen(buffer) - 1);
		ba_array[item_offset].currency[strlen(buffer) - 1] = 0;

		item_offset += 1;
	}

	printf("List of bank accounts:\n");
	for (unsigned char i = 0; i < ba_array_size; i++)
	{
		printf("%s %s\n", ba_array[i].iban, ba_array[i].owner_name);
	}

	// deallocate the bank account array
	for (unsigned char i = 0; i < ba_array_size; i++)
	{
		free(ba_array[i].currency);
		free(ba_array[i].owner_name);
	}
	free(ba_array);
	ba_array = NULL;

	printf("List of bank accounts after deallocation:\n");
	for (unsigned char i = 0; i < ba_array_size; i++)
	{
		if(ba_array != NULL)
			printf("%s %s\n", ba_array[i].iban, ba_array[i].owner_name);
	}

	fclose(f);
	return 0;
}