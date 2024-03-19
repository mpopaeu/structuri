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
	//while (fgets(buffer, sizeof(buffer), f))
	//{
	//	buffer[strlen(buffer) - 1] = 0;
	//	strcpy(p_conturi[i].iban, buffer);

	//	fgets(buffer, sizeof(buffer), f);
	//	buffer[strlen(buffer) - 1] = 0;
	//	p_conturi[i].titular = (char*)malloc(strlen(buffer) + 1); // +1 pt byte terminator 0x00
	//	strcpy(p_conturi[i].titular, buffer);

	//	fgets(buffer, sizeof(buffer), f);
	//	buffer[strlen(buffer) - 1] = 0;
	//	strcpy(p_conturi[i].moneda, buffer);

	//	fgets(buffer, sizeof(buffer), f);
	//	buffer[strlen(buffer) - 1] = 0;
	//	p_conturi[i].sold = (float)atof(buffer);

	//	i += 1;
	//}

	char nume_buff[128];
	struct ContBancar contB;
	fscanf(f, "%s\n", contB.iban);
	while (strlen(contB.iban))
	{
		fscanf(f, "%[^\n]", nume_buff);
		contB.titular = (char*)malloc(strlen(nume_buff) + 1);
		strcpy(contB.titular, nume_buff);

		fscanf(f, "%s", contB.moneda);
		fscanf(f, "%f", &contB.sold);

		p_conturi[i] = contB;

		i += 1;
		contB.iban[0] = 0;
		fscanf(f, "%s\n", contB.iban);
	}

	// traversare vector conturi bancare pt confirmare continut
	printf("Vectorul de conturi bancare: \n");
	for (unsigned int i = 0; i < nr_conturi; i++)
		printf("%s %s\n", p_conturi[i].iban, p_conturi[i].titular);

	// dezalocare vector de conturi bancare
	for (unsigned int i = 0; i < nr_conturi; i++)
		free(p_conturi[i].titular);
	free(p_conturi);
	p_conturi = NULL;

	printf("Vectorul de conturi bancare dupa dezalocare: \n");
	for (unsigned int i = 0; i < nr_conturi; i++)
	{
		if(p_conturi != NULL)
			printf("%s %s\n", p_conturi[i].iban, p_conturi[i].titular);
	}

	fclose(f);
	return 0;
}