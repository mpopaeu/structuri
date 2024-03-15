#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct ContBancar
{
	char iban[25]; // 24 bytes pt iban + 1 byte terminator string
	char moneda[4]; // 3 bytes pt cod moneda + 1 byte terminator string
	char* titular;
	float sold;
};

int main()
{
	FILE* f = fopen("Conturi.txt", "r");
	unsigned char nr_linii = 0;
	char buffer[256];

	while (fgets(buffer, sizeof(buffer), f))
	{
		nr_linii += 1;
	}

	unsigned char nr_conturi = nr_linii / 4;

	struct ContBancar* p_conturi = (struct ContBancar*)malloc(nr_conturi * sizeof(struct ContBancar));

	fseek(f, 0, SEEK_SET);
	unsigned char i = 0;
	while (fgets(buffer, sizeof(buffer), f))
	{
		buffer[strlen(buffer) - 1] = 0;
		strcpy(p_conturi[i].iban, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = 0;
		p_conturi[i].titular = (char*)malloc(strlen(buffer) + 1); // +1 pt byte terminator 0x00
		strcpy(p_conturi[i].titular, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = 0;
		strcpy(p_conturi[i].moneda, buffer);

		fgets(buffer, sizeof(buffer), f);
		buffer[strlen(buffer) - 1] = 0;
		p_conturi[i].sold = (float)atof(buffer);

		i += 1;
	}

	fclose(f);
	return 0;
}