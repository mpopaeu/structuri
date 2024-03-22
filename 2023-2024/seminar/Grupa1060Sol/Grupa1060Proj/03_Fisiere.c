#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct User
{
	char* nume_cont;
	char* nume_user;
	unsigned char varsta;
	char deschis_la[11]; // 10 bytes pt data calendaristica + 1 byte pt terminator string (0x00)
};

int main()
{
	FILE* f = fopen("Accounts.txt", "r");

	struct User *user_array = NULL;
	char buffer[256];
	unsigned char nr_conturi = 0;

	while (fgets(buffer, sizeof(buffer), f))
	{
		nr_conturi += 1;
	}

	user_array = (struct User*)malloc(nr_conturi * sizeof(struct User));

	fseek(f, 0, SEEK_SET);
	unsigned char idx_current = 0;
	char sep[] = ";";

	while (fgets(buffer, sizeof(buffer), f))
	{
		char* token = NULL;
		token = strtok(buffer, sep); // token contine adresa de inceput in buffer pt nume_cont
		user_array[idx_current].nume_cont = (char*)malloc(strlen(token) + 1);
		strcpy(user_array[idx_current].nume_cont, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt nume_user
		user_array[idx_current].nume_user = (char*)malloc(strlen(token) + 1);
		strcpy(user_array[idx_current].nume_user, token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt varsta
		user_array[idx_current].varsta = (unsigned char)atoi(token);

		token = strtok(NULL, sep); // token contine adresa de inceput in buffer pt deschis_la
		strcpy(user_array[idx_current].deschis_la, token);

		idx_current += 1;
	}

	printf("Vector de user-i:\n");
	for (unsigned char i = 0; i < nr_conturi; i++)
		printf("%s %s\n", user_array[i].nume_user, user_array[i].deschis_la);


	// dezalocare vector user_array
	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		free(user_array[i].nume_cont);
		free(user_array[i].nume_user);
	}
	free(user_array); // dezalocare vector de User
	user_array = NULL;

	printf("Vector de user-i dupa dezalocare:\n");
	for (unsigned char i = 0; i < nr_conturi; i++)
	{
		if(user_array != NULL)
			printf("%s %s\n", user_array[i].nume_user, user_array[i].deschis_la);
	}

	fclose(f);
	return 0;
}