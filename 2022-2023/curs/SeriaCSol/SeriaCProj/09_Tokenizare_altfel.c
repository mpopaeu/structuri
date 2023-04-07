#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>


int main() {
	FILE* fp;
	char str[100], c[50];
	int a, b;

	/* opening file for reading */
	fp = fopen("Test.txt", "r");

	printf("\n\nUtilizare fgets:\n"); // atentie la continut fisier pe linii
	while (fgets(str, sizeof(str), fp) != NULL) {
		/* writing content to stdout */
		puts(str);
		sscanf(str, "%d %d %[^\n]", &a, &b, c);
		printf("a= %d, b= %d, c= %s\n", a, b, c);
	}

	
	fseek(fp, 0, SEEK_SET);
	printf("\n\nUtilizare fscanf:\n"); // atentie la continut fisier pe linii si ordine apel fscanf!
	fscanf(fp, "%d %d %[^\n]", &a, &b, c);
	while (!feof(fp))
	{
		printf("a= %d, b= %d, c= %s\n", a, b, c);
		fscanf(fp, "%d %d %[^\n]", &a, &b, c);
	}

	fclose(fp);

	return 0;
}