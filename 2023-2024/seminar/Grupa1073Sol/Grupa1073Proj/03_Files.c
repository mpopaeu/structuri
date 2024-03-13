#include <stdio.h>
#include <string.h>
#include <malloc.h>

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

	fseek(f, 0, SEEK_SET);
	while (fgets(buffer, sizeof(buffer), f))
	{
		// try to populate the array account_array
	}

	fclose(f);
	return 0;
}