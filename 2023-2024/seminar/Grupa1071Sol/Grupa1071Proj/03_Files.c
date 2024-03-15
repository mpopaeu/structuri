#include <stdio.h>

struct BankAccount
{
	char iban[25]; // 24 bytes/positions for iban itself + 1 additional byte at the end (0x00)
	char* owner_name;
	double balance;
	char* currency; 
};

int main()
{
	FILE* f = fopen("Accounts.txt", "r");


	fclose(f);
	return 0;
}