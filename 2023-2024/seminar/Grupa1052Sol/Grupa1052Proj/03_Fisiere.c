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

	char buffer[256], separatori[] = ",\n";
	unsigned char nr_conturi = 0;
	struct ContBancar* v_conturi = NULL;

	while (fgets(buffer, sizeof(buffer), f))
	{
		nr_conturi += 1;
	}

	v_conturi = (struct ContBancar*)malloc(nr_conturi * sizeof(struct ContBancar));
	unsigned char i_curent = 0;

	fseek(f, 0, SEEK_SET);

	while (fgets(buffer, sizeof(buffer), f)) 
	{
		struct ContBancar tCont;
		char* token = strtok(buffer, separatori);
		strcpy(tCont.iban, token);

		token = strtok(NULL, separatori);
		strcpy(tCont.moneda, token);

		token = strtok(NULL, separatori);
		tCont.titular = (char*)malloc(strlen(token) + 1);
		strcpy(tCont.titular, token);

		token = strtok(NULL, separatori);
		tCont.sold = (float)atof(token);

		// copiere camp cu camp tCont in vector de Conturi pe pozitia i_curent
		strcpy(v_conturi[i_curent].iban, tCont.iban);
		strcpy(v_conturi[i_curent].moneda, tCont.moneda);
		v_conturi[i_curent].sold = tCont.sold;
		v_conturi[i_curent].titular = tCont.titular;

		i_curent += 1;
	}

	printf("Vector de conturi bancare:\n");
	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		printf("%s %s\n", v_conturi[i].iban, v_conturi[i].titular);
	}


	// dezalocare vector de conturi bancare
	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		free(v_conturi[i].titular);
	}
	free(v_conturi);

	v_conturi = NULL;

	fclose(f);
	return 0;
}