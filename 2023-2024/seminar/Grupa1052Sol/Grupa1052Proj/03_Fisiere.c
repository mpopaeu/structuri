#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ContBancar {
	char iban[25]; // 24 dim iban + 1 byte pt 0x00
	float sold;
	char moneda[4]; // 3 dim cod moneda + 1 byte pt 0x00
	char* titular;
};

struct NodLS
{
	struct ContBancar cont;
	struct NodLS* next;
};

int main()
{

	FILE* f = fopen("Conturi.txt", "r");

	char buffer[256], separatori[] = ",";
	struct ContBancar tCont;
	while (fgets(buffer, sizeof(buffer), f)) 
	{
		char* token = strtok(buffer, separatori);
		strcpy(tCont.iban, token);

		token = strtok(NULL, separatori);
		strcpy(tCont.moneda, token);

		token = strtok(NULL, separatori);
		tCont.titular = (char*)malloc(strlen(token) + 1);
		strcpy(tCont.titular, token);

		token = strtok(NULL, separatori);
		tCont.sold = atof(token);
	}

	fclose(f);
	return 0;
}